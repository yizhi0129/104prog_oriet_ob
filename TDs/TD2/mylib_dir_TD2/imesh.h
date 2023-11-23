#ifndef IMESH_H
#define IMESH_H

class IMesh 
{
public:
    virtual double initial_time() const = 0;
    virtual double final_time() const = 0;
    virtual double time_step() const = 0;
    virtual double initial_position() const = 0;
    virtual double final_position() const = 0;
    virtual double position_step() const = 0;
};

#endif

