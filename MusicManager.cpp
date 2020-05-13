//
// Created by Arik on 12/05/2020.
//

#include "MusicManager.h"

void *Init() {
    try {
        auto *DS = new MusicManager();
        return DS;
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
    if (ds->PlayCountList->getHead()->getNext()->getData().plays != 0) {
        auto *zeroCount = new PlayCountNode();
        zeroCount->plays = 0;
        ds->PlayCountList->insertFirst(*zeroCount);
    }
    LinkedList<PlayCountNode>::ListNode *first = ds->PlayCountList->getHead()->getNext();
    if (first->getData().singerTree == nullptr) {
        auto *tree2 = new AVLTree<int, SecondTreeNode>();
    }
    auto *node2 = new SecondTreeNode();
    first->getData().singerTree->add(artistID, *node2);
    first->getData().ChangeSmallest(first->getData().singerTree->getSmallest());
    auto *tree3 = new AVLTree<int, ThirdTreeNode>();
    for (int i = 0; i < numOfSongs; ++i) {
        auto *node3 = new ThirdTreeNode(node2);
        tree3->add(i, *node3);
    }
    node2->songTree = tree3;
    node2->originNode = first;
    node2->smallest = tree3->getSmallest();
    for (int j = 0; j < numOfSongs; ++j) {
        data->songs[j] = first;
    }
    return SUCCESS;
}
