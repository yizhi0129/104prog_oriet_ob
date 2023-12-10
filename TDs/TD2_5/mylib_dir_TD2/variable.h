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
        double u_n;
        double u_np1;

    private : 
        std::vector<double> uvect;
        IMesh* mesh_;
};

#endif
