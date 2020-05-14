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
