#ifndef EQUATION_H
#define EQUATION_H

#include "variable.h"
#include "imesh.h"
#include <cmath>

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
    for (int i = 0; i <= mesh->x_size(); ++ i)
    {
        double x_i = mesh->x_i(i);
        var[i] = calc_init_cond(x_i, mu, sigma);
    }
}

template <typename T>
void Equation::compute_for_scheme(T scheme, double time, IMesh* mesh, double &u_n, double &u_np1, double a)
{
    T::update(u_n, u_np1, a, mesh);
}



#endif
