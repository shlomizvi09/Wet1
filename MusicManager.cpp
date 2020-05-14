//
// Created by Arik on 12/05/2020.
//

#include "MusicManager.h"

MusicManagerResult MusicManager::AddArtist(int artistID, int numOfSongs) {
    FirstTreeNodeData **dataTypeOne = nullptr;
    if (this->Tree1->searchData(artistID, &dataTypeOne) == AVL_SUCCESS) {
        return MM_EXISTS;
    }
    FirstTreeNodeData *node1 = new FirstTreeNodeData(numOfSongs);
    this->Tree1->add(artistID, node1);
    if (this->PlayCountList->getFirst()->getData() == nullptr ||
        this->PlayCountList->getFirst()->getData()->plays != 0) {
        PlayCountNodeData *zeroPlaysData = new PlayCountNodeData(0);
        this->PlayCountList->insertFirst(zeroPlaysData);
        AVLTree<int, SecondTreeNodeData *>
                *tree2 = new AVLTree<int, SecondTreeNodeData *>();
        zeroPlaysData->singerTree = tree2;
        printf("bla");
    }
    SecondTreeNodeData *dataTypeTwo = new SecondTreeNodeData();
    this->PlayCountList->getFirst()->getData()->singerTree->add(artistID,
                                                                dataTypeTwo);

    this->PlayCountList->getFirst()->getData()->ChangeSmallest(this->PlayCountList->getFirst()->getData()
                                                                       ->singerTree->getSmallest());

    TreeNode<int, SecondTreeNodeData *> *node2 = nullptr;
    this->PlayCountList->getFirst()->getData()->singerTree->searchNode(artistID,
                                                                       &node2);
    AVLTree<int, ThirdTreeNodeData *>
            *tree3 = new AVLTree<int, ThirdTreeNodeData *>();
    for (int i = 0; i < numOfSongs; ++i) {
        ThirdTreeNodeData *dataTypeThree = new ThirdTreeNodeData(node2);
        tree3->add(i, dataTypeThree);
    }
    dataTypeTwo->songTree = tree3;
    dataTypeTwo->ChangeSmallest(dataTypeTwo->songTree->getSmallest());
    dataTypeTwo->originNode = this->PlayCountList->getFirst();
    for (int j = 0; j < numOfSongs; ++j) {
        node1->songs[j] = this->PlayCountList->getFirst();
    }
    this->TotalSongs += numOfSongs;
    return MM_SUCCESS;
}

MusicManagerResult MusicManager::RemoveArtist(int artistID) {
    TreeNode<int, FirstTreeNodeData *> *node1 = new TreeNode<int, FirstTreeNodeData *>();
    if (this->Tree1->searchNode(artistID, &node1) == AVL_SUCCESS) {
        return MM_EXISTS;
    }
    for (int i = 0; i < node1->getData()->numOfSongs; ++i) {
        if (node1->getData()->songs[i] == nullptr)
            continue;


    }

}

 void MusicManager::DeleteTreeData(AVLTree<int,ThirdTreeNodeData*> *tree) {
     TreeNode<int, ThirdTreeNodeData*> *root = tree->getRoot();

 }

void MusicManager::DeleteData(TreeNode<int, ThirdTreeNodeData *> *root) {
    if (root == nullptr) {
        return;
    }
    DeleteData(root.);
    DeleteData(root->leftSon);

}
}

using std::bad_alloc;
