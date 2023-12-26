#include "equation.h"
#include "variable.h"

class LaxWendroff
{
     public:
        static void update(Variable& u_n_2nd_order, Variable& u_np1_2nd_order, double a, IMesh *mesh);
};