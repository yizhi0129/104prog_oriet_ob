#include "problem.h"
#include <iostream>

Problem::Problem(const Equation& eq, IMesh* mesh) : equation_(eq), mesh_(mesh) {}

void Problem::solve() 
{
    std::cout << "--- Solve problem ---" << std::endl;
    
    for (double time = mesh_->getInitialTime(); time <= mesh_->getFinalTime(); time += mesh_->getTimeStep()) 
    {
        std::cout << "--- compute equation at time: " << time << " ---" << std::endl;
        
        for (double position = mesh_->getInitialPosition(); position <= mesh_->getFinalPosition(); position += mesh_->getSpaceStep()) 
        {
            equation_.compute(time, position);
        }
    }
}
