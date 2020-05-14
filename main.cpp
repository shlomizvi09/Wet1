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
  return 0;
}