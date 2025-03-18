#ifndef CPP2_S21_CONTAINERS_S21_CONTAINERS_AVLTREE_AVLTREE_H_
#define CPP2_S21_CONTAINERS_S21_CONTAINERS_AVLTREE_AVLTREE_H_

#include <linux/sysctl.h>
#include <sys/types.h>

#include <iostream>

template <typename Key, typename Value>
class AVLTree {
 protected:
  struct Node;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* past_node = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator& it);
    friend class AVLTree<Key, Value>;
    bool operator!=(const iterator& it);

   protected:
    Node* iter_node_;  // посмотреть куда пихнуть. протектед или приват
    Node* iter_past_node_;
    Node* MoveForward(Node* node);
    Node* MoveBack(Node* node);
  };
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
    const_reference operator-() const { return Iterator::operator-(); };
  };

  AVLTree();
  AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other) noexcept;
  ~AVLTree();
  AVLTree& operator=(AVLTree&& other) noexcept;
  AVLTree& operator=(const AVLTree& other);
  iterator begin();
  iterator end();
  bool empty() const;
  size_type size() const;
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key& key);
  void erase(iterator pos);
  void swap(AVLTree& other);
  void merge(AVLTree& other);
  bool contains(const Key& key);
  iterator Find(const Key& key);

 protected:
  struct Node {
    Node(Key key, value_type value);
    Node(Key key, value_type value, Node* parent);
    Key key_;
    value_type value_;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node* parent_ = nullptr;
    int height_ = 0;
    friend class AVLTree<Key, Value>;
  };
  Node* root_;
  // SUPPORT FOR CONSTRUCTORS
  void FreeNode(Node* node);
  Node* CopyTree(Node* node, Node* parent);
  // AVL BALANCE
  void SwapValue(Node* a, Node* b);  // swap only key and value
  void RightRotate(Node* node);
  void LeftRotate(Node* node);
  void Balance(Node* node);
  int GetBalance(Node* node);
  int GetHeight(Node* node);
  void SetHeight(Node* node);
  // MIN && MAX
  static Node* GetMin(Node* node);
  static Node* GetMax(Node* node);
  // RECURSIVE SUPPORT FUNCTIONS
  bool RecursiveInsert(Node* node, const Key& key, Value value);
  Node* RecursiveDelete(Node* node, Key key);
  size_t RecursiveSize(Node* node) const;
  Node* RecursiveFind(Node* node, const Key& key) const;
};

#include "AVLTree.tpp"
#endif  // CPP2_S21_CONTAINERS_S21_CONTAINERS_AVLTREE_AVLTREE_H_