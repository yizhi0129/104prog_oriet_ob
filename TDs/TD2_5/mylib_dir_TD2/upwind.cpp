#include <iostream>
#include "upwind.h"

void Upwind::update(double &u_n, double &u_np1, double a, IMesh *mesh)
{
    double CFL = 0.5;
    double u_nim1 = *(&u_n - 1);
    u_np1 = u_n - CFL * (u_n - u_nim1); 
    u_n = u_np1;
}