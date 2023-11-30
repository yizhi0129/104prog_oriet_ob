#include <iostream>
#include "variable.h"

Variable::Variable(IMesh* mesh){
    this->mesh_ = mesh;
    int size = mesh_->x_size();
    this->uvect = std::vector<double>(size);
    // std::cout << variable[0] << std::endl;
}

double& Variable::operator[](int i) {
    return uvect[i];
}
