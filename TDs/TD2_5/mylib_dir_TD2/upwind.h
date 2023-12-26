#include "imesh.h"
#include "variable.h"

class Upwind
{
    public:
        static void update(Variable& u_n, Variable& u_np1, double a, IMesh *mesh); 
};