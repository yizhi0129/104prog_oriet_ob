#include "problem.h"
#include "variable.h"
#include "upwind.h"
#include "laxwendroff.h"
#include <iostream>

Problem::Problem(const Equation& eq, IMesh* mesh) : equation_(eq), mesh_(mesh) {}

void Problem::solve() 
{    
    Variable u_n = Variable(mesh_);
    Variable u_np1 = Variable(mesh_);
    Variable u_n_2nd_order = Variable(mesh_);
    Variable u_np1_2nd_order = Variable(mesh_);
    Variable u_ref = Variable(mesh_);
    
    std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(u_n, mesh_, gaussian);
    u_np1 = u_n;
    u_n.print();
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    //u_np1.print();
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    equation_.compute_initial_condition(u_n_2nd_order, mesh_, gaussian);
    u_np1_2nd_order = u_n_2nd_order;
    //u_n_2nd_order.print();
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    //u_np1_2nd_order.print();
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    equation_.compute_initial_condition(u_ref, mesh_, gaussian);
    //u_ref.print();

    std::cout << "--- exact solution ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {   
        equation_.compute_exact_solution(u_ref, mesh_, time, gaussian);  
    }

      
    std::cout << "--- Solve problem ---" << std::endl;
    
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
    
    std::cout << "--- upwind ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        std::cout << "--- time: " << time << " ---" << std::endl;
        double n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            equation_.compute_for_scheme(Upwind(), time, mesh_, u_n, u_np1, 0.5);
            u_n[n] = u_np1[n];
            std::cout << u_np1[n] << std::endl;
            n ++;
            //std::cout << u_np1[n] << std::endl;
        }
    }
    

    std::cout << "--- laxwendroff ---" << std::endl;
    
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- time: " << time << " ---" << std::endl;
        double n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            equation_.compute_for_scheme(LaxWendroff(), time, mesh_, u_n_2nd_order, u_np1_2nd_order, 0.5);
            u_n_2nd_order[n] = u_np1_2nd_order[n];
            //std::cout << u_np1_2nd_order[n] << std::endl;   
            n ++;
        }
    }
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    u_np1.print();
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    u_np1_2nd_order.print();
    //std::cout << "--- -------------------------------------------------- ---" << std::endl;
    u_ref.print();
}