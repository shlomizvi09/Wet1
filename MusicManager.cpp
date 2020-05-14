//
// Created by Arik on 12/05/2020.
//

#include "MusicManager.h"

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
