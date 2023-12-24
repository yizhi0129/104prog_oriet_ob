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


// class Upwind
// {
//     public:
//         static void update(double &u_n, double &u_np1, double a, IMesh *mesh); 
// };

// class LaxWendroff
// {
//     public:
//         static void update(double &u_n, double &u_np1, double a, IMesh *mesh);
// };


#endif
