#ifndef WET1__AVLTREE_H_
#define WET1__AVLTREE_H_

#include <iostream>
#include <rpcdce.h>

template<class Key, class Data>
class TreeNode {
  Key key;
  Data data;
  int height;
  TreeNode *rightSon; //  greater values
  TreeNode *leftSon;  //   smaller values

  template<class otherKey, class otherData>// so we won't shadow TreeNode's parameters
  friend
  class AVLTree;

  void setRightSon(TreeNode *son);
  void setLeftSon(TreeNode *son);
  void updateData(Data new_data); // maybe we'll need it
  void setHeight(int new_height);

  const Key &getKey() const; // once created, the key is unchangeable
  Data &getData();
  TreeNode *getRightSon() const;
  TreeNode *getLeftSon() const;
  const int getHeight() const; // may change only by setHeight

 public:
  TreeNode() : key(), data(), height(0), rightSon(nullptr), leftSon(nullptr) {}
  TreeNode(Key key, Data data)
      : key(key),
        data(data),
        height(0),
        rightSon(nullptr),
        leftSon(nullptr) {}
  ~TreeNode() = default;

  void printData() const;
  void printKey() const;
};

/*        IMPLEMENTATION        */

/*
 *      PRIVATE FUNCTIONS
 */

template<class Key, class Data>
void TreeNode<Key, Data>::setRightSon(TreeNode<Key, Data> *son) {
  this->rightSon = son;
}
template<class Key, class Data>
void TreeNode<Key, Data>::setLeftSon(TreeNode<Key, Data> *son) {
  this->leftSon = son;
}
template<class Key, class Data>
void TreeNode<Key, Data>::updateData(Data new_data) {
  this->data = new_data;
}
template<class Key, class Data>
void TreeNode<Key, Data>::setHeight(int new_height) {
  this->height = new_height;
}

template<class Key, class Data>
const Key &TreeNode<Key, Data>::getKey() const {
  return this->key;
}
template<class Key, class Data>
Data &TreeNode<Key, Data>::getData() {
  return this->data;
}
template<class Key, class Data>
TreeNode<Key, Data> *TreeNode<Key, Data>::getRightSon() const {
  return this->rightSon;
}
template<class Key, class Data>
TreeNode<Key, Data> *TreeNode<Key, Data>::getLeftSon() const {
  return this->leftSon;
}
template<class Key, class Data>
const int TreeNode<Key, Data>::getHeight() const {
  return this->height;
}

/*
 *      PUBLIC FUNCTIONS
 */

template<class Key, class Data>
void TreeNode<Key, Data>::printData() const {
  std::cout << this->data << " ";
}
template<class Key, class Data>
void TreeNode<Key, Data>::printKey() const {
  std::cout << this->key << " ";
}

#endif //WET1__AVLTREE_H_
