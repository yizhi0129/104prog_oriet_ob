#include "problem.h"
#include "variable.h"
#include <iostream>

Problem::Problem(const Equation& eq, IMesh* mesh) : equation_(eq), mesh_(mesh) {}

void Problem::solve() 
{
    int n = 0;
    
    Variable variable = Variable(mesh_);
    std::cout << variable[0] << std::endl;
    std::cout << variable[1] << std::endl;

    double &u_n = variable[n];
    double &u_np1 = variable[n+1];

    std::cout << "--- Solve problem ---" << std::endl;
    
    for (double time = mesh_->initial_time(); time <= mesh_->final_time(); time += mesh_->time_step()) 
    {
        std::cout << "--- compute equation at time: " << time << " ---" << std::endl;
        
        for (double position = mesh_->initial_position(); position <= mesh_->final_position(); position += mesh_->position_step()) 
        {
            equation_.compute(time, position);
        }
    }

    u_n = u_np1;
}


