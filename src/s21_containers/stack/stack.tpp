#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_STACK_STACK_TPP
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_STACK_STACK_TPP

#include <stdexcept>

#include "stack.h"

namespace s21 {

template <typename T>
Stack<T>::Stack() : topNode(nullptr) {}

template <typename T>
Stack<T>::Stack(const Stack& other) : topNode(nullptr) {
  if (!other.isEmpty()) {
    topNode = new Node(other.topNode->data);
    Node* thisCurrent = topNode;
    Node* otherCurrent = other.topNode->next;
    while (otherCurrent != nullptr) {
      thisCurrent->next = new Node(otherCurrent->data);
      thisCurrent = thisCurrent->next;
      otherCurrent = otherCurrent->next;
    }
  }
}

template <typename T>
Stack<T>::Stack(Stack&& other) : topNode(other.topNode) {
  other.topNode = nullptr;
}

template <typename T>
Stack<T>::~Stack() {
  while (!isEmpty()) {
    pop();
  }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if (this != &other) {
    while (!isEmpty()) {
      pop();
    }

    if (!other.isEmpty()) {
      topNode = new Node(other.topNode->data);
      Node* thisCurrent = topNode;
      Node* otherCurrent = other.topNode->next;
      while (otherCurrent != nullptr) {
        thisCurrent->next = new Node(otherCurrent->data);
        thisCurrent = thisCurrent->next;
        otherCurrent = otherCurrent->next;
      }
    }
  }
  return *this;
}

template <typename T>
bool Stack<T>::isEmpty() const {
  return topNode == nullptr;
}

template <typename T>
void Stack<T>::push(const T& item) {
  Node* newNode = new Node(item);
  newNode->next = topNode;
  topNode = newNode;
}

template <typename T>
void Stack<T>::pop() {
  if (isEmpty()) {
    throw std::out_of_range("Stack<>::pop(): empty stack");
  }
  Node* temp = topNode;
  topNode = topNode->next;
  delete temp;
}

template <typename T>
size_t Stack<T>::size() const {
  size_t count = 0;
  Node* current = topNode;
  while (current != nullptr) {
    ++count;
    current = current->next;
  }
  return count;
}

template <typename T>
T& Stack<T>::top() {
  if (isEmpty()) {
    throw std::out_of_range("Stack<>::top(): empty stack");
  }
  return topNode->data;
}

template <typename T>
void Stack<T>::swap(Stack& other) {
  std::swap(topNode, other.topNode);
}

template <typename T>
Stack<T>::Iterator::Iterator(Node* node) : currentNode(node) {}

template <typename T>
T& Stack<T>::Iterator::operator*() const {
  return currentNode->data;
}

template <typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator++() {
  currentNode = currentNode->next;
  return *this;
}

template <typename T>
bool Stack<T>::Iterator::operator!=(
    const typename Stack<T>::Iterator& other) const {
  return currentNode != other.currentNode;
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const {
  return Iterator(topNode);
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const {
  return Iterator(nullptr);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_STACK_STACK_TPP
