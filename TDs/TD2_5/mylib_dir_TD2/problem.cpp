#include "problem.h"
#include "variable.h"
#include "upwind.h"
#include "laxwendroff.h"
#include <iostream>


Problem::Problem(const Equation& eq, IMesh* mesh) : equation_(eq), mesh_(mesh) {}

void Problem::solve() 
{    
    Variable variable = Variable(mesh_);
    std::cout << "--- exact solution ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- time: " << time << " ---" << std::endl;    
        equation_.compute_exact_solution(variable, mesh_, time, gaussian);  
    }




    std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(variable, mesh_, gaussian);
    
    
    std::cout << "--- Solve problem ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- compute equation at time: " << time << " ---" << std::endl;
        std::cout << "--- time: " << time << " ---" << std::endl;
        double n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            double &u_n = variable[n];
            double u_np1 = 0.0;
            equation_.compute(time, position, u_n, u_np1, mesh_);
            variable[n] = u_np1;
            std::cout << "x_i: " << position << " u_np1: " << u_np1 << std::endl;
            ++ n;
        }
    }



    std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(variable, mesh_, gaussian);

    std::cout << "--- upwind ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        std::cout << "--- time: " << time << " ---" << std::endl;
        double n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            double &u_n = variable[n];
            double u_np1 = 0.0;
            equation_.compute_for_scheme(Upwind(), time, mesh_, u_n, u_np1, 0.5);
            variable[n] = u_np1;
            std::cout << "x_i: " << position << " u_np1: " << u_np1 << std::endl;
            ++ n;
        }
    }



    std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(variable, mesh_, gaussian);

    std::cout << "--- laxwendroff ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        std::cout << "--- time: " << time << " ---" << std::endl;
        double n = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            double &u_n_2nd_order = variable[n];
            double u_np1_2nd_order = 0.0;
            equation_.compute_for_scheme(LaxWendroff(), time, mesh_, u_n_2nd_order, u_np1_2nd_order, 0.5);
            variable[n] = u_np1_2nd_order;
            std::cout << "x_i: " << position << " u_np1_2nd_order: " << u_np1_2nd_order << std::endl;
            ++ n;
        }
    }
    variable.print();


}


