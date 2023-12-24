#include "equation.h"

class LaxWendroff
{
     public:
        static void update(double &u_n, double &u_np1, double a, IMesh *mesh);
};