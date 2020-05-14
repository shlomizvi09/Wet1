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
  TreeNode<int, SecondTreeNodeData *> *singer_node = nullptr;
  res = num_of_plays_node->getData()->singerTree->searchNode(artistID,
                                                             &singer_node);
  if (res == AVL_KeyNotFound) {
    return MM_FAIL;
  }
  TreeNode<int, ThirdTreeNodeData *> *song_node = nullptr;
  res = (singer_node->getData())->songTree->searchNode(songID, &song_node);
  if (res == AVL_KeyNotFound) {
    return MM_FAIL;
  }
}
