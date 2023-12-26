#include "mylib_dir_TD2/problem.h"
#include "mylib_dir_TD2/unif_mesh.h"
#include "mylib_dir_TD2/imesh.h"
#include "mylib_dir_TD2/equation.h"
#include <iostream>

int main() 
{
    Equation eq;
    IMesh* mesh = new UniformMesh(0, 2, 0.1, 0, 10, 0.1);
    //IMesh* mesh = new UniformMesh(0, 10, 0.1, 0, 10, 1e-6);
    Problem problem(eq, mesh);
    problem.solve();
    delete mesh; 
    return 0;
}
