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
    TreeNode()
            : key(), data(), height(0), rightSon(nullptr), leftSon(nullptr) {}

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
typedef enum AVLTreeOrderKind {
    Pre, In, Post, Rev
} AVLTreeOrderKind;

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

    AVLTreeResult internalAdd(TreeNode<Key, Data> *root,
                              TreeNode<Key, Data> *new_node);

    AVLTreeResult internalRemove(TreeNode<Key, Data> *tree_node, Key &key);

    AVLTreeResult deleteTreeNode(TreeNode<Key, Data> **tree_node);

    void deleteNodesWithTwoSons(TreeNode<Key, Data> *tree_node);

public:
    AVLTree();

    ~AVLTree();

    AVLTreeResult search(const Key &key, Data **data);

    AVLTreeResult add(Key key, Data data);

    AVLTreeResult remove(Key &key);

    void print(AVLTreeOrderKind print_order) const;

    TreeNode<Key, Data> *getSmallest();
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
    // TODO : Long complicated function, dont implement at night
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

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::AVLTreeBalance(TreeNode<Key,
        Data> *tree_node) {
    // now we need to sort the kind of imbalance, if exists
    if (heightDifference(tree_node) == NOT_BALANCED_L) {
        if (heightDifference(tree_node->leftSon) == BALANCED_L) {
            return LRrotation(tree_node, tree_node->leftSon);
        }
        return LLrotation(tree_node, tree_node->leftSon);
    }
    if (heightDifference(tree_node) == NOT_BALANCED_R) {
        if (heightDifference(tree_node->rightSon) == BALANCED_R) {
            return RLrotation(tree_node, tree_node->rightSon);
        }
        return RRrotation(tree_node, tree_node->rightSon);
    }
    //the tree is balanced
    return tree_node;
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::LLrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
    parent->setLeftSon(son->rightSon);
    son->setRightSon(parent);
    updateTreeNodeHeight(parent);
    updateTreeNodeHeight(son);
    return son;
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::LRrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
    parent->setLeftSon(RRrotation(son, son->rightSon));
    return LLrotation(parent, parent->leftSon);
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::RLrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
    parent->setRightSon(LLrotation(son->leftSon));
    return RRrotation(parent, parent->rightSon);
}

template<class Key, class Data>
TreeNode<Key, Data> *AVLTree<Key, Data>::RRrotation(TreeNode<Key, Data> *parent,
                                                    TreeNode<Key, Data> *son) {
    parent->setRightSon(son->leftSon);
    son->setLeftSon(parent);
    updateTreeNodeHeight(parent);
    updateTreeNodeHeight(son);
    return son;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::internalAdd(TreeNode<Key, Data> *root,
                                              TreeNode<Key, Data> *new_node) {
    Key root_key = root->key, new_node_key = new_node->key;
    AVLTreeResult result = AVL_SUCCESS; //unless we'll find out otherwise...
    if (root_key == new_node_key) {
        return AVL_KeyAlreadyExists;
    }
    if (root_key > new_node_key) {
        if (root->leftSon == nullptr) {
            root->setLeftSon(new_node);
            updateTreeNodeHeight(root);
            return AVL_SUCCESS;
        }
        result = internalAdd(root->leftSon, new_node);
        updateTreeNodeHeight(root);
        root = AVLTreeBalance(root);
        return result;
    }
    // if we got here, new_node_key must be greater than root_key
    if (root->rightSon == nullptr) {
        root->setRightSon(new_node);
        updateTreeNodeHeight(root);
        return AVL_SUCCESS;
    }
    result = internalAdd(root->rightSon, new_node);
    updateTreeNodeHeight(root);
    root = AVLTreeBalance(root);
    return result;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::internalRemove(TreeNode<Key, Data> *tree_node,
                                                 Key &key) {
    if (tree_node == nullptr) return AVL_KeyNotFound;
    Key curr_key = tree_node->key;
    if (curr_key == key) {
        deleteTreeNode(&tree_node);
    } else if (curr_key > key) {
        internalRemove(tree_node->leftSon, key);
        updateTreeNodeHeight(tree_node);
        tree_node = AVLTreeBalance(tree_node);
    } else {
        internalRemove(tree_node->rightSon, key);
        updateTreeNodeHeight(tree_node);
        tree_node = AVLTreeBalance(tree_node);
    }
    return AVL_SUCCESS;
}

template<class Key, class Data>
AVLTreeResult AVLTree<Key, Data>::deleteTreeNode(TreeNode<Key,
        Data> **tree_node) {
    TreeNode<Key, Data> *node_to_remove;
    if (*(tree_node)->leftSon == nullptr && *(tree_node)->rightSon == nullptr) {
        node_to_remove = *tree_node;
        *tree_node = nullptr;
        delete node_to_remove;
    } else if (*(tree_node)->leftSon != nullptr
               && *(tree_node)->rightSon == nullptr) {
        node_to_remove = *tree_node;
        *tree_node = *(tree_node)->leftSon;
        delete node_to_remove;
    } else if (*(tree_node)->leftSon == nullptr
               && *(tree_node)->rightSon != nullptr) {
        node_to_remove = *tree_node;
        *tree_node = *(tree_node)->rightSon;
        delete node_to_remove;
    } else {
        deleteNodesWithTwoSons(*tree_node);
    }
    return AVL_SUCCESS;
}

#endif //WET1__AVLTREE_H_
