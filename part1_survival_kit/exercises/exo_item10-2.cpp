#include <iostream>

struct A{};

void apply_ref([[maybe_unused]] A& a){
    std::cout << "apply_ref(A&)" << std::endl;
}

void apply_const_ref([[maybe_unused]] A const& a){
    std::cout <<"apply_const_ref(A const& a)" << std::endl;
}

int main() {
    A a{};
    apply_ref(a);
    apply_const_ref(a);
}