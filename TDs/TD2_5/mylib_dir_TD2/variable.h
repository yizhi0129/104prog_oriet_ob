#ifndef VARIABLE_H
#define VARIABLE_H

#include "imesh.h"
#include <vector>

class Variable
{
    public:
        Variable(IMesh* mesh);
        double& operator[](int i);
        ~Variable() = default;

    private : 
        std::vector<double> uvect;
        IMesh* mesh_;
};

#endif