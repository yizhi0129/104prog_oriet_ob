#include "unif_mesh.h"
#include <iostream>

double UniformMesh::initial_time() const
{
    return t_ini;
};

double UniformMesh::final_time() const
{
    return t_final;
};

double UniformMesh::time_step() const
{
    return dt;
};

double UniformMesh::initial_position() const
{
    return x_min;
};

double UniformMesh::final_position() const
{
    return x_max;
};

double UniformMesh::position_step() const
{
    return dx;
};

UniformMesh::UniformMesh(double t_ini, double t_final, double dt, double x_min, double x_max, double dx)
{
    this->t_ini = t_ini;
    this->t_final = t_final;
    this->dt = dt;
    this->x_min = x_min;
    this->x_max = x_max;
    this->dx = dx;
};

int UniformMesh::x_size() const
{
    return (final_position() - initial_position()) / position_step() + 1;
};

double UniformMesh::x_i(int i) const
{
    return initial_position() + i * position_step();
};