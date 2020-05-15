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

void InOrder(TreeNode<int, int> *node){
    if(node== nullptr)
        return;
    InOrder(node->getLeftSon());
    node->printKey();
    InOrder(node->getRightSon());
}

int main() {
    void *mivne = Init();
    MusicManager *ds = (MusicManager*)mivne;
    AddArtist(mivne,1,10);
    AddArtist(mivne,2,1);
    AddArtist(mivne,3,2);
    AddArtist(mivne,4,3);
    AddArtist(mivne,5,4);
    RemoveArtist(mivne,1);
    RemoveArtist(mivne,2);
    RemoveArtist(mivne,5);

    int a=10;
    NumberOfStreams(mivne,4,0,&a);
    Quit(&mivne);

    AVLTree<int,int> numberTree();
    numberTree.add(1,1);
    numberTree().add(3,1);
    numberTree().add(2,1);
    numberTree().add(4,1);
    numberTree().add(5,1);
    numberTree().add(9,1);
    numberTree().add(7,1);
    InOrder(numberTree().getRoot());


    printf("great success");

    return 0;
}