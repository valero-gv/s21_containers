#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_H
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_H

#include "../AvlTree/AVLTree.h"

namespace s21 {

template <typename Key>
class Set {
 private:
  AVLTree<Key, bool> tree_;

 public:
  // Public types
  using value_type = Key;
  using size_type = std::size_t;
  using iterator = typename AVLTree<Key, bool>::Iterator;

  // Constructors and destructor
  Set();
  Set(const Set& other);
  Set(Set&& other) noexcept;
  Set(std::initializer_list<value_type> const& items);
  ~Set();

  // Assignment operators
  Set& operator=(const Set& other);
  Set& operator=(Set&& other) noexcept;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(Set& other);
  void merge(Set& other);

  // Lookup
  iterator find(const value_type& value);
  bool contains(const value_type& value);

  // Iterators
  iterator begin();
  iterator end();
};

}  // namespace s21

#include "set.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_SET_SET_H