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


void Variable::print()
{
    for (int i = 0; i < mesh_->x_size(); ++ i)
    {
        std::cout << m_name << " " << u_vector[i] << std::endl;
    }
}
