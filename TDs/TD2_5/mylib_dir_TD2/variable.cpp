#include <iostream>
#include "variable.h"

Variable::Variable(IMesh* mesh)
{
    this->mesh_ = mesh;
    int size = mesh_->x_size();
    this->u_vector = std::vector<double>(size);
}

double& Variable::operator[](int i) 
{
    return u_vector[i];
}


void Variable::print() const {
    std::for_each(u_vector.begin(), u_vector.end(), [](const double& val) {
        std::cout << val << std::endl;
    });
}
