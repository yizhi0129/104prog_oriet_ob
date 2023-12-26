#include "upwind.h"

void Upwind::update(std::vector<double> u_n, std::vector<double> u_np1, double a, IMesh *mesh)
{
    double CFL = 0.5;
    u_np1[0] = u_n[0] - CFL * u_n[0];
    for (int i = 1; i < mesh->t_size(); i ++)
    {
        u_np1[i] = u_n[i] - CFL * (u_n[i] - u_n[i - 1]); 
        //u_n = u_np1;
    }    
}