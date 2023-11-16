#ifndef UNIF_MESH_H
#define UNIF_MESH_H

#include "imesh.h"

class UniformMesh : public IMesh 
{
public:
    UniformMesh(double t_ini, double t_final, double dt, double x_min, double x_max, double dx);
    
    double getInitialTime() const override;
    double getFinalTime() const override;
    double getTimeStep() const override;
    double getInitialPosition() const override;
    double getFinalPosition() const override;
    double getSpaceStep() const override;
    
private:
    double t_ini_;
    double t_final_;
    double dt_;
    double x_min_;
    double x_max_;
    double dx_;
};

#endif
