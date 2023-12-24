#include "laxwendroff.h"

void LaxWendroff::update(double &u_n, double &u_np1, double a, IMesh *mesh)
{
     double CFL = 0.5;
     double u_nim1 = *(&u_n - 1);
     double u_nip1 = *(&u_n + 1);
     u_np1 = u_n - CFL * (u_nip1 - u_nim1) / 2.0 + pow(CFL, 2) * (u_nip1 - 2 * u_n + u_nim1) / 2.0; 
     u_n = u_np1;
     std::cout << "-----------laxwendroff-----------" << std::endl;
     std::cout << "u_n: " << u_n << " u_np1: " << u_np1 << std::endl;
};