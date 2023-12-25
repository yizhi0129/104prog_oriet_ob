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
            // ~Variable() = default; // Remove this line
            void print();
            Variable() : m_name(""), u_np1(0.0) {};
            Variable(const std::string& name) : m_name(name), u_np1(0.0) {};
            std::string getName() const { return m_name; }

        private : 
            std::vector<double> u_n;
            std::vector<double> u_np1;
            std::vector<double> u_ref;
            std::vector<double> u_n_2nd_order;
            std::vector<double> u_np1_2nd_order;
            IMesh* mesh_;
        std::string m_name;
};

#endif
