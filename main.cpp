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

void func(int *&num) {
  num++;
}

int main() {
  int x = 4;
  int &y = x;
  int *z = &y;

  std::cout << "x= " << x << std::endl << "y= " << y << std::endl << "z= " << z
            << std::endl;
  func(z);
  std::cout << "x= " << x << std::endl << "y= " << y << std::endl << "z= " << z
            << std::endl;
  return 0;
}