#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_TPP
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_TPP

#include <initializer_list>

#include "set.h"

namespace s21 {

template <typename Key>
Set<Key>::Set() : tree_() {}

template <typename Key>
Set<Key>::Set(const Set& other) : tree_(other.tree_) {}

template <typename Key>
Set<Key>::Set(Set&& other) noexcept : tree_(std::move(other.tree_)) {}

template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const& items) : tree_() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
Set<Key>::~Set() {}

template <typename Key>
Set<Key>& Set<Key>::operator=(const Set& other) {
  if (this != &other) {
    tree_ = other.tree_;
  }
  return *this;
}

template <typename Key>
Set<Key>& Set<Key>::operator=(Set&& other) noexcept {
  if (this != &other) {
    tree_ = std::move(other.tree_);
  }
  return *this;
}

template <typename Key>
bool Set<Key>::empty() const {
  return tree_.empty();
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::size() const {
  return (size_type)tree_.size();
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const {
  return (size_type)tree_.max_size();
}

template <typename Key>
void Set<Key>::clear() {
  tree_.clear();
}

template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const value_type& value) {
  return tree_.insert(value);
}

template <typename Key>
void Set<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void Set<Key>::swap(Set& other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void Set<Key>::merge(Set& other) {
  tree_.merge(other.tree_);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const value_type& value) {
  return tree_.Find(value);
}

template <typename Key>
bool Set<Key>::contains(const value_type& value) {
  return tree_.contains(value);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() {
  return tree_.end();
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_TPP
