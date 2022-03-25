#pragma once
#ifndef __LIST_H__
#define __LIST_H__

#include "allocator.h"
#include "iterator.h"
#include "type_traits.h"

namespace TinySTL {
template <typename T>
struct list_node {
  T data_;
  struct list_node* prev_;
  struct list_node* next_;
  list_node(const T& data, list_node* prev, list_node* next)
      : data_(data), prev_(prev), next_(next) {}
  bool operator==(const list_node& node) {
    return node.data == data_ && node.prev == prev_ && node.next == next_;
  }
};

template <typename T>
struct list_iterator : public iterator<bidirectional_iterator_tag, T> {
  typedef list_node<T>* link_type;
  link_type node_;

  explicit list_iterator(link_type node = nullptr) : node_(node) {}

  list_iterator& operator++();
  list_iterator& operator--();
  list_iterator operator++(int);
  list_iterator operator--(int);
  T& operator*() { return node_->data_; }
  T* operator->() { return &(operator*()); }

  template <typename T>
  friend bool operator==(const list_iterator<T>& lhs,
                         const list_iterator<T>& rhs) {
    return lhs.node_ == rhs.node_;
  }
  template <typename T>
  friend bool operator!=(const list_iterator<T>& lhs,
                         const list_iterator<T>& rhs) {
    return !(lhs.node_ == rhs.node_);
  }
};

template <typename T>
class list {
 private:
  typedef allocator<list_node<T>> list_allocator;
  typedef list_node<T>* link_type;

 public:
  typedef list_iterator<const T> const_iterator;
  typedef list_iterator<T> iterator;
  typedef size_t size_type;
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;

 private:
  iterator head_;
  iterator tail_;

 public:
  list();
  list(size_type n, const value_type& value);
  template <typename InputIterator>
  list(InputIterator first, InputIterator last);
  list(const list& node);
  list& operator=(const list& node);
  ~list();

  void push_back(const value_type& value);
  void push_front(const value_type& value);
  void pop_back();
  void pop_front();

  bool empty() const { return head_ == tail_; }
  reference front() { return head_.node_->data_; }
  reference back() { return tail_.node_->data_; }
  size_type size() const;

  iterator begin() { return head_; }
  iterator end() { return tail_; }
  const_iterator begin() const;
  const_iterator end() const;

  iterator insert(iterator position, const value_type& value);
  void insert(iterator position, size_type n, const value_type& value);
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last);
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);

 private:
  link_type new_node(const T& value = T());
  void delete_node(link_type node);
  void construct_aux(size_type n, const value_type& value, std::true_type);
  template <typename InputIterator>
  void construct_aux(InputIterator first, InputIterator last, std::false_type);
};
}  // namespace TinySTL

#endif  // __LIST_H__