#include "list.h"

namespace TinySTL {
template <typename T>
list_iterator<T>& list_iterator<T>::operator++() {
  node_ = node_->next_;
  return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator++(int) {
  link_type node = *this;
  ++(*this);
  return node;
}

template <typename T>
list_iterator<T>& list_iterator<T>::operator--() {
  node_ = node_->prev_;
  return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator--(int) {
  link_type node = node_->prev_;
  --(*this);
  return *this;
}

template <typename T>
void list<T>::construct_aux(size_type n, const value_type& value,
                            std::true_type) {
  head_.node_ = new_node();
  tail_.node_ = nullptr;
  while (n--) {
    push_back(value);
  }
}

template <typename T>
template <typename InputIterator>
void list<T>::construct_aux(InputIterator first, InputIterator last,
                            std::false_type) {
  head_.node_ = new_node();
  tail_.node_ = nullptr;
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template <typename T>
list<T>::list() {
  head_.node_ = new_node();
  tail_.node_ = nullptr;
}

template <typename T>
list<T>::list(size_type n, const value_type& value) {
  construct_aux(n, value, std::is_integral<value_type>());
}

template <typename T>
template <typename InputIterator>
list<T>::list(InputIterator first, InputIterator last) {
  construct_aux(first, last, std::is_integral<InputIterator>());
}

template <typename T>
list<T>::list(const list& value) {
  head_.node_ = new_node();
  tail_.node_ = nullptr;
  for (auto node = value.head_.node_; node != value.tail_.node_;
       node = node->next_) {
    push_back(node->data_);
  }
}

template <typename T>
list<T>& list<T>::operator=(const list& node) {
  if (this != &node) {
  }
  return *this;
}

template <typename T>
list<T>::~list() {
  while (head_ != tail_) {
    iterator node = head_++;
    list_allocator::destroy(node.node_);
    list_allocator::deallocate(node.node_);
  }
  list_allocator::deallocate(tail_.node_);
}

template <typename T>
void list<T>::push_back(const value_type& value) {
  link_type node = new_node(value);
  node->prev_ = tail_.node_;
  tail_.node_->next_ = node;
  tail_.node_ = node;
}

template <typename T>
void list<T>::push_front(const value_type& value) {
  link_type node = new_node(value);
  node->next_ = head_.node_;
  head_.node_->prev_ = node;
  head_.node_ = node;
}

template <typename T>
void list<T>::pop_back() {
  link_type node = tail_.node_->prev_;
  node->next_ = nullptr;
  delete_node(tail_.node_);
  tail_.node_ = node;
}

template <typename T>
void list<T>::pop_front() {
  link_type node = head_.node_->next_;
  node->prev_ = nullptr;
  delete_node(head_.node_);
  head_.node_ = node;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  size_type size = 0;
  for (auto first = head_; first != end; ++first) {
    ++size;
  }
  return size;
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {

}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  
}

template <typename T>
typename list<T>::link_type list<T>::new_node(const T& value) {
  link_type node = list_allocator();
  list_allocator::construct(node, list_node<T>(value, nullptr, nullptr));
  return node;
}

template <typename T>
void list<T>::delete_node(link_type node) {
  node->prev_ = node->next_ = nullptr;
  list_allocator::destroy(node);
  list_allocator::deallocate(node);
}

}  // namespace TinySTL
