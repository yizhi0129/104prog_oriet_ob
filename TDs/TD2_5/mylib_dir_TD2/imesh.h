#ifndef IMESH_H
#define IMESH_H

class IMesh 
{
private:
    double t_ini;
    double t_final;
    double dt;
    double x_min;
    double x_max;
    double dx;

public:
    virtual double initial_time() const = 0;
    virtual double final_time() const = 0;
    virtual double time_step() const = 0;
    virtual double initial_position() const = 0;
    virtual double final_position() const = 0;
    virtual double position_step() const = 0;

    virtual int x_size() const = 0;
    virtual double x_i(int i) const = 0;  
    
    virtual ~IMesh() = default;
};

#endif

