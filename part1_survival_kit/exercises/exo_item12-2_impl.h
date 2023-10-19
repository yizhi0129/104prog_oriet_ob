#include <iostream>

template<typename T, typename U, typename V>
void Tuple<T,U,V>::print() {
  std::cout << "My tuple contains : " << std::endl;
  std::cout << m_t << " " << m_u << " " << m_v << std::endl;
}
  
  
template<>
void Tuple<int,int,int>::print() {
 std::cout << "My tuple, Made of int, contains : " << std::endl;
 std::cout << m_t << " " << m_u << " " << m_v << std::endl;
}