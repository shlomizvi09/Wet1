#include <iostream>
#include <stdbool.h>
#include "AVLtree.h"
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
  os << other.age << " ";
}

int main() {
  Person son("shlomi", 26);
  return 0;
}