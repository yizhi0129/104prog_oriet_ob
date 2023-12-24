#include "equation.h"
#include <iostream>



void Equation::compute(double time, double position, double &u_n, double &u_np1, IMesh *mesh)
{
    // std::cout << "Computing equation at time: " << time << " -- at x_i = " << position << std::endl;
    double CFL = 0.5;
    double a = CFL * mesh->position_step() / mesh->time_step();
    double u_nim1 = *(&u_n - 1);
    u_np1 = u_n - CFL * (u_n - u_nim1); 
    u_n = u_np1;

    //std::cout << "time" << time << ", position" << position << ", u_n = " << u_n << std::endl;
}



