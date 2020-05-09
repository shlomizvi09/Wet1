#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> arik;
    LinkedList<int>::Node a = arik.insertInPlace(arik.getHead(), 1);
    LinkedList<int>::Node b = arik.insertInPlace(&a, 2);
    LinkedList<int>::Node c = arik.insertInPlace(&b, 3);
    std::cout << "Hello, World!" << std::endl;


    return 0;
}

































