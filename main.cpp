#include <iostream>
#include <stdbool.h>
#include "AVLTree.h"
#include <string>
using std::string;

class Person {
  string name;
  int age;
 public:
  Person() : name(), age() {}
  Person(string name, int age) : name(name), age(age) {}
  Person(const Person &Old) : name(Old.name), age(Old.age) {}
  friend std::ostream &operator<<(std::ostream &os, const Person &other);
};

std::ostream &operator<<(std::ostream &os, const Person &other) {
  os << "name: " << other.name << "\n" << "age: " << other.age << " ";
}

int main() {
  Person son("shlomi", 26);
  TreeNode<int, Person> Node = TreeNode<int, Person>(312425192, son);
  Node.printKey();
  Node.printData();
  return 0;
}