#ifndef EQUATION_H
#define EQUATION_H

#include "variable.h"
#include "imesh.h"
#include <cmath>
#include <iostream>

class Equation
{
    public:
        template <typename T>
        void compute_initial_condition(Variable &var, IMesh *mesh, T calc_init_cond);
        
        void compute(double time, double position, Variable& u_n, Variable& u_np1, IMesh *mesh);
        
        template <typename T>
        void compute_exact_solution(Variable &var, IMesh *mesh, double t, T calc_exact_sol);
        
        template <typename T>
        void compute_for_scheme(T scheme, double time, IMesh *mesh, Variable& u_n, Variable& u_np1, double a);
};

// it's quite ugly to define the following functions in the header file, but it's the only way I found to make it work
// I tried to define them in equation.cpp, but then I got a linker error
// Why can we define functions in .h files?

auto gaussian = [](double x, double mu, double sigma) -> double
{
    double pi = 4 * atan(1.0);
    return exp(-pow(x - mu, 2) / (2 * pow(sigma, 2))) / (sigma * sqrt(2 * pi));
};

template <typename T>
void Equation::compute_initial_condition(Variable& var, IMesh* mesh, T calc_init_cond)
{
    if (mesh == nullptr) 
    {
        throw std::invalid_argument("IMesh pointer is nullptr");
    }
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step(); 
    for (int n = 0; n < mesh->x_size(); ++ n)
    {
        double x_i = mesh->x_i(n);
        var[n] = calc_init_cond(x_i, mu, sigma);
        
        //std::cout << "x_i: " << x_i << " u_n: " << var[n] << std::endl;
    }
}

template <typename T>
void Equation::compute_for_scheme(T scheme, double time, IMesh* mesh, Variable& u_n, Variable& u_np1, double a)
{
    T::update(u_n, u_np1, a, mesh);
}

template <typename T>
void Equation::compute_exact_solution(Variable& var, IMesh* mesh, double t, T calc_exact_sol)
{
    if (mesh == nullptr) 
    {
        throw std::invalid_argument("error: nullptr");
    }
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);  
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step();
    double CFL = 0.5;
    double a = CFL * mesh->position_step() / mesh->time_step();
    for (int n = 0; n < mesh->x_size(); ++ n)
    {
        double x_i = mesh->x_i(n);
        double x = x_i - a * t;
        var[n] = calc_exact_sol(x, mu, sigma);
        //std::cout << "x_i: " << x_i << " u_ref: " << var[n] << std::endl;
    }
}

#endif
