#ifndef VARIABLE_H
#define VARIABLE_H

#include "imesh.h"
#include <vector>
#include <string>

class Variable
{
    public:
        Variable(IMesh* mesh);
        double& operator[](int i);
        double& operator()(int i);
        ~Variable() = default;
        void print();
        Variable() : m_name(""), u_np1(0.0) {};
        Variable(const std::string& name) : m_name(name), u_np1(0.0) {};
        std::string getName() const { return m_name; }

    private : 
        double u_n;
        double u_np1;
        double u_n_2nd_order;
        double u_np1_2nd_order;
        double u_ref;
        std::vector<double> u_vector;
        std::vector<double> u_ref_vector;
        std::vector<double> u_2nd_vector;
        IMesh* mesh_;
        std::string m_name;
};

#endif
