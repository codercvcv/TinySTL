#pragma once
#ifndef __ALLOC_H__
#define __ALLOC_H__

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

  // get the index of free_list as allocate size bytes
  static size_t FREELIST_INDEX(size_t byte) {
    return (byte + ALIGN - 1) / ALIGN - 1;
  }

  // riase bytes to multiple of 8
  static size_t ROUND_UP(size_t byte) {
    return (byte + ALIGN - 1) & ~(ALIGN - 1);
  }

  static char* chunk_alloc(size_t size, size_t& nobjs);
  static void* refill(size_t n);

  static obj* free_list_[NFREELIST];
  static size_t heap_size;
  static char* start_free_;
  static char* end_free_;

 public:
  static void* allocate(size_t size);
  static void deallocate(void* p, size_t size);
};
}  // namespace TinySTL

#endif  // __ALLOC_H__
