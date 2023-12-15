#include "equation.h"
#include <iostream>
#include <cmath>

void Equation::compute(double time, double position, double &u_n, double &u_np1, IMesh *mesh)
{
    // std::cout << "Computing equation at time: " << time << " -- at x_i = " << position << std::endl;
    double CFL = 0.5;
    double a = CFL * mesh->position_step() / mesh->time_step();
    double u_nim1 = *(&u_n - 1);
    u_np1 = u_n - CFL * (u_n - u_nim1); 
    u_n = u_np1;

    std::cout << "time" << time << ", position" << position << ", u_n = " << u_n << std::endl;
}

void Equation::compute_initial_condition(Variable& var, IMesh* mesh)
{
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step(); 
    double pi = 4 * atan(1.0);
    for (int i = 0; i <= mesh->x_size(); ++ i)
    {
        double x_i = mesh->x_i(i);
        double value = exp(-pow(x_i - mu, 2) / (2 * pow(sigma, 2))) / (sigma * sqrt(2 * pi));
        var[i] = value;
    }
}

void Equation::compute_exact_solution(Variable& var, IMesh* mesh, double t)
{
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);
    double t_ini = mesh->initial_time();
    double t_final = mesh->final_time();
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step();
    double pi = 4 * atan(1.0);
    double t = t_ini;
    for (int n = 0; n <= mesh->t_size(); ++ n)
    {
        double t = mesh->t_n(n);
        double x_i = mesh->x_i(i);
        double a = 0.5;
        double val_exa = exp(-pow((x_i - a * t)- mu, 2) / (2 * pow(sigma, 2))) / (sigma * sqrt(2 * pi)); 
    }
}
