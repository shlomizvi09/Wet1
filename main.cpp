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

class Animal {
  Person *owner;
 public:
  Animal(Person *owner) : owner(owner) {}
  ~Animal() {

  }
  void printOwner();

};

void Animal::printOwner() {
  std::cout << owner->name;
}

int main() {
    void *mivne = Init();
    MusicManager *ds = (MusicManager*)mivne;
    AddArtist(mivne,3,10);
    AddArtist(mivne,3,3);
    AddArtist(mivne,2,13);
    AddArtist(mivne,5,15);
    AddArtist(mivne,6,1);
    AddArtist(mivne,6,0);
    AddArtist(mivne,4,100);
    AddArtist(mivne,-5,100);
    AddArtist(mivne,0,100);
    AddArtist(mivne,55,10540);
    AddArtist(mivne,4,-5);
    AddArtist(mivne,1,0);


    printf("great success");

    return 0;
}