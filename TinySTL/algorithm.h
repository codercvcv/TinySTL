#pragma once
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "iterator.h"

namespace TinySTL {

template <typename InputIterator>
typename iterator_traits<InputIterator>::difference_type _distance(
    InputIterator first, InputIterator last, input_iterator_tag) {
  typename iterator_traits<InputIterator>::difference_type distnece = 0;
  while (first++ != last) {
    ++distnece;
  }
  return distnece;
}

template <typename RandomAccessIterator>
typename iterator_traits<RandomAccessIterator>::difference_type _distence(
    RandomAccessIterator first, RandomAccessIterator last,
    random_access_iterator_tag) {
  return last - first;
}

template <typename Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first,
                                                             Iterator last) {
  typedef typename iterator_traits<Iterator>::iterator_category category;
  return _distance(first, last, category());
}

template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
  for (; first != last; ++first) {
    *first = value;
  }
}

inline void fill(char* first, char* last, const char value) {
  memset(first, static_cast<unsigned char>(value), last - first);
}

inline void fill(wchar_t* first, wchar_t* last, const char value) {
  memset(first, static_cast<unsigned char>(value), last - first);
}

template <typename InputIterator, typename Size, typename T>
InputIterator fill_n(InputIterator first, Size n, const T& value) {
  while (n-- > 0) {
    *first = value;
    ++first;
  }
}

template <typename Size>
char* fill_n(char* first, Size n, const char value) {
  memset(first, static_cast<unsigned char>(value), n);
  return first + n;
}

template <typename Size>
wchar_t* fill_n(wchar_t* first, Size n, const char value) {
  memset(first, static_cast<unsigned char>(value), n);
}

}  // namespace TinySTL

#endif  // __ALGORITHM_H__