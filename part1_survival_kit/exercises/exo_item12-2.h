#ifndef EXO_ITEM11_1_H_
#define EXO_ITEM11_1_H_

template<typename T, typename U, typename V>
struct Tuple
{
  T m_t = T{};
  U m_u = U{};
  V m_v = V{};
  void print();
};


#include "exo_item12-2_impl.h"

#endif /* EXO_ITEM11_1_H_ */