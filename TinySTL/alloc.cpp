#include "alloc.h"

namespace TinySTL {
char* alloc::start_free_ = nullptr;
char* alloc::end_free_ = nullptr;
size_t alloc::heap_size = 0;
alloc::obj* alloc::free_list_[NFREELIST] = {0, 0, 0, 0, 0, 0, 0, 0,
                                            0, 0, 0, 0, 0, 0, 0, 0};

void* alloc::allocate(size_t size) {
  if (size > MAX_BYTES) {
    return malloc(size);
  }

  size_t index = FREELIST_INDEX(size);
  obj* node = free_list_[index];
  if (node) {
    free_list_[index] = node->next_;
    return node;
  } else {
    return refill(ROUND_UP(size));
  }
}

void alloc::deallocate(void* p, size_t size) {
  if (size > MAX_BYTES) {
    free(p);
  } else {
    size_t index = FREELIST_INDEX(size);
    obj* node = reinterpret_cast<obj*>(p);
    node->next_ = free_list_[index];
    free_list_[index] = node;
  }
}

char* alloc::chunk_alloc(size_t size, size_t& nobjs) {
  size_t total_bytes = size * nobjs;
  size_t bytes_left = start_free_ - end_free_;
  char* result = nullptr;

  if (bytes_left >= total_bytes) {
    result = start_free_;
    start_free_ += total_bytes;
    return result;
  } else if (bytes_left >= size) {
    result = start_free_;
    nobjs = bytes_left / size;
    total_bytes = nobjs * size;
    start_free_ += total_bytes;
    return result;
  } else {
    if (bytes_left > 0) {
      size_t index = FREELIST_INDEX(bytes_left);
      obj* node = reinterpret_cast<obj*>(start_free_);
      node->next_ = free_list_[index];
      free_list_[index] = node;
    }

    size_t bytes_to_get = size * nobjs * 2 + ROUND_UP(heap_size);
    start_free_ = static_cast<char*>(malloc(bytes_to_get));
    if (!start_free_) {
      size_t index = FREELIST_INDEX(size);
      for (size_t i = index + 1; i < NFREELIST; ++i) {
        if (free_list_[i]) {
          start_free_ = reinterpret_cast<char*>(free_list_[i]);
          end_free_ = start_free_ + (i + 1) * ALIGN;
          free_list_[i] = free_list_[i]->next_;
          return chunk_alloc(size, nobjs);
        }
      }
    }

    heap_size += bytes_to_get;
    end_free_ = start_free_ + bytes_to_get;
    return chunk_alloc(size, nobjs);
  }
}

void* alloc::refill(size_t size) {
  size_t nobjs = NOBJS;
  char* chunk = chunk_alloc(size, nobjs);

  if (1 == nobjs) {
    return chunk;
  }

  size_t index = FREELIST_INDEX(size);
  free_list_[index] = reinterpret_cast<obj*>(chunk + size);
  obj* result = reinterpret_cast<obj*>(chunk);
  obj* next_obj = free_list_[index];
  obj* current_obj = nullptr;

  for (size_t i = 1;; ++i) {
    current_obj = next_obj;
    next_obj = reinterpret_cast<obj*>(reinterpret_cast<char*>(next_obj) + size);
    if (i == nobjs - 1) {
      current_obj->next_ = nullptr;
      break;
    } else {
      current_obj->next_ = next_obj;
    }
  }

  return result;
}

}  // namespace TinySTL
