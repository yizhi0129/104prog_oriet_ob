#include <iostream>
#include "variable.h"

Variable::Variable(IMesh* mesh){
    u_n = 0.0;
    u_np1 = 0.0;
    this->mesh_ = mesh;
    int size = mesh_->x_size();
    this->uvect = std::vector<double>(size);
    // std::cout << variable[0] << std::endl;
}

double& Variable::operator[](int i) {
    return uvect[i];
}
