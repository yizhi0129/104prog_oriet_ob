#include <iostream>
#include <exception>

void printPositiveInt(int i ) {
  if (i >=0) std::cout << "Int i = " <<i <<std::endl;
  else throw std::runtime_error("A positive int is required in printPositiveInt");
}

int main() {
  try {
    printPositiveInt(1);
    printPositiveInt(-1);
  }
  catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
} 