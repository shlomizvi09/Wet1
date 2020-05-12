//
// Created by Arik on 12/05/2020.
//

#include "MusicManager.h"

void *Init() {
    try {
        auto *DS = new MusicManager();
    }
    catch (std::bad_alloc &e) {
        return nullptr;
    }
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (numOfSongs <= 0 || DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    auto *ds = (MusicManager *) DS;
    auto *data = new FirstTreeNode(numOfSongs);
    if (ds->Tree1->add(artistID, *data) == AVL_KeyAlreadyExists)
        return FAILURE;
    if (ds->PlayCountList->getHead()->getNext()->getData() != 0) {
        auto *zeroCount = new PlayCountNode();
        ds->PlayCountList->insertFirst(*zeroCount);
    }
    PlayCountNode *first = ds->PlayCountList->getHead()->getNext();
    auto *tree2 = new AVLTree<int, SecondTreeNode>();
    auto *node2 = new SecondTreeNode();
    auto *tree3 = new AVLTree<int, ThirdTreeNode>();
    for (int i = 0; i < numOfSongs; ++i) {
        auto *node3 = new ThirdTreeNode(node2);
        tree3->add(i, *node3);
    }
    node2->originNode=ZeroCount;


}
