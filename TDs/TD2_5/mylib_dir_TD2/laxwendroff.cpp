#include "laxwendroff.h"


void LaxWendroff::update(std::vector<double> u_n_2nd_order, std::vector<double> u_np1_2nd_order, double a, IMesh *mesh)
{
     double CFL = 0.5;
     double c = CFL / 2.0;
     double b = pow(CFL, 2) / 2.0;
     u_np1_2nd_order[0] = u_n_2nd_order[0] - a * u_n_2nd_order[1] + b * (u_n_2nd_order[1] - 2 * u_n_2nd_order[0]);
     for (int i = 1; i < mesh->t_size(); i ++)
     {
          u_np1_2nd_order[i] = u_n_2nd_order[i] - c * (u_n_2nd_order[i + 1] - u_n_2nd_order[i - 1]) +  b * (u_n_2nd_order[i + 1] - 2 * u_n_2nd_order[i] + u_n_2nd_order[i - 1]); 
          //u_n_2nd_order = u_np1_2nd_order;
     }    
};