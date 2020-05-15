//
// Created by Arik on 07/05/2020.
//

#ifndef WET1_LINKEDLIST_H
#define WET1_LINKEDLIST_H

#include <iostream>

// Doubly linked list //
template<class T>
class LinkedList {

 public:
  // generic node in the list //
  class ListNode;

  // default constructor //
  LinkedList<T>();

  // destructor //
  ~LinkedList<T>();

  // return the head of the list //
  ListNode *getHead();

  // return the tail of the list //
  ListNode *getTail();

  ListNode *getFirst();

  // insert new node, next to current //
  ListNode *insertInPlace(ListNode *current, T data);

  // insert new node to be the first node //
  ListNode *insertFirst(T data);

  // remove node from the list //
  void deleteNode(ListNode *node);

  // prints the data of all the node from head to tail //
  void printList();

  class ListNode {
    T data;
    ListNode *next;
    ListNode *prev;
   public:
    // node constructor //
    ListNode(T data);

    // default constructor //
    ListNode();

    // destructor //
    ~ListNode() = default;

    // returns the data contained in the node //
    T &getData();

    // returns the next node //
    ListNode *getNext();

    // returns the previous node //
    ListNode *getPrev();

    // removes the node //
    void removeNode();

    // changes next node to be *next //
    void setNext(ListNode *next);

    // changes previous node to be *prev //
    void setPrev(ListNode *prev);

    // changes the data contained in the node //
    void changeData(T data);
  };

 private:
  ListNode *head;
  ListNode *tail;
};

/*        IMPLEMENTATION        */

template<class T>
LinkedList<T>::LinkedList() {
  this->head = new ListNode();
  this->tail = new ListNode();
  this->head->setNext(tail);
  this->head->setPrev(nullptr);
  this->tail->setNext(nullptr);
  this->tail->setPrev(head);
}

template<class T>
LinkedList<T>::~LinkedList() {
  ListNode *iterator = this->getHead()->getNext();
  ListNode *tmp = iterator;
  while (iterator != this->tail) {
    iterator = iterator->getNext();
    tmp->removeNode();
    tmp = iterator;
  }
  delete this->head;
  delete this->tail;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::getHead() {
  return this->head;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::getTail() {
  return this->tail;
}

template<class T>
typename LinkedList<T>::ListNode *
LinkedList<T>::insertInPlace(LinkedList::ListNode
                             *current, T
                             data) {
  ListNode *newNode = new ListNode(data);
  newNode->setPrev(current);
  newNode->setNext(current->getNext());
  current->getNext()->setPrev(newNode);
  current->setNext(newNode);
  return newNode;
}

template<class T>
void LinkedList<T>::printList() {
  ListNode *iterator = this->head->getNext();
  while (iterator->getNext()) {
    std::cout << iterator->getData() << std::endl;
    iterator = iterator->getNext();
  }

}

template<class T>
void LinkedList<T>::deleteNode(LinkedList::ListNode *node) {
  if (node == tail || node == head)
    return;
  node->removeNode();

}

template<class T>
typename LinkedList<T>::ListNode *
LinkedList<T>::insertFirst(T
                           data) {
  ListNode *newNode = new ListNode();
  newNode->changeData(data);
  newNode->setPrev(this->head);
  newNode->setNext(this->head->getNext());
  newNode->getNext()->setPrev(newNode);
  newNode->getPrev()->setNext(newNode);
  return newNode;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::getFirst() {
  return this->getHead()->getNext();
}

template<class T>
LinkedList<T>::ListNode::ListNode(T data) :data(data) {
  this->next = nullptr;
  this->prev = nullptr;
}

template<class T>
LinkedList<T>::ListNode::ListNode() {
  this->data = nullptr;
  this->next = nullptr;
  this->prev = nullptr;
}

template<class T>
T &LinkedList<T>::ListNode::getData() {
  return data;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::getNext() {
  return this->next;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::getPrev() {
  return this->prev;
}

template<class T>
void LinkedList<T>::ListNode::removeNode() {
  this->getPrev()->setNext(this->getNext());
  this->getNext()->setPrev(this->getPrev());
  delete this;
}

template<class T>
void LinkedList<T>::ListNode::setNext(LinkedList<T>::ListNode *next) {
  this->next = next;
}

template<class T>
void LinkedList<T>::ListNode::setPrev(LinkedList<T>::ListNode *prev) {
  this->prev = prev;
}

template<class T>
void LinkedList<T>::ListNode::changeData(T data) {
  this->data = data;

}

#endif //WET1_LINKEDLIST_H
