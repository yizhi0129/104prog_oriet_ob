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
        
        void compute(double time, double position, double &u_n, double &u_np1, IMesh *mesh);
        
        template <typename T>
        void compute_exact_solution(Variable &var, IMesh *mesh, double t, T calc_exact_sol);
        
        template <typename T>
        void compute_for_scheme(T scheme, double time, IMesh *mesh, double &u_n, double &u_np1, double a);
};



// it's quite ugly to define the following functions in the header file, but it's the only way I found to make it work
// I tried to define them in equation.cpp, but then I got a linker error
// Why can we define functions in .h files?

inline auto gaussian = [](double x, double mu, double sigma)
{
    double pi = 4 * atan(1.0);
    return exp(-pow(x - mu, 2) / (2 * pow(sigma, 2))) / (sigma * sqrt(2 * pi));
};

template <typename T>
void Equation::compute_initial_condition(Variable& var, IMesh* mesh, T calc_init_cond)
{
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step(); 
    for (int i = 0; i < mesh->x_size(); ++ i)
    {
        double x_i = mesh->x_i(i);
        var[i] = calc_init_cond(x_i, mu, sigma);
        std::cout << "x_i: " << x_i << " u_n: " << var[i] << std::endl;
    }
}

template <typename T>
void Equation::compute_for_scheme(T scheme, double time, IMesh* mesh, double &u_n, double &u_np1, double a)
{
    T::update(u_n, u_np1, a, mesh);
}

/*
template <typename T>
void Equation::compute_exact_solution(Variable& var, IMesh* mesh, double t, T calc_exact_sol)
{
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);
    double t_ini = mesh->initial_time();
    double t_final = mesh->final_time();
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step();
    double CFL = 0.5;
    double a = CFL * mesh->position_step() / mesh->time_step();
    for (int n = 0; n <= mesh->t_size(); ++ n)
    {
        t = mesh->t_n(n);
        for (int i = 0; i <= mesh->x_size(); ++ i)
        {
            double x_i = mesh->x_i(i);
            double x = x_i - a * (t - t_ini);
            var[i] = calc_exact_sol(x, mu, sigma);
            std::cout << "x_i: " << x_i << " u_n: " << var[i] << std::endl;
        }
    }
}
*/
template <typename T>
void Equation::compute_exact_solution(Variable& var, IMesh* mesh, double t, T calc_exact_sol)
{
    t = mesh->final_time();
    double x_max = mesh->x_i(mesh->x_size());
    double x_min = mesh->x_i(0);  
    double mu = (x_max - x_min) / 2.0;
    double sigma = 10 * mesh->position_step();
    double CFL = 0.5;
    double a = CFL * mesh->position_step() / mesh->time_step();
    for (int i = 0; i < mesh->x_size(); ++ i)
    {
        double x_i = mesh->x_i(i);
        double x = x_i - a * t;
        var[i] = calc_exact_sol(x, mu, sigma);
        std::cout << "x_i: " << x_i << " u_n: " << var[i] << std::endl;
    }
}

#endif
