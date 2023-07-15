#include "ge_vector.hpp"

#include <iostream>

int main()
{
  GE::Pt pt2{ 1.0f, 2.0f };
  GE::Pt pt3{ 1.0f, 2.0f, 3.0f };
  GE::Pt pt4{ 1.0f, 2.0f, 3.0f, 4.0f };
  auto len = pt2.Length();
  std::cout << len << std::endl;
  len = pt3.Length();
  std::cout << len << std::endl;
  len = pt4.Length();
  std::cout << len << std::endl;
  return 0;
}
