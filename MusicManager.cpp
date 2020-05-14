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
    FirstTreeNodeData *dataTypeOne = nullptr;
    tmpResult = ds->Tree1->searchData(artistID, &dataTypeOne);
    if (tmpResult == AVL_KeyAlreadyExists)
        return FAILURE;
    dataTypeOne = new FirstTreeNodeData(numOfSongs);
    ds->Tree1->add(artistID, *dataTypeOne);
    if (ds->PlayCountList->getFirst()->getData() != 0) {
        PlayCountNodeData *zeroPlaysData = new PlayCountNodeData();
        ds->PlayCountList->insertFirst(*zeroPlaysData);
        AVLTree<int, SecondTreeNodeData> *tree2 = new AVLTree<int, SecondTreeNodeData>();
        zeroPlaysData->singerTree = tree2;
    }
    SecondTreeNodeData *dataTypeTwo = new SecondTreeNodeData();
    ds->PlayCountList->getFirst()->getData().singerTree->add(artistID, *dataTypeTwo);

    ds->PlayCountList->getFirst()->getData().ChangeSmallest(ds->PlayCountList->getFirst()->getData()
                                                                    .singerTree->getSmallest());

    TreeNode<int, SecondTreeNodeData> *node2 = nullptr;
    ds->PlayCountList->getFirst()->getData().singerTree->searchNode(artistID, &node2);
    dataTypeTwo->ChangeSmallest(dataTypeTwo->songTree->getSmallest());
    AVLTree<int, ThirdTreeNodeData> *tree3 = new AVLTree<int, ThirdTreeNodeData>();
    for (int i = 0; i < numOfSongs; ++i) {
        ThirdTreeNodeData *dataTypeThree = new ThirdTreeNodeData(node2);
        tree3->add(i, *dataTypeThree);
    }
    dataTypeTwo->songTree = tree3;
    dataTypeTwo->ChangeSmallest(dataTypeTwo->songTree->getSmallest());
    dataTypeTwo->originNode = ds->PlayCountList->getFirst();
    return SUCCESS;
}


StatusType RemoveArtist(void *DS, int artistID) {
    if (DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    FirstTreeNodeData *node1 = nullptr;

}

