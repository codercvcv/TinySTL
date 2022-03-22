#pragma once
#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

namespace TinySTL {
struct true_type {};
struct false_type {};

template <typename T>
struct type_traits {
  typedef false_type has_trivial_default_constructor;
  typedef false_type has_trivial_copy_constructor;
  typedef false_type has_trivial_assignment_operator;
  typedef false_type has_trivial_destructor;
  typedef false_type is_POD_type;
};

template <>
struct type_traits<bool> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<char> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<signed char> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned char> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<wchar_t> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<short> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned short> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<int> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned int> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<long> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<long long> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned long> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<unsigned long long> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<float> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <typename T>
struct type_traits<T*> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <typename T>
struct type_traits<const T*> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <>
struct type_traits<char*> {
  typedef true_type has_trivial_default_constructor;
  typedef true_type has_trivial_copy_constructor;
  typedef true_type has_trivial_assignment_operator;
  typedef true_type has_trivial_destructor;
  typedef true_type is_POD_type;
};

template <typename T>
struct remove_const {
  typedef T type;
};

template <typename T>
struct remove_const<T const> {
  typedef T type;
};

template <typename T>
struct remove_volatile {
  typedef T type;
};

template <typename T>
struct remove_volatile<T volatile> {
  typedef T type;
};

template <typename T>
struct remove_cv {
  typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

template <typename T>
struct is_void_helper : public false_type {};

template <>
struct is_void_helper<void> : public true_type {};

template <typename T>
struct is_void : public is_void_helper<typename remove_cv<T>::type> {};

}  // namespace TinySTL

#endif  // ____TYPE_TRAITS_H__