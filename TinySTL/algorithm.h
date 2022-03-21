#pragma once
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "iterator.h"

namespace TinySTL {

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type _distance(
    const InputIterator& first, const InputIterator& last,
    input_iterator_tag&) {
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last) {
    ++n;
    ++first;
  }
  return n;
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type _distence(
    const InputIterator& first, const InputIterator& last,
    random_access_iterator_tag&) {
  return last - first;
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type distance(
    const InputIterator& first, const InputIterator& last) {
  typedef typename iterator_traits<InputIterator>::iterator_category category;
  return _distance(first, last, category());
}
}  // namespace TinySTL

#endif  // __ALGORITHM_H__