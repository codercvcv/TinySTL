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
 typename iterator_traits<RandomAccessIterator>::difference_type
_distence(RandomAccessIterator first, RandomAccessIterator last,
          random_access_iterator_tag) {
  return last - first;
}

 template <typename Iterator>
 typename iterator_traits<Iterator>::difference_type distance(Iterator first,
                                                             Iterator last) {
  typedef typename iterator_traits<Iterator>::iterator_category category;
  return _distance(first, last, category());
}

}  // namespace TinySTL

#endif  // __ALGORITHM_H__