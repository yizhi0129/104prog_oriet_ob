#include "problem.h"
#include "variable.h"
#include "upwind.h"
#include <iostream>


Problem::Problem(const Equation& eq, IMesh* mesh) : equation_(eq), mesh_(mesh) {}

void Problem::solve() 
{    
    Variable variable = Variable(mesh_);

    std::cout << "--- Initial condition ---" << std::endl;
    equation_.compute_initial_condition(variable, mesh_, gaussian);
    variable.print();
    
    //std::cout << "--- Solve problem ---" << std::endl;
    std::cout << "--- approximation ---" << std::endl;
    for (double time = mesh_->initial_time(); time < mesh_->final_time(); time += mesh_->time_step()) 
    {
        //std::cout << "--- compute equation at time: " << time << " ---" << std::endl;
        std::cout << "--- time: " << time << " ---" << std::endl;
        double i = 0;
        
        for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
        {
            double &u_n = variable[i];
            double u_np1 = 0.0;
            //equation_.compute(time, position, u_n, u_np1, mesh_);
            equation_.compute_for_scheme(Upwind(), time, mesh_, u_n, u_np1, 0.5);
            std::cout << "u_n: " << u_n << " u_np1: " << u_np1 << std::endl;
            ++ i;
        }
    }
    variable.print();

    std::cout << "--- exact solution ---" << std::endl;

    double i = 0;
        
    for (double position = mesh_->initial_position(); position < mesh_->final_position(); position += mesh_->position_step()) 
    {
        double &u_n = variable[i];
        double u_np1 = 0.0;
        equation_.compute_exact_solution(variable, mesh_, mesh_->final_time(), gaussian);
        std::cout << "u_n: " << u_n << " u_np1: " << u_np1 << std::endl;
        ++ i;
    }

    variable.print();
}


