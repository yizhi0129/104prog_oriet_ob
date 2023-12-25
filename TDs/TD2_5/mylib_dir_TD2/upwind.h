#include "imesh.h"
#include "variable.h"

class Upwind
{
    public:
        static void update(std::vector<double> u_n, std::vector<double> u_np1, double a, IMesh *mesh); 
};