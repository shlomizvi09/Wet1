#include <iostream>
#include <stdbool.h>
#include "AVLTree.h"
#include "LinkedList.h"
#include "MusicManager.h"
#include <string>

using std::string;

class Person {
 public:
  string name;
  int age;
  friend class Animal;

  Person() : name(""), age(0) {}

  Person(string name, int age) : name(name), age(age) {}

  Person(const Person &Old) : name(Old.name), age(Old.age) {}

  ~Person() {
    std::cout << "error";
  }

  friend std::ostream &operator<<(std::ostream &os, const Person &other);
};

std::ostream &operator<<(std::ostream &os, const Person &other) {
  os << "name: " << other.name << "\n" << "age: " << other.age << " ";
  return os;
}

int main() {
  AVLTree<int, Person> *new_tree = new AVLTree<int, Person>();
  return 0;
}