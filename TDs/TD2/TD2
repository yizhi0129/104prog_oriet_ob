#include "problem.h"
#include "unif_mesh.h"
#include "imesh.h"
#include "equation.h"

#include <iostream>

int main() 
{
    Equation eq;
    IMesh* mesh = new UniformMesh(0, 1, 0.5, 0, 5, 2);
    
    Problem problem(eq, mesh);
    problem.solve();
    
    delete mesh; 
    
    return 0;
}
