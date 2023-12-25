#include "laxwendroff.h"

void LaxWendroff::update(double &u1, double &u2, double a, IMesh *mesh)
{
     double CFL = 0.5;
     double u_im1 = ;
     double u_ip1 = ;
     u2 = u1 - CFL * (u_ip1 - u_im1) / 2.0 + pow(CFL, 2) * (u_ip1 - 2 * u1 + u_im1) / 2.0; 
     u1 = u2;
};