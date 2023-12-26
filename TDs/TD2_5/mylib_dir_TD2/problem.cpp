#include "problem.h"
#include "variable.h"
#include "upwind.h"
#include "laxwendroff.h"
#include <iostream>


Problem::Problem(const Equation& eq, IMesh* mesh) : equation_(eq), mesh_(mesh) 
{
    if (mesh == nullptr) 
    {
        throw std::invalid_argument("error: nullptr");
    }
}

void Problem::solve() 
{   
    Timer timer;
    timer.start();

    Variable u_n = Variable(mesh_);
    Variable u_np1 = Variable(mesh_);
    Variable u_n_2nd_order = Variable(mesh_);
    Variable u_np1_2nd_order = Variable(mesh_);
    Variable u_ref = Variable(mesh_);
    
    //std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(u_n, mesh_, gaussian);
    u_np1 = u_n;
    equation_.compute_initial_condition(u_n_2nd_order, mesh_, gaussian);
    u_np1_2nd_order = u_n_2nd_order;
    equation_.compute_initial_condition(u_ref, mesh_, gaussian);

    std::ofstream initFile("init.dat");
    if (!initFile.is_open()) 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else
    {
        u_n.print(initFile);
    }
    initFile.close();
    

    //std::cout << "--- exact solution ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {   
        equation_.compute_exact_solution(u_ref, mesh_, time, gaussian);  
    }
    
    std::ofstream exaFile("ref.dat");
    if (!exaFile.is_open()) 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else
    {
        u_ref.print(exaFile);
    }
    exaFile.close();
      
    //std::cout << "--- Solve problem ---" << std::endl;
    
    /*
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- compute equation at time: " << time << " ---" << std::endl;
        std::cout << "--- time: " << time << " ---" << std::endl;
        int n = 0;
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step())
        {
            u_n[n] = variable[n];
            equation_.compute(time, position, u_n, u_np1, mesh_);
            variable[n] = u_np1[n];
            std::cout << u_np1[n] << std::endl;
            ++ n;
        }
    }
    */
    
    //std::cout << "--- upwind ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- time: " << time << " ---" << std::endl;
        int n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            equation_.compute_for_scheme(Upwind(), time, mesh_, u_n, u_np1, 0.5);
            u_n[n] = u_np1[n];
            //std::cout << u_np1[n] << std::endl;
            n ++;
        }
    }
    
    std::ofstream uwFile("uw.dat");
    if (!uwFile.is_open()) 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else
    {
        u_np1.print(uwFile);
    }
    uwFile.close();

    //std::cout << "--- laxwendroff ---" << std::endl;
    
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- time: " << time << " ---" << std::endl;
        int n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            equation_.compute_for_scheme(LaxWendroff(), time, mesh_, u_n_2nd_order, u_np1_2nd_order, 0.5);
            u_n_2nd_order[n] = u_np1_2nd_order[n];
            //std::cout << u_np1_2nd_order[n] << std::endl;   
            n ++;
        }
    }

    std::ofstream lwdFile("lwd.dat");
    if (!lwdFile.is_open()) 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else
    {
        u_np1_2nd_order.print(lwdFile);
    }
    lwdFile.close();
    
    timer.stop();
    timer.print("reference time");
}


void Problem::solve_parallel()
{
    Timer timer2;
    timer2.start();

    Variable u_n = Variable(mesh_);
    Variable u_np1 = Variable(mesh_);
    Variable u_n_2nd_order = Variable(mesh_);
    Variable u_np1_2nd_order = Variable(mesh_);
    Variable u_ref = Variable(mesh_);

    //std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(u_n, mesh_, gaussian);
    u_np1 = u_n;
    equation_.compute_initial_condition(u_n_2nd_order, mesh_, gaussian);
    u_np1_2nd_order = u_n_2nd_order;
    equation_.compute_initial_condition(u_ref, mesh_, gaussian);

    std::ofstream initFile("init.dat");
    if (!initFile.is_open()) 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else
    {
        u_n.print(initFile);
    }
    initFile.close();

    std::thread first_thread([&]()
    {
        //std::cout << "--- exact solution ---" << std::endl;
        for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
        {   
            equation_.compute_exact_solution(u_ref, mesh_, time, gaussian);  
        } 
        std::ofstream exaFile("ref.dat");
        if (!exaFile.is_open()) 
        {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else
        {
            u_ref.print(exaFile);
        }
        exaFile.close();
    });
      


    //std::cout << "--- Solve problem ---" << std::endl;

    std::thread second_thread([&]()
    {
        //std::cout << "--- upwind ---" << std::endl;
        for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
        {
            //std::cout << "--- time: " << time << " ---" << std::endl;
            int n = 0;
        
            for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
            {
                equation_.compute_for_scheme(Upwind(), time, mesh_, u_n, u_np1, 0.5);
                u_n[n] = u_np1[n];
                //std::cout << u_np1[n] << std::endl;
                n ++;
            }
        }
        std::ofstream uwFile("uw.dat");
        if (!uwFile.is_open()) 
        {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else
        {
            u_np1.print(uwFile);
        }
        uwFile.close();
    });
   

    std::thread third_thread([&]()
    {
        //std::cout << "--- laxwendroff ---" << std::endl;
    
        for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
        {
            int n = 0;
        
            for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
            {
                equation_.compute_for_scheme(LaxWendroff(), time, mesh_, u_n_2nd_order, u_np1_2nd_order, 0.5);
                u_n_2nd_order[n] = u_np1_2nd_order[n];  
                n ++;
            }
        }
        std::ofstream lwdFile("lwd.dat");
        if (!lwdFile.is_open()) 
        {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else
        {
            u_np1_2nd_order.print(lwdFile);
        }
        lwdFile.close();
    });

    first_thread.join();
    second_thread.join();
    third_thread.join();

    timer2.stop();
    timer2.print("treads time");
}

void Problem::solve_async()
{
    Timer timer3;
    timer3.start();

    Variable u_n = Variable(mesh_);
    Variable u_np1 = Variable(mesh_);
    Variable u_n_2nd_order = Variable(mesh_);
    Variable u_np1_2nd_order = Variable(mesh_);
    Variable u_ref = Variable(mesh_);

    //std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(u_n, mesh_, gaussian);
    u_np1 = u_n;
    equation_.compute_initial_condition(u_n_2nd_order, mesh_, gaussian);
    u_np1_2nd_order = u_n_2nd_order;
    equation_.compute_initial_condition(u_ref, mesh_, gaussian);

    std::ofstream initFile("init.dat");
    if (!initFile.is_open()) 
    {
        std::cerr << "Error opening the file!" << std::endl;
    }
    else
    {
        u_n.print(initFile);
    }
    initFile.close();

    std::future first_task = std::async(std::launch::async,[&]()
    {
        //std::cout << "--- exact solution ---" << std::endl;
        for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
        {   
            equation_.compute_exact_solution(u_ref, mesh_, time, gaussian);  
        }           
        std::ofstream exaFile("ref.dat");
        if (!exaFile.is_open()) 
        {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else
        {
            u_ref.print(exaFile);
        }
        exaFile.close(); 
    });
      


    //std::cout << "--- Solve problem ---" << std::endl;

    std::future second_task = std::async(std::launch::async,[&]()
    {
        //std::cout << "--- upwind ---" << std::endl;
        for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
        {
            //std::cout << "--- time: " << time << " ---" << std::endl;
            int n = 0;
        
            for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
            {
                equation_.compute_for_scheme(Upwind(), time, mesh_, u_n, u_np1, 0.5);
                u_n[n] = u_np1[n];
                //std::cout << u_np1[n] << std::endl;
                n ++;
            }
        }
        std::ofstream uwFile("uw.dat");
        if (!uwFile.is_open()) 
        {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else
        {
            u_np1.print(uwFile);
        }
        uwFile.close();
    });
   

    std::future third_task = std::async(std::launch::async,[&]()
    {
        //std::cout << "--- laxwendroff ---" << std::endl;
    
        for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
        {
            int n = 0;
        
            for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
            {
                equation_.compute_for_scheme(LaxWendroff(), time, mesh_, u_n_2nd_order, u_np1_2nd_order, 0.5);
                u_n_2nd_order[n] = u_np1_2nd_order[n];  
                n ++;
            }
        }
        std::ofstream lwdFile("lwd.dat");
        if (!lwdFile.is_open()) 
        {
            std::cerr << "Error opening the file!" << std::endl;
        }
        else
        {
            u_np1_2nd_order.print(lwdFile);
        }
        lwdFile.close();
    });

    first_task.wait();
    second_task.wait();
    third_task.wait();

    timer3.stop();
    timer3.print("async time");
}