#pragma once
#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>

namespace TinySTL {
class input_iterator_tag {};
class output_iterator_tag {};
class forward_iterator_tag : public input_iterator_tag {};
class bidirectional_iterator_tag : public forward_iterator_tag {};
class random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T, typename Distance = ptrdiff_t>
class input_iterator {
 public:
  typedef input_iterator_tag iterator_category;
  typedef Distance difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
};

template <typename T, typename Distance = ptrdiff_t>
class output_iterator {
 public:
  typedef output_iterator_tag iterator_category;
  typedef void difference_type;
  typedef void value_type;
  typedef void reference;
  typedef void pointer;
};

template <typename T, typename Distance = ptrdiff_t>
class forward_iterator {
  typedef forward_iterator_tag iterator_category;
  typedef Distance difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
};

template <typename T, typename Distance = ptrdiff_t>
class bidirection_iterator {
 public:
  typedef bidirectional_iterator_tag iterator_category;
  typedef Distance difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
};

template <typename T, typename Distance = ptrdiff_t>
class random_access_iterator {
 public:
  typedef random_access_iterator_tag iterator_category;
  typedef Distance difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
};

template <typename Category, typename T, typename Distance = ptrdiff_t>
class iterator {
 public:
  typedef Category iterator_category;
  typedef Distance difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
};

template <typename Iterator>
class iterator_traits {
 public:
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::pointer pointer;
};

template <typename T>
struct iterator_traits<T*> {
 public:
  typedef random_access_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
};

template <typename T>
class iterator_traits<const T*> {
 public:
  typedef random_access_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T& reference;
  typedef const T* pointer;
};

template <typename Iterator>
typename iterator_traits<Iterator>::iterator_category iterator_category(
    const Iterator&) {
  typedef typename iterator_traits<Iterator>::iterator_category category;
  return category();
}

template <typename Iterator>
typename iterator_traits<Iterator>::value_type* value_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::value_type*>(nullptr);
}

template <typename Iterator>
typename iterator_traits<Iterator>::difference_type* difference_type(
    const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::differencetype*>(
      nullptr);
}

}  // namespace TinySTL

#endif  // __ITERATOR_H__