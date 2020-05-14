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
    AVLTree<int, string> *new_tree = new AVLTree<int, string>();
    new_tree->add(7, "g");
    new_tree->add(1, "a");
    new_tree->add(2, "b");
    new_tree->add(8, "h");
    new_tree->add(5, "e");
    new_tree->add(6, "f");
    new_tree->add(3, "c");
    new_tree->add(4, "d");
    new_tree->add(9, "i");
    int num = 5;
    new_tree->remove(num);
    new_tree->print(In);

    void *DS = Init();
    AddArtist(DS, 3, 10);
    MusicManager *ds = (MusicManager *) DS;

    return 0;


}