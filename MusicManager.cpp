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

    this->PlayCountList->getFirst()->getData()->updateSmallest();
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
    dataTypeTwo->UpdateSmallest();
    dataTypeTwo->originNode = this->PlayCountList->getFirst();
    for (int j = 0; j < numOfSongs; ++j) {
        node1->songs[j] = this->PlayCountList->getFirst();
    }
    this->TotalSongs += numOfSongs;
    return MM_SUCCESS;
}

MusicManagerResult MusicManager::RemoveArtist(int artistID) {
    TreeNode<int, FirstTreeNodeData *> *node1 = nullptr;
    if (this->Tree1->searchNode(artistID, &node1) == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    for (int i = 0; i < node1->getData()->numOfSongs; ++i) {
        if (node1->getData()->songs[i] == nullptr)
            continue;
        LinkedList<PlayCountNodeData *>::ListNode *playNode = node1->getData()->songs[i];
        TreeNode<int, SecondTreeNodeData *> *node2 = nullptr;
        node1->getData()->songs[i]->getData()->singerTree->searchNode
                (artistID, &node2);
        if (node2 == nullptr)
            continue;
        this->DeleteData(node2->getData()->songTree->getRoot(), node1);
        node2->getData()->songTree->cleanTree(node2->getData()->songTree->getRoot());
        delete node2->getData();
        playNode->getData()->singerTree->remove(artistID);
        if (playNode->getData()->singerTree->getRoot() == nullptr) {
            delete playNode->getData()->singerTree;
            delete playNode->getData();
            this->PlayCountList->deleteNode(playNode);
            continue;
        }
        playNode->getData()->smallest = playNode->getData()->singerTree->getSmallest();
    }
    delete node1->getData();
    this->Tree1->remove(artistID);
    return MM_SUCCESS;
}

MusicManagerResult MusicManager::NumberOfStreams(int artistID, int songID, int *streams) {
    TreeNode<int, FirstTreeNodeData *> *node1 = nullptr;
    if (this->Tree1->searchNode(artistID, &node1) == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    if (node1->getData()->numOfSongs <= songID)
        return MM_FAIL;
    *streams = node1->getData()->songs[songID]->getData()->plays;
    return MM_SUCCESS;
}

void MusicManager::DeleteData(TreeNode<int, ThirdTreeNodeData *> *root, TreeNode<int, FirstTreeNodeData *> *node1) {
    if (root == nullptr) {
        return;
    }
    DeleteData(root->getRightSon(), node1);
    DeleteData(root->getLeftSon(), node1);
    if (node1 != nullptr)
        node1->getData()->songs[root->getKey()] = nullptr;
    delete root->getData();
}

MusicManagerResult MusicManager::Quit() {
    LinkedList<PlayCountNodeData *>::ListNode *node1 = this->PlayCountList->getFirst();
    TreeNode<int, SecondTreeNodeData *> *node2 = nullptr;

    while (node1->getNext()) {
        PatrolTree(node1->getData()->singerTree->getRoot(), nullptr);
        delete node1->getData();
        node1 = node1->getNext();
        this->PlayCountList->deleteNode(node1->getPrev());
    }
    this->DeleteMainTree(this->Tree1->getRoot());
    this->Tree1->cleanTree(this->Tree1->getRoot());
    return MM_SUCCESS;
}

void MusicManager::DeleteMainTree(TreeNode<int, FirstTreeNodeData *> *root) {
    if (root == nullptr) {
        return;
    }
    DeleteMainTree(root->getRightSon());
    DeleteMainTree(root->getLeftSon());
    delete root->getData();
}

void MusicManager::PatrolTree(TreeNode<int, SecondTreeNodeData *> *root, TreeNode<int, FirstTreeNodeData *> *node1) {
    if (root == nullptr) {
        return;
    }
    PatrolTree(root->getRightSon(), node1);
    PatrolTree(root->getLeftSon(), node1);
    DeleteData(root->getData()->songTree->getRoot(), node1);
    root->getData()->songTree->cleanTree(root->getData()->songTree->getRoot());
    delete root->getData()->songTree;
    LinkedList<PlayCountNodeData *>::ListNode *origin = root->getData()->originNode;
    delete root->getData();
    int key = root->getKey();
    origin->getData()->singerTree->remove(key);
}

MusicManagerResult MusicManager::GetRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    if (this->TotalSongs < numOfSongs)
        return MM_FAIL;
    LinkedList<PlayCountNodeData *>::ListNode *playNode = nullptr;
    int counter = 0;
    while (counter < numOfSongs) {

    }
}


using std::bad_alloc;

MusicManagerResult MusicManager::AddToSongCount(int artistID, int songID) {
    FirstTreeNodeData **artist_data_tree_one = nullptr;
    AVLTreeResult res = this->Tree1->searchData(artistID, &artist_data_tree_one);
    if (res == AVL_KeyAlreadyExists) {
        return MM_NOT_EXISTS;
    }
    if (songID >= (*artist_data_tree_one)->numOfSongs) {
        return MM_FAIL;
    }
    LinkedList<PlayCountNodeData *>::ListNode
            *num_of_plays_node = (*artist_data_tree_one)->songs[songID];
    if (num_of_plays_node == nullptr) {
        return MM_FAIL;
    }
    TreeNode<int, SecondTreeNodeData *> *artist_node = nullptr;
    res = num_of_plays_node->getData()->singerTree->searchNode(artistID,
                                                               &artist_node);
    if (res == AVL_KeyNotFound) {
        return MM_FAIL;
    }
    TreeNode<int, ThirdTreeNodeData *> *song_node = nullptr;
    res = (artist_node->getData())->songTree->searchNode(songID, &song_node);
    if (res == AVL_KeyNotFound) {
        return MM_FAIL;
    }
    if ((artist_node->getData()->originNode->getData()->plays + 1)
        != (artist_node->getData()->originNode->getNext()->getData()->plays)) {

    }

}

void SecondTreeNodeData::UpdateSmallest() {
    this->smallest = this->songTree->getSmallest();
}
