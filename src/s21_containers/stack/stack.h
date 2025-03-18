#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_STACK_STACK_H
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_STACK_STACK_H

namespace s21 {

template <typename T>
class Stack {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& newData) : data(newData), next(nullptr) {}
  };

  Node* topNode;

 public:
  Stack();
  Stack(const Stack& other);
  Stack(Stack&& other);
  ~Stack();
  Stack& operator=(const Stack& other);
  bool isEmpty() const;
  size_t size() const;
  void push(const T& item);
  void pop();
  T& top();
  void swap(Stack& other);

  class Iterator {
   private:
    Node* currentNode;

   public:
    Iterator(Node* node);
    T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& other) const;
  };

  Iterator begin() const;
  Iterator end() const;
};

}  // namespace s21

#include "stack.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_STACK_STACK_H
