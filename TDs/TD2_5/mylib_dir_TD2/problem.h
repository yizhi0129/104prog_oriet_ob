#ifndef PROBLEM_H
#define PROBLEM_H

#include "imesh.h"
#include "equation.h"


class Problem 
{
public:
    Problem(const Equation& eq, IMesh* mesh);
    void solve();
    ~Problem() = default; 
private:
    Equation equation_;
    IMesh* mesh_;
};

#endif
