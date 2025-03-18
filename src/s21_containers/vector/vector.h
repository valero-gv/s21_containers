
#include <cmath>
#include <iostream>

namespace s21 {
template <typename T>
class Iterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using size_type = std::size_t;

  Iterator(const Iterator& iter);
  Iterator(pointer value);
  Iterator<value_type>& operator=(const Iterator& iter);
  Iterator<value_type>& operator=(Iterator&& iter);

  bool operator!=(const Iterator& other) const;
  bool operator==(const Iterator& other) const;
  bool operator>(const Iterator& other) const;
  bool operator>=(const Iterator& other) const;
  bool operator<(const Iterator& other) const;
  bool operator<=(const Iterator& other) const;
  pointer operator->();
  reference operator*() const;
  Iterator& operator++();
  Iterator& operator--();
  Iterator& operator++(int);
  Iterator& operator--(int);
  Iterator operator+(size_type value) const;
  Iterator operator-(size_type value) const;
  Iterator& operator+=(size_type value);
  Iterator& operator-=(size_type index);
  size_type operator-(const Iterator& other) const;

 private:
  pointer val;
};

template <typename T>
class ConstIterator {
 public:
  using value_type = T;
  using reference = T&;
  using pointer = T*;
  using const_pointer = const T*;
  using size_type = std::size_t;

  ConstIterator(const ConstIterator& iter);
  ConstIterator(pointer value);
  ConstIterator(const_pointer value);

  bool operator!=(const ConstIterator& other) const;
  bool operator==(const ConstIterator& other) const;
  bool operator>(const ConstIterator& other) const;
  bool operator>=(const ConstIterator& other) const;
  bool operator<(const ConstIterator& other) const;
  bool operator<=(const ConstIterator& other) const;
  pointer operator->();
  value_type operator*() const;
  ConstIterator& operator++();
  ConstIterator& operator--();
  ConstIterator& operator++(int);
  ConstIterator& operator--(int);
  ConstIterator operator+(size_type value) const;
  ConstIterator operator-(size_type value) const;
  ConstIterator& operator+=(size_type value);
  ConstIterator& operator-=(size_type index);
  size_type operator-(const ConstIterator& other) const;

 private:
  const_pointer val;
};

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = Iterator<T>;
  using const_iterator = ConstIterator<T>;
  using size_type = std::size_t;
  using pointer = T*;

  vector();
  vector(size_type size_vec);
  vector(const vector<value_type>& other);
  vector(vector<value_type>&& other) noexcept;
  vector(std::initializer_list<value_type> other);
  ~vector();
  vector<value_type>& operator=(vector<value_type>&& other) noexcept;

  reference at(size_type place) const;
  reference operator[](size_type i) const;
  reference at(size_type place);
  reference operator[](size_type i);
  const_reference front() const;
  const_reference back() const;
  reference front();
  reference back();
  pointer data();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type count);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(value_type new_value);
  void pop_back();
  void swap(vector<value_type>& other);

 private:
  pointer arr;
  size_type m_size;
  size_type m_capacity;

  void change_capacity();
  void free_vector();
  void copy_vector(const vector<value_type>& other);
  void init_list_copy(std::initializer_list<value_type> other);
};

template <typename value_type>
vector<value_type>::vector() : arr(nullptr), m_size(0), m_capacity(0) {}

template <typename value_type>
vector<value_type>::vector(size_type size_vec) {
  if (size_vec > this->max_size()) {
    throw std::out_of_range("can't create vector larger then max_size()");
  }
  arr = new value_type[size_vec];
  m_size = size_vec;
  m_capacity = size_vec;
  for (size_type i = 0; i < m_size; i++) {
    arr[i] = 0;
  }
}
template <typename value_type>
vector<value_type>::vector(const vector<value_type>& other) {
  copy_vector(other);
}

template <typename value_type>
vector<value_type>::vector(vector<value_type>&& other) noexcept
    : arr(nullptr), m_size(0), m_capacity(0) {
  std::swap(this->arr, other.arr);
  std::swap(this->m_size, other.m_size);
  std::swap(this->m_capacity, other.m_capacity);
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> other) {
  init_list_copy(other);
}

template <typename value_type>
vector<value_type>::~vector() {
  free_vector();
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(
    vector<value_type>&& other) noexcept {
  if (this != &other) {
    free_vector();
    std::swap(this->arr, other.arr);
    std::swap(this->m_size, other.m_size);
    std::swap(this->m_capacity, other.m_capacity);
  }
  return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type place) {
  if (place >= m_size) {
    throw std::out_of_range("Out of range exception");
  }
  return arr[place];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(
    size_type place) const {
  if (place >= m_size) {
    throw std::out_of_range("Out of range exception");
  }
  return arr[place];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type i) {
  if (i >= m_size) {
    throw std::out_of_range("Out of range exception");
  }
  return arr[i];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type i) const {
  if (i >= m_size) {
    throw std::out_of_range("Out of range exception");
  }
  return arr[i];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::front() {
  if (m_size == 0) {
    throw std::out_of_range("vector size is zero");
  }
  return arr[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  if (m_size == 0) {
    throw std::out_of_range("vector size is zero");
  }
  return arr[0];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::back() {
  if (m_size == 0) {
    throw std::out_of_range("vector size is zero");
  }
  return arr[m_size - 1];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  if (m_size == 0) {
    throw std::out_of_range("vector size is zero");
  }
  return arr[m_size - 1];
}

template <typename value_type>
typename vector<value_type>::pointer vector<value_type>::data() {
  return arr;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(arr);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator((arr + m_size));
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cbegin() const {
  return const_iterator(arr);
}

template <typename value_type>
typename vector<value_type>::const_iterator vector<value_type>::cend() const {
  return const_iterator((arr + m_size));
}

template <typename value_type>
bool vector<value_type>::empty() const {
  return m_size > 0 ? false : true;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() const {
  return m_size;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() const {
  int bits = 0;
  size_type res = 0;
#if defined(__LP64__) || defined(_M_IA64)
  bits = 63;
#else
  bits = 31;
#endif
  if (bits == 63) {
    res = static_cast<size_type>(pow(2, 63)) / sizeof(int) - 1;
  } else {
    res = static_cast<size_type>(pow(2, 31)) / sizeof(int) - 1;
  }
  return res;
}

template <typename value_type>
void vector<value_type>::reserve(size_type count) {
  long int temp = count;
  if (temp < 0) {
    throw std::length_error("This memory out of range");
  }
  if (count > m_capacity) {
    pointer arr1 = new value_type[count];
    m_capacity = count;
    for (size_type i = 0; i < m_size; i++) {
      arr1[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = arr1;
  }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() const {
  return m_capacity;
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  pointer new_arr = new value_type[m_size];
  std::copy(arr, arr + m_size, new_arr);
  delete[] arr;
  arr = new_arr;
  m_capacity = m_size;
}

template <typename value_type>
void vector<value_type>::clear() {
  delete[] arr;
  arr = new value_type[m_capacity];
  m_size = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const const_reference value) {
  size_type position = pos - begin();
  if (position > m_size) {
    throw std::out_of_range("Position is out of range");
  }
  if (m_size == m_capacity) {
    change_capacity();
  }
  iterator new_it = begin() + position;
  for (auto i = end(); i != new_it; --i) {
    *i = *(i - 1);
  }
  *new_it = value;
  m_size += 1;
  return new_it;
}

template <typename value_type>
void vector<value_type>::erase(vector<value_type>::iterator pos) {
  size_type position = pos - begin();
  if (position > m_size) {
    throw std::out_of_range("Position is out of range");
  }
  value_type tmp = arr[m_size - 1];
  for (auto i = m_size - 1; i > position; i--) {
    value_type prev = arr[i - 1];
    arr[i - 1] = tmp;
    tmp = prev;
  }
  m_size -= 1;
}

template <typename value_type>
void vector<value_type>::push_back(value_type new_value) {
  if (m_size >= m_capacity) {
    change_capacity();
  }
  arr[m_size++] = new_value;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (m_size > 0) {
    m_size--;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector<value_type>& other) {
  std::swap(this->arr, other.arr);
  std::swap(this->m_size, other.m_size);
  std::swap(this->m_capacity, other.m_capacity);
}

template <typename value_type>
void vector<value_type>::change_capacity() {
  if (m_capacity == 0) {
    arr = new value_type[1];
    m_capacity = 1;
  } else {
    pointer arr1 = new value_type[m_size * 2];
    m_capacity = m_size * 2;
    std::copy(arr, arr + m_size, arr1);
    delete[] arr;
    arr = arr1;
  }
}

template <typename value_type>
void vector<value_type>::free_vector() {
  delete[] arr;
  m_size = 0;
  m_capacity = 0;
  arr = nullptr;
}

template <typename value_type>
void vector<value_type>::copy_vector(const vector<value_type>& other) {
  this->m_size = other.size();
  this->arr = new value_type[this->m_size];
  for (size_type i = 0; i < m_size; i++) {
    this->arr[i] = other.at(i);
  }
  this->m_capacity = m_size;
}

template <typename value_type>
void vector<value_type>::init_list_copy(
    std::initializer_list<value_type> other) {
  arr = new value_type[other.size()];
  m_size = other.size();
  m_capacity = m_size;
  std::copy(other.begin(), other.end(), arr);
}

template <typename value_type>
Iterator<value_type>::Iterator(pointer value) : val(value) {}

template <typename value_type>
Iterator<value_type>::Iterator(const Iterator& iter) : val(iter.val) {}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator=(
    const Iterator<value_type>& iter) {
  this->val = iter.val;
  return *this;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator=(
    Iterator<value_type>&& iter) {
  this->val = nullptr;
  std::swap(this->val, iter.val);
  return *this;
}

template <typename value_type>
bool Iterator<value_type>::operator!=(const Iterator& other) const {
  return val != other.val;
}

template <typename value_type>
bool Iterator<value_type>::operator==(const Iterator& other) const {
  return val == other.val;
}

template <typename value_type>
bool Iterator<value_type>::operator>(const Iterator& other) const {
  return val > other.val;
}

template <typename value_type>
bool Iterator<value_type>::operator>=(const Iterator& other) const {
  return val >= other.val;
}

template <typename value_type>
bool Iterator<value_type>::operator<(const Iterator& other) const {
  return val < other.val;
}

template <typename value_type>
bool Iterator<value_type>::operator<=(const Iterator& other) const {
  return val <= other.val;
}

template <typename value_type>
typename Iterator<value_type>::reference Iterator<value_type>::operator*()
    const {
  return *val;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator++() {
  ++val;
  return *this;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator--() {
  --val;
  return *this;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator++(int) {
  val++;
  return *this;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator--(int) {
  val++;
  return *this;
}

template <typename value_type>
Iterator<value_type> Iterator<value_type>::operator-(size_type value) const {
  Iterator<value_type> iter(*this);
  for (size_type i = 0; i < value; i++) {
    --iter;
  }
  return iter;
}

template <typename value_type>
Iterator<value_type> Iterator<value_type>::operator+(size_type value) const {
  Iterator<value_type> iter(*this);
  for (size_type i = 0; i < value; i++) {
    ++iter;
  }
  return iter;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator+=(size_type value) {
  for (size_type i = 0; i < value; i++) {
    ++val;
  }
  return *this;
}

template <typename value_type>
Iterator<value_type>& Iterator<value_type>::operator-=(size_type value) {
  for (size_type i = 0; i < value; i++) {
    --val;
  }
  return *this;
}

template <typename value_type>
typename Iterator<value_type>::size_type Iterator<value_type>::operator-(
    const Iterator<value_type>& other) const {
  return val - other.val;
}

template <typename value_type>
typename Iterator<value_type>::pointer Iterator<value_type>::operator->() {
  return val;
}

template <typename value_type>
ConstIterator<value_type>::ConstIterator(pointer value) : val(value) {}

template <typename value_type>
ConstIterator<value_type>::ConstIterator(const_pointer value) : val(value) {}

template <typename value_type>
ConstIterator<value_type>::ConstIterator(const ConstIterator& iter)
    : val(iter.val) {}

template <typename value_type>
bool ConstIterator<value_type>::operator!=(const ConstIterator& other) const {
  return val != other.val;
}

template <typename value_type>
bool ConstIterator<value_type>::operator==(const ConstIterator& other) const {
  return val == other.val;
}

template <typename value_type>
bool ConstIterator<value_type>::operator>(const ConstIterator& other) const {
  return val > other.val;
}

template <typename value_type>
bool ConstIterator<value_type>::operator>=(const ConstIterator& other) const {
  return val >= other.val;
}

template <typename value_type>
bool ConstIterator<value_type>::operator<(const ConstIterator& other) const {
  return val < other.val;
}

template <typename value_type>
bool ConstIterator<value_type>::operator<=(const ConstIterator& other) const {
  return val <= other.val;
}

template <typename value_type>
typename ConstIterator<value_type>::value_type
ConstIterator<value_type>::operator*() const {
  return *val;
}

template <typename value_type>
ConstIterator<value_type>& ConstIterator<value_type>::operator++() {
  ++val;
  return *this;
}

template <typename value_type>
ConstIterator<value_type>& ConstIterator<value_type>::operator--() {
  --val;
  return *this;
}

template <typename value_type>
ConstIterator<value_type>& ConstIterator<value_type>::operator++(int) {
  val++;
  return *this;
}

template <typename value_type>
ConstIterator<value_type>& ConstIterator<value_type>::operator--(int) {
  val++;
  return *this;
}

template <typename value_type>
ConstIterator<value_type> ConstIterator<value_type>::operator-(
    size_type value) const {
  ConstIterator<value_type> iter(*this);
  for (int i = 0; i < value; i++) {
    --iter;
  }
  return iter;
}

template <typename value_type>
ConstIterator<value_type> ConstIterator<value_type>::operator+(
    size_type value) const {
  ConstIterator<value_type> iter(*this);
  for (size_type i = 0; i < value; i++) {
    ++iter;
  }
  return iter;
}

template <typename value_type>
ConstIterator<value_type>& ConstIterator<value_type>::operator+=(
    size_type value) {
  for (size_type i = 0; i < value; i++) {
    ++val;
  }
  return *this;
}

template <typename value_type>
ConstIterator<value_type>& ConstIterator<value_type>::operator-=(
    size_type value) {
  for (size_type i = 0; i < value; i++) {
    --val;
  }
  return *this;
}

template <typename value_type>
typename ConstIterator<value_type>::size_type
ConstIterator<value_type>::operator-(
    const ConstIterator<value_type>& other) const {
  return val - other.val;
}

template <typename value_type>
typename ConstIterator<value_type>::pointer
ConstIterator<value_type>::operator->() {
  return val;
}

}  // namespace s21
