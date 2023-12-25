#include <iostream>
#include "variable.h"

Variable::Variable(IMesh* mesh)
{
    this->mesh_ = mesh;
    int size = mesh_->x_size();
    this->u_n = std::vector<double>(size);
    this->u_np1 = std::vector<double>(size);
    this->u_ref = std::vector<double>(size); 
    this->u_n_2nd_order = std::vector<double>(size);
    this->u_np1_2nd_order = std::vector<double>(size);
}

double& Variable::operator[](int i) 
{
    return u_n[i];
}


void Variable::print()
{
    for (int i = 0; i < mesh_->x_size(); ++ i)
    {
        std::cout << m_name << " u_np1: " << u_n[i] << "u_np1_2nd_order:" << u_n_2nd_order[i] << " u_ref: " << u_ref[i] << std::endl;
    }
}
