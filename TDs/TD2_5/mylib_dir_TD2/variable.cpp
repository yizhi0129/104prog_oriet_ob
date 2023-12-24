#include <iostream>
#include "variable.h"


Variable::Variable(IMesh* mesh)
{
    u_n = 0.0;
    u_np1 = 0.0;
    this->mesh_ = mesh;
    int size = mesh_->x_size();
    this->u_vector = std::vector<double>(size);
    // std::cout << variable[0] << std::endl;
}

double& Variable::operator[](int i) 
{
    return u_vector[i];
}

void Variable::print()
{
    for (int i = 0; i <= mesh_->x_size(); ++ i)
    {
        std::cout << m_name << " u_np1: " << u_np1 << " u_ref: " << u_ref << std::endl;
    }
}
