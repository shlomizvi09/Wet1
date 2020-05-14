//
// Created by Arik on 12/05/2020.
//

#include "MusicManager.h"

using std::bad_alloc;

void *Init() {
    MusicManager *DS;
    try {
        DS = new MusicManager();
        return (void *) DS;
    } catch (...) {
        return nullptr;
    }
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (numOfSongs <= 0 || DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *) DS;
    AVLTreeResult tmpResult;
    FirstTreeNodeData *node1 = nullptr;
    tmpResult = ds->Tree1->search(artistID, &node1);
    if (tmpResult == AVL_KeyAlreadyExists)
        return FAILURE;
    node1 = new FirstTreeNodeData(numOfSongs);
    ds->Tree1->add(artistID, *node1);

}

StatusType RemoveArtist(void *DS, int artistID) {
    if (DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    FirstTreeNodeData *node1 = nullptr;

}

