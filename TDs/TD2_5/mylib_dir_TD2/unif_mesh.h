#ifndef UNIF_MESH_H
#define UNIF_MESH_H

#include "imesh.h"

class UniformMesh : public IMesh 
{
private:
    double t_ini;
    double t_final;
    double dt;
    double x_min;
    double x_max;
    double dx;

public:
    UniformMesh(double t_ini, double t_final, double dt, double x_min, double x_max, double dx);
    
    double initial_time() const override;
    double final_time() const override;
    double time_step() const override;
    double initial_position() const override;
    double final_position() const override;
    double position_step() const override;

    int x_size() const override;
    // ~UniformMesh() = default;
};

#endif
