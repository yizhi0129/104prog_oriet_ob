#include "equation.h"
#include "variable.h"

class LaxWendroff
{
     public:
        static void update(std::vector<double> u_n_2nd_order, std::vector<double> u_np1_2nd_order, double a, IMesh *mesh);
};