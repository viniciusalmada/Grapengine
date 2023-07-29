#include "ge_application.hpp"

#include <iostream>

int main()
{
  Application application{ "Graphic Engine", 512, 512 };

  application.Run();
  return 0;
}
