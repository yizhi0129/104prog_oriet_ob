#include "unif_mesh.h"

UniformMesh::UniformMesh(double t_ini, double t_final, double dt, double x_min, double x_max, double dx)
    : t_ini_(t_ini), t_final_(t_final), dt_(dt), x_min_(x_min), x_max_(x_max), dx_(dx) {}

double UniformMesh::getInitialTime() const 
{
    return t_ini_;
}

double UniformMesh::getFinalTime() const 
{
    return t_final_;
}

double UniformMesh::getTimeStep() const 
{
    return dt_;
}

double UniformMesh::getInitialPosition() const 
{
    return x_min_;
}

double UniformMesh::getFinalPosition() const 
{
    return x_max_;
}

double UniformMesh::getSpaceStep() const 
{
    return dx_;
}
