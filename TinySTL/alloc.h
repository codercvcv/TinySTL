#pragma once
#ifndef __ALLOC__
#define __ALLOC__

#include <cstdlib>

namespace TinySTL {
class alloc {
 private:
  enum { ALIGN = 8 };
  enum { NOBJS = 20 };
  enum { MAX_BYTES = 128 };
  enum { NFREELIST = MAX_BYTES / ALIGN };

  struct obj {
    struct obj* next_;
  };

  static size_t FREELIST_INDEX(size_t size) {
    return (size + ALIGN - 1) / ALIGN - 1;
  }

  static size_t ROUND_UP(size_t size) {
    return (size + ALIGN - 1) & ~(ALIGN - 1);
  }

  static char* chunk_alloc(size_t size, size_t& nobjs);
  static void* refill(size_t size);

  static obj* free_list_[NFREELIST];
  static size_t heap_size;
  static char* start_free_;
  static char* end_free_;

 public:
  static void* allocate(size_t size);
  static void deallocate(void* p, size_t size);
};
}  // namespace TinySTL

#endif  // __ALLOC__
