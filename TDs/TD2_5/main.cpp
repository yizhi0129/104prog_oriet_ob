#include "mylib_dir_TD2/problem.h"
#include "mylib_dir_TD2/unif_mesh.h"
#include "mylib_dir_TD2/imesh.h"
#include "mylib_dir_TD2/equation.h"
#include <iostream>

int main(int argc, char* argv[]) 
{
    double t_init, t_final, dt, x_min, x_max, dx;
    std::string option = argv[7];

    if (argc != 8) 
    {
        std::cout << "usage: " << argv[0] << " t_init t_final dt x_min x_max dx option" << std::endl;
        return 1;
    }
    t_init = std::stof(argv[1]);
    t_final = std::stof(argv[2]);
    dt = std::stof(argv[3]);
    x_min = std::stof(argv[4]);
    x_max = std::stof(argv[5]);
    dx = std::stof(argv[6]);
    

    Equation eq;
    IMesh* mesh = new UniformMesh(t_init, t_final, dt, x_min, x_max, dx);
    
    Problem problem(eq, mesh);
    if (option == "solve") 
    {
        problem.solve();
    } 
    else if (option == "solve_parallel") 
    {
        problem.solve_parallel();
    } 
    else if (option == "solve_async") 
    {
        problem.solve_async();
    } 
    else 
    {
        std::cerr << "Invalid execution option. Please use 'solve', 'solve_parallel', or 'solve_async'." << std::endl;
    }

    
    delete mesh; 
    return 0;
}
