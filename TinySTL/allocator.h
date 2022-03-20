#pragma once
#ifndef __ALLOCATOR__
#define __ALLOCATOR__

#include <cstddef>

#include "alloc.h"

namespace TinySTL {
template <typename T>
class allocator {
 public:
  using difference_type = ptrdiff_t;
  using const_reference = const T&;
  using value_type = T;
  using reference = T&;
  using pointer = T*;

  static pointer allocate() {
    return static_cast<pointer>(alloc::allocate(sizeof(value_type)));
  }

  static pointer allocate(size_t n) {
    return static_cast<pointer>(alloc::allocate(sizeof(value_type) * n));
  }

  static void deallocate(pointer p) {
    alloc::deallocate(p, sizeof(value_type));
  }

  static void deallocate(pointer p, size_t n) {
    if (0 == n) return;
    alloc::deallocate(p, sizeof(value_type) * n);
  }

  static void construct(pointer p) { new (p) value_type(); }
  static void construct(pointer p, const_reference value) {
    new (p) value_type(value);
  }

  static destroy(pointer p) { p->~value_type(); }

  static destroy(pointer first, pointer last) {
    while (first != last) {
      (first++)->~value_type();
    }
  }
};
}  // namespace TinySTL

#endif  // __ALLOCATOR__
