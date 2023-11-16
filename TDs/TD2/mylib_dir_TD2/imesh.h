#ifndef IMESH_H
#define IMESH_H

class IMesh 
{
public:
    virtual double getInitialTime() const = 0;
    virtual double getFinalTime() const = 0;
    virtual double getTimeStep() const = 0;
    virtual double getInitialPosition() const = 0;
    virtual double getFinalPosition() const = 0;
    virtual double getSpaceStep() const = 0;
};

#endif

