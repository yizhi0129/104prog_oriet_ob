#include "equation.h"
#include <iostream>


// void Upwind::update(double &u_n, double &u_np1, double a, IMesh *mesh)
// {
//     double CFL = 0.5;
//     double u_nim1 = *(&u_n - 1);
//     u_np1 = u_n - CFL * (u_n - u_nim1); 
//     u_n = u_np1;
// }

// void LaxWendroff::update(double &u_n, double &u_np1, double a, IMesh *mesh)
// {
//     double CFL = 0.5;
//     double u_nim1 = *(&u_n - 1);
//     double u_nip1 = *(&u_n + 1);
//     u_np1 = u_n - CFL * (u_nip1 - u_nim1) / 2.0 + pow(CFL, 2) * (u_nip1 - 2 * u_n + u_nim1) / 2.0; 
//     u_n = u_np1;
// }


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
            var[i] = calc_exact_sol(x_i, mu, sigma, t, a);
        }
    }
}
