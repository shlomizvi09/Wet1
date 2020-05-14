#include <iostream>
#include <stdbool.h>
#include "AVLTree.h"
#include "LinkedList.h"
#include "MusicManager.h"
#include <string>

using std::string;

class Person {
  int *num;
  string name;
  int age;
 public:
  Person() : name(), age() {}

  Person(int *num, string name, int age) : num(num), name(name), age(age) {}

  Person(const Person &Old) : name(Old.name), age(Old.age) {}

  void setNum(int *num1);
  void printNum();

  friend std::ostream &operator<<(std::ostream &os, const Person &other);
};

std::ostream &operator<<(std::ostream &os, const Person &other) {
  os << "name: " << other.name << "\n" << "age: " << other.age << " ";
  return os;
}

void Person::setNum(int *num1) {
  this->num = num1;
}
void Person::printNum() {
  std::cout << *(this->num) << " ";
}

int main() {
  AVLTree<int, int> *new_tree = new AVLTree<int, int>();
  for (int num = 1; num < 10; ++num) {
    new_tree->add(num, num);
  }
  TreeNode<int, int> *node_ptr;
  AVLTreeResult res = new_tree->searchNode(4, &node_ptr);
  if (res == AVL_KeyNotFound) {
    std::cout << res << " ";
    return 0;
  }
  node_ptr->printKey();
  std::cout << "is found ! ";
  return 0;
}