#ifndef WET1__AVLTREE_H_
#define WET1__AVLTREE_H_

#include <iostream>

#define BALANCED_R 1
#define NOT_BALANCED_R -2
#define BALANCED_L -1
#define NOT_BALANCED_L 2
#define EMPTY_HEIGHT -1 //if one of the sons is nullptr

/*
 *  TreeNode
 */


template<class Key, class Data>
class TreeNode {
  Key key;
  Data data;
  int height;
  TreeNode *parent;
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
  TreeNode *getParent() const;
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
TreeNode<Key, Data> *TreeNode<Key, Data>::getParent() const {
  return this->parent;
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

/*
 * AVLTree
 */

typedef enum AVLTreeResult {
  AVL_SUCCESS,
  AVL_KeyAlreadyExists,
  AVL_KeyNotFound
} AVLTreeResult;
typedef enum AVLTreeOrderKind { Pre, In, Post, Rev } AVLTreeOrderKind;

template<class Key, class Data>
class AVLTree {
  TreeNode<Key, Data> *root;
  void setRoot(TreeNode<Key, Data> *tree_node);
  void cleanTree(TreeNode<Key, Data> *tree_node);

  void printPreOrder(TreeNode<Key, Data> *tree_node) const;
  void printInOrder(TreeNode<Key, Data> *tree_node) const;
  void printPostOrder(TreeNode<Key, Data> *tree_node) const;

  AVLTreeResult updateData(const Key &key, Data &data);
  TreeNode<Key, Data> *findNodeInTree(const Key &key,
                                      TreeNode<Key, Data> *tree_node);

  int heightDifference(TreeNode<Key, Data> *tree_node);
  void swapBetweenNodes(TreeNode<Key, Data> *first_node,
                        TreeNode<Key, Data> *second_node);
  void updateTreeNodeHeight(TreeNode<Key, Data> *tree_node);
  TreeNode<Key, Data> *AVLTreeBalance(TreeNode<Key, Data> *tree_node);
  TreeNode<Key, Data> *LLrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);
  TreeNode<Key, Data> *LRrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);
  TreeNode<Key, Data> *RLrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);
  TreeNode<Key, Data> *RRrotation(TreeNode<Key, Data> *parent,
                                  TreeNode<Key, Data> *son);


};

/*        IMPLEMENTATION        */

/*
 *      PRIVATE FUNCTIONS
 */

template<class Key, class Data>
void AVLTree<Key, Data>::setRoot(TreeNode<Key, Data> *tree_node) {
  if (tree_node == nullptr) {
    return;
  }
  this->root = tree_node;
}
template<class Key, class Data>
void AVLTree<Key, Data>::cleanTree(TreeNode<Key, Data> *tree_node) {
  if (tree_node == nullptr) {
    return;
  }
  cleanTree(tree_node->rightSon);
  cleanTree(tree_node->leftSon);
  delete tree_node;
}
template<class Key, class Data>
void AVLTree<Key, Data>::printPreOrder(TreeNode<Key, Data> *tree_node) const {
  if (tree_node == nullptr) return;
  tree_node->printKey();
  printPreOrder(tree_node->getLeftSon());
  printPreOrder(tree_node->getRightSon());
}
template<class Key, class Data>
void AVLTree<Key, Data>::printInOrder(TreeNode<Key, Data> *tree_node) const {
  if (tree_node == nullptr) return;
  printInOrder(tree_node->getLeftSon());
  tree_node->printKey();
  printInOrder(tree_node->getRightSon());
}
template<class Key, class Data>
void AVLTree<Key, Data>::printPostOrder(TreeNode<Key, Data> *tree_node) const {
  if (tree_node == nullptr) return;
  printPostOrder(tree_node->getLeftSon());
  printPostOrder(tree_node->getRightSon());
  tree_node->printKey();
}
template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::updateData(const Key &key, Data &data) {
  TreeNode<Key, Data> *tree_node = findNodeInTree(key, this->root);
  if (tree_node == nullptr) {
    return AVL_KeyNotFound;
  }
  tree_node->updateData(data);
  return AVL_SUCCESS;
}
template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::findNodeInTree(const Key &key,
                                                        TreeNode<Key,
                                                                 Data> *tree_node) {
  if (tree_node == nullptr) {
    return nullptr; //subtree ended and key wasn't found
  }
  Key curr_key = tree_node->getKey();
  if (curr_key == key) {
    return tree_node; // we found it !
  }
  if (curr_key > key) {
    return findNodeInTree(key,
                          tree_node->leftSon); // it MAY BE in the left subtree
  } else {
    return findNodeInTree(key,
                          tree_node->rightSon); // it MAY BE in the right subtree
  }
  /* "it" refers to the Node we are searching */
}
template<class Key, class Data>
int AVLTree<Key, Data>::heightDifference(TreeNode<Key, Data> *tree_node) {
  int left_height = EMPTY_HEIGHT, right_height = EMPTY_HEIGHT;
  if (tree_node->getRightSon() != nullptr) {
    right_height = tree_node->getRightSon()->getHeight();
  }
  if (tree_node->getLeftSon() != nullptr) {
    left_height = tree_node->getLeftSon()->getHeight();
  }
  return (left_height - right_height);
}
template<class Key, class Data>
void AVLTree<Key, Data>::swapBetweenNodes(TreeNode<Key, Data> *first_node,
                                          TreeNode<Key, Data> *second_node) {

}
template<class Key, class Data>
void AVLTree<Key, Data>::updateTreeNodeHeight(TreeNode<Key, Data> *tree_node) {
  int left_height = EMPTY_HEIGHT, right_height = EMPTY_HEIGHT, new_height = 0;
  if (tree_node->leftSon != nullptr) {
    left_height = tree_node->leftSon->getHeight();
  }
  if (tree_node->rightSon != nullptr) {
    right_height = tree_node->rightSon->getHeight();
  }
  new_height = (left_height > right_height) ? left_height : right_height;
  tree_node->setHeight(new_height + 1);
}


#endif //WET1__AVLTREE_H_
