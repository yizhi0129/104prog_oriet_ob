#include <iostream>
#include "upwind.h"

void Upwind::update(double &u1, double &u2, double a, IMesh *mesh)
{
    double CFL = 0.5;
    double u_im1 = ;
    u2 = u1 - CFL * (u1 - u_im1); 
    u1 = u2;
}