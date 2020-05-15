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
    TreeNode<int, SecondTreeNodeData *> *node2 = nullptr;
    node1->getData()->songs[i]->getData()->singerTree->searchNode
        (artistID, &node2);
    if (node2 == nullptr)
      continue;
    this->DeleteData(node2->getData()->songTree->getRoot());
    node2->getData()->songTree->cleanTree(node2->getData()->songTree->getRoot());
    delete node2->getData();
    node1->getData()->songs[i]->getData()->singerTree->remove(artistID);
  }
  delete node1->getData();
  this->Tree1->remove(artistID);
  return MM_SUCCESS;
}

MusicManagerResult MusicManager::NumberOfStreams(int artistID,
                                                 int songID,
                                                 int *streams) {
  TreeNode<int, FirstTreeNodeData *> *node1 = nullptr;
  if (this->Tree1->searchNode(artistID, &node1) == AVL_KeyNotFound) {
    return MM_NOT_EXISTS;
  }
  if (node1->getData()->numOfSongs <= songID)
    return MM_FAIL;
  *streams = node1->getData()->songs[songID]->getData()->plays;
  return MM_SUCCESS;
}

void MusicManager::DeleteData(TreeNode<int, ThirdTreeNodeData *> *root) {
  if (root == nullptr) {
    return;
  }
  DeleteData(root->getRightSon());
  DeleteData(root->getLeftSon());
  delete root->getData();
}

using std::bad_alloc;

MusicManagerResult MusicManager::AddToSongCount(int artistID, int songID) {
  FirstTreeNodeData **first_tree_data = nullptr;
  AVLTreeResult
      res = this->Tree1->searchData(artistID, &first_tree_data);
  if (res == AVL_KeyAlreadyExists) {
    return MM_NOT_EXISTS;
  }
  if (songID >= (*first_tree_data)->numOfSongs) {
    return MM_FAIL;
  }
  LinkedList<PlayCountNodeData *>::ListNode
      *num_plays_list_node = (*first_tree_data)->songs[songID];
  if (num_plays_list_node == nullptr) {
    return MM_FAIL;
  }
  PlayCountNodeData *num_plays_list_data = num_plays_list_node->getData();
  if (num_plays_list_data == nullptr) {
    return MM_NULL_ARGUMENT;
  }
  LinkedList<PlayCountNodeData *>::ListNode
      *next_num_plays_list_node = num_plays_list_node->getNext();
  PlayCountNodeData *new_num_plays_list_data = next_num_plays_list_node->getData();
  if (new_num_plays_list_data == nullptr) {
    return MM_NULL_ARGUMENT;
  }
  TreeNode<int, SecondTreeNodeData *> *second_tree_node = nullptr;
  res = num_plays_list_data->singerTree->searchNode(artistID, &second_tree_node);
  if (res == AVL_KeyNotFound) {
    return MM_FAIL;
  }
  SecondTreeNodeData *second_tree_data = second_tree_node->getData();
  if (second_tree_data == nullptr) {
    return MM_NULL_ARGUMENT;
  }
  TreeNode<int, ThirdTreeNodeData *> *third_tree_node = nullptr;
  res = second_tree_data->songTree->searchNode(songID, &third_tree_node);
  if (res == AVL_KeyNotFound) {
    return MM_FAIL;
  }
  ThirdTreeNodeData *third_tree_data = third_tree_node->getData();
  if (third_tree_node == nullptr) {
    return MM_NULL_ARGUMENT;
  }
  /*if the num_of_play_list_node is the last node before the tail
   * OR there is no node with the song's new plays number*/
  if (next_num_plays_list_node == this->PlayCountList->getTail()
      || num_plays_list_data->plays + 1
          != new_num_plays_list_data->plays) {
    AVLTree<int, ThirdTreeNodeData *> *new_tree3 = new AVLTree<int, ThirdTreeNodeData *>();
    new_tree3->add(songID, third_tree_data);
    SecondTreeNodeData *new_second_tree_data =
        new SecondTreeNodeData(nullptr, new_tree3, new_tree3->getSmallest());
    AVLTree<int, SecondTreeNodeData *>
        *new_tree2 = new AVLTree<int, SecondTreeNodeData *>();
    new_tree2->add(artistID, new_second_tree_data);
    TreeNode<int, SecondTreeNodeData *> *new_origin_artist = nullptr;
    new_tree2->searchNode(artistID, &new_origin_artist);
    third_tree_data->setOriginArtist(new_origin_artist);
    PlayCountNodeData *new_play_count_data = new PlayCountNodeData(
        num_plays_list_data->plays + 1,
        new_tree2,
        new_tree2->getSmallest());
    next_num_plays_list_node = this->PlayCountList->insertInPlace(
        num_plays_list_node,
        new_play_count_data);
    new_second_tree_data->setOriginNode(next_num_plays_list_node);
    (*first_tree_data)->songs[songID] = next_num_plays_list_node;
  } else if (num_plays_list_data->plays + 1
      == next_num_plays_list_node->getData()->plays) {// if the new num_of_play_list_node does exist
    SecondTreeNodeData **new_second_tree_data = nullptr;
    new_num_plays_list_data->singerTree->searchData(artistID, &new_second_tree_data);
    if (*new_second_tree_data == nullptr) { // the artist isn't in this listNode
      AVLTree<int, ThirdTreeNodeData *> *new_tree3 = new AVLTree<int, ThirdTreeNodeData *>();
      new_tree3->add(songID, third_tree_data);
      *new_second_tree_data =
          new SecondTreeNodeData(next_num_plays_list_node, new_tree3, new_tree3->getSmallest());
      (*new_second_tree_data)->UpdateSmallest();
      new_num_plays_list_data->singerTree->add(artistID, *new_second_tree_data);
      new_num_plays_list_data->updateSmallest();
    } else {
      (*new_second_tree_data)->songTree->add(songID, third_tree_data);
      (*new_second_tree_data)->UpdateSmallest();
      new_num_plays_list_data->updateSmallest();
    }
  }
  second_tree_data->songTree->remove(songID);
  if (second_tree_data->songTree->isEmpty()) {
    delete second_tree_data->songTree;
    delete second_tree_data;
    num_plays_list_data->singerTree->remove(artistID);
    if (num_plays_list_data->singerTree->isEmpty()) {
      delete num_plays_list_data->singerTree;
      delete num_plays_list_data;
      this->PlayCountList->deleteNode(num_plays_list_node);
    }
  }
  return MM_SUCCESS;
}
void PlayCountNodeData::updateSmallest() {
  this->smallest_singer = this->singerTree->getSmallest();
}

void SecondTreeNodeData::setOriginNode(LinkedList<PlayCountNodeData *>::ListNode *new_originNode) {
  if (new_originNode == nullptr) return;
  this->originNode = new_originNode;
}

void SecondTreeNodeData::UpdateSmallest() {
  this->smallest_song = this->songTree->getSmallest();
}

void ThirdTreeNodeData::setOriginArtist(TreeNode<int,
                                                 SecondTreeNodeData *> *new_origin_artist) {
  if (new_origin_artist != nullptr) {
    this->originArtist = new_origin_artist;
  }
}
