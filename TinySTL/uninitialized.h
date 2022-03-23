#pragma once
#ifndef __UNINITIALIZED_H__
#define __UNINITIALIZED_H__

#include "allocator.h"
#include "iterator.h"
#include "type_traits.h"

namespace TinySTL {
template <typename InputIterator, typename ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                        ForwardIterator result, true_type) {
  memcpy(result, first, sizeof(*first) * (last - first));
  return result;
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                        ForwardIterator result, false_type) {
  size_t i = 0;
  for (; first != last; ++first, ++i) {
    construct(result + i, *first);
  }
  return result + i;
}

template <typename InputIterator, typename ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
                                   ForwardIterator result) {
  typedef typename type_traits<
      iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
  _uninitialized_copy_aux(first, last, result, is_POD_type());
}

template <typename InputIterator, typename T>
void _uninitialized_fill_aux(InputIterator first, InputIterator last,
                             const T& value, true_type) {
  fill(first, last, value);
}

template <typename InputIterator, typename T>
void _uninitialized_fill_aux(InputIterator first, InputIterator last,
                             const T& value, false_type) {
  while (first != last) {
    construct(first++, value);
  }
}

template <typename InputIterator, typename T>
void uninitialized_fill(InputIterator first, InputIterator last,
                        const T& value) {
  typedef typename type_traits<T>::is_POD_type is_POD_type;
  _uninitialized_fill_aux(first, last, value, is_POD_type());
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                          const T& value, true_type) {
  return fill_n(first, n, value);
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n,
                                          const T& value, false_type) {
  size_t i = 0;
  for (; first != last; ++i) {
    construct(reinterpret_cast<T*>(first + i), value);
  }
  return first + i;
}

template <typename ForwardIterator, typename Size, typename T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
                                     const T& value) {
  typedef typename type_traits<T>::is_POD_type is_POD_type;
  return _uninitialized_fill_n_aux(first, last, n, is_POD_type());
}
}  // namespace TinySTL

#endif  // __UNINITIALIZED_H__
