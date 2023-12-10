#ifndef EQUATION_H
#define EQUATION_H

#include "variable.h"
#include "imesh.h"

class Equation
{
public:
    void compute(double time, double position, double &u_n, double &u_np1, IMesh *mesh);
    void compute_initial_condition(Variable &var, IMesh *mesh);
};

#endif
