#ifndef PROBLEM_H
#define PROBLEM_H

#include "imesh.h"
#include "equation.h"
#include <algorithm>
#include <stdexcept>
#include "timer.h"
#include <thread>
#include <execution>
#include <future>


class Problem 
{
public:
    Problem(const Equation& eq, IMesh* mesh);
    void solve();
    void solve_parallel();
    void solve_async();
    ~Problem() = default; 
private:
    Equation equation_;
    IMesh* mesh_;
};

#endif
