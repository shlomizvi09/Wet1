#include <iostream>
#include <stdbool.h>
#include "AVLTree.h"
#include "LinkedList.h"
#include "MusicManneger.h"
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
    return os;
}

void func(int *&num) {
    num++;
}

int main() {
    int x = 4;
    int &y = x;
    int *z = &y;

    std::cout << "x= " << x << std::endl << "y= " << y << std::endl << "z= "
              << z
              << std::endl;
    func(z);
    std::cout << "x= " << x << std::endl << "y= " << y << std::endl << "z= "
              << z
              << std::endl;

    LinkedList<int> arik;
    LinkedList<int>::ListNode *node1= arik.insertFirst(1);
    LinkedList<int>::ListNode *node2= arik.insertInPlace(node1,3);
    LinkedList<int>::ListNode *node3= arik.insertInPlace(node2,4);
    LinkedList<int>::ListNode *node4= arik.insertInPlace(node1,2);
    arik.printList();
    arik.deleteNode(node2);
    arik.printList();
    arik.deleteNode(arik.getHead());

    AVLTree<int,FirstTreeNode> DS;
    FirstTreeNode node5(3);








    return 0;
}