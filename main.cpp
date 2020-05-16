#include <iostream>
#include <stdbool.h>
#include "AVLTree.h"
#include "MusicManager.h"
#include <string>
#include "library1.h"

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

void InOrder(TreeNode<int, int> *node) {
    if (node == nullptr)
        return;
    InOrder(node->getLeftSon());
    node->printKey();
    InOrder(node->getRightSon());
}

int main() {
    void *music_manager = Init();
    MusicManager *mm = (MusicManager *) music_manager;
    int num = 5;
    AddArtist(music_manager, 1, num);

    AddToSongCount(music_manager, 1, 0);
    for (int i = 0; i < 5; ++i) {
        AddToSongCount(music_manager, 1, 1);
    }
    for (int i = 0; i < 10; ++i) {
        AddToSongCount(music_manager, 1, 2);
    }
    for (int i = 0; i < 15; ++i) {
        AddToSongCount(music_manager, 1, 3);
    }
    for (int i = 0; i < 20; ++i) {
        AddToSongCount(music_manager, 1, 4);
    }
    AddArtist(music_manager, 2, 1);
    AddArtist(music_manager, 4, 1);
    AddArtist(music_manager, 5, 1);
    AddArtist(music_manager, 8, 1);
    AddArtist(music_manager, 9, 1);

    AddToSongCount(music_manager, 2, 0);
    RemoveArtist(music_manager, 1);
    AddToSongCount(music_manager, 2, 0);
    AddToSongCount(music_manager, 2, 0);
    AddToSongCount(music_manager, 2, 0);
    AddToSongCount(music_manager, 2, 0);
    AddToSongCount(music_manager, 2, 0);
    RemoveArtist(music_manager, 2);
    RemoveArtist(music_manager, 4);
    RemoveArtist(music_manager, 5);
    RemoveArtist(music_manager, 8);
    RemoveArtist(music_manager, 9);
    Quit(&music_manager);
    return 0;
}