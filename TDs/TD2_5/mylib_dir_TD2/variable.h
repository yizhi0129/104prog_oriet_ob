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
        void print(std::ostream& os) const;
        Variable() : m_name("") {};
        Variable(const std::string& name) : m_name(name) {};
        std::string getName() const { return m_name; }
        ~Variable() = default;
    private : 
    /*    std::vector<double> u_n;
        std::vector<double> u_np1;
        std::vector<double> u_ref;
        std::vector<double> u_n_2nd_order;
        std::vector<double> u_np1_2nd_order; */
        std::vector<double> u_vector;
        IMesh* mesh_;
        std::string m_name;
};

#endif
