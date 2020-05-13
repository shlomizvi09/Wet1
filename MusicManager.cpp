//
// Created by Arik on 12/05/2020.
//

#include "MusicManager.h"

using std::bad_alloc;

void *Init() {
    MusicManager* DS;
    try {
        DS = new MusicManager();
    } catch (...) {
        return nullptr;
    }
    return (void*)DS;
}

