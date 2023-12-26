#include "equation.h"
#include <iostream>

void Equation::compute(double time, double position, Variable& u_n, Variable& u_np1, IMesh *mesh)
{
    if (mesh == nullptr) 
    {
        throw std::invalid_argument("error: nullptr");
    }
    // std::cout << "Computing equation at time: " << time << " -- at x_i = " << position << std::endl;
    double CFL = 0.5;
    u_np1[0] = u_n[0] - CFL * u_n[0];
    for (int i = 1; i < mesh->t_size(); i ++)
    {
        u_np1[i] = u_n[i] - CFL * (u_n[i] - u_n[i - 1]); 
        //u_n = u_np1;
    } 
}



