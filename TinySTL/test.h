#pragma once
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>

#include "algorithm.h"
#include "allocator.h"
#include "iterator.h"
#include "type_traits.h"

namespace TinySTL {
const size_t MAX_OBJS = 0x0001 << 4;
namespace Test {
void test_alloc01() {
  int* arr_pint[MAX_OBJS];
  for (size_t i = 0; i < MAX_OBJS; ++i) {
    arr_pint[i] = TinySTL::allocator<int>::allocate();
    std::cout << "allocator_addr:\t" << arr_pint[i] << std::endl;
  }
}

void test_iterator01() {
  int* arr_pint[MAX_OBJS];
  for (size_t i = 0; i < MAX_OBJS; ++i) {
    arr_pint[i] = TinySTL::allocator<int>::allocate();
  }

  std::cout << "distance: " << distance(arr_pint[0], arr_pint[5]) << std::endl;
}

void _type_traits(true_type) { std::cout << "is void type" << std::endl; }
void _type_traits(false_type) { std::cout << "is not void type" << std::endl; }

void test_type_traits() {
  _type_traits(is_void<void>());
  _type_traits(is_void<int>());
}
}  // namespace Test

}  // namespace TinySTL

#endif  // _TEST_H_
