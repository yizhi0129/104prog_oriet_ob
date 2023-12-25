#include "equation.h"
#include <iostream>

void Equation::compute(double time, double position, std::vector<double> u_n, std::vector<double> u_np1, IMesh *mesh)
{
    // std::cout << "Computing equation at time: " << time << " -- at x_i = " << position << std::endl;
    double CFL = 0.5;
    for (int i = 1; i < mesh->t_size(); i ++)
    {
        u_np1[i] = u_n[i] - CFL * (u_n[i] - u_n[i - 1]); 
        u_n = u_np1;
    } 
}



