#include <iostream>

#include "test.h"

int main() {
  TinySTL::Test::test_alloc01();
  TinySTL::Test::test_iterator01();
  TinySTL::Test::test_type_traits();

  return 0;
}