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
    this->TotalSongs-=node1->getData()->numOfSongs;
    for (int i = 0; i < node1->getData()->numOfSongs; ++i) {
        if (node1->getData()->songs[i] == nullptr)
            continue;
        LinkedList<PlayCountNodeData *>::ListNode *playNode = node1->getData()->songs[i];
        TreeNode<int, SecondTreeNodeData *> *node2 = nullptr;
        playNode->getData()->singerTree->searchNode(artistID,&node2);
        if (node2 == nullptr)
            continue;
        this->DeleteData(node2->getData()->songTree->getRoot(), node1);
        node2->getData()->songTree->cleanTree(node2->getData()->songTree->getRoot());
        delete node2->getData()->songTree;
        delete node2->getData();
        playNode->getData()->singerTree->remove(artistID);
        if (playNode->getData()->singerTree->isEmpty()) {
            delete playNode->getData()->singerTree;
            delete playNode->getData();
            this->PlayCountList->deleteNode(playNode);
            continue;
        }
        playNode->getData()->updateSmallest();
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

void MusicManager::DeleteData(TreeNode<int, ThirdTreeNodeData *> *root,
                              TreeNode<int, FirstTreeNodeData *> *node1) {
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
    while (node1->getNext()) {
        PatrolTree(node1->getData()->singerTree->getRoot(), nullptr);
        delete node1->getData()->singerTree;
        delete node1->getData();
        node1 = node1->getNext();
        this->PlayCountList->deleteNode(node1->getPrev());
    }
    this->PlayCountList->deleteNode(node1->getPrev());
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

void MusicManager::PatrolTree(TreeNode<int, SecondTreeNodeData *> *root,
                              TreeNode<int, FirstTreeNodeData *> *node1) {
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
    LinkedList<PlayCountNodeData *>::ListNode *playNode = this->PlayCountList->getTail()->getPrev();
    int counter = 0;
    while (counter < numOfSongs) {
        PatrolFromSmallestSinger(playNode->getData()->smallest_singer, numOfSongs, artists, songs, &counter,
                                 playNode->getData()->singerTree->getSize());
        playNode = playNode->getPrev();
    }
    return MM_SUCCESS;
}

using std::bad_alloc;

MusicManagerResult MusicManager::AddToSongCount(int artistID, int songID) {
    FirstTreeNodeData **first_tree_data = nullptr;
    AVLTreeResult
            res = this->Tree1->searchData(artistID, &first_tree_data);
    if (res == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    if (songID >= (*first_tree_data)->numOfSongs) {
        return MM_FAIL;
    }
    LinkedList<PlayCountNodeData *>::ListNode
            *num_plays_list_node = (*first_tree_data)->songs[songID];
    if (num_plays_list_node == nullptr) {
        return MM_NULL_ARGUMENT;
    }
    PlayCountNodeData *num_plays_list_data = num_plays_list_node->getData();
    if (num_plays_list_data == nullptr) {
        return MM_NULL_ARGUMENT;
    }
    LinkedList<PlayCountNodeData *>::ListNode
            *next_num_plays_list_node = num_plays_list_node->getNext();
    PlayCountNodeData *new_num_plays_list_data = next_num_plays_list_node->getData();
    /*if (new_num_plays_list_data == nullptr) {
      return MM_NULL_ARGUMENT;
    }*/
    TreeNode<int, SecondTreeNodeData *> *second_tree_node = nullptr;
    res = num_plays_list_data->singerTree->searchNode(artistID, &second_tree_node);
    if (res == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
    }
    SecondTreeNodeData *second_tree_data = second_tree_node->getData();
    if (second_tree_data == nullptr) {
        return MM_NULL_ARGUMENT;
    }
    TreeNode<int, ThirdTreeNodeData *> *third_tree_node = nullptr;
    res = second_tree_data->songTree->searchNode(songID, &third_tree_node);
    if (res == AVL_KeyNotFound) {
        return MM_NOT_EXISTS;
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
        TreeNode<int, SecondTreeNodeData *> *new_second_tree_node = nullptr;
        new_tree2->searchNode(artistID, &new_second_tree_node);
        third_tree_data->setOriginArtist(new_second_tree_node);
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
        if (new_second_tree_data == nullptr
            || *new_second_tree_data == nullptr) { // the artist isn't in this listNode
            AVLTree<int, ThirdTreeNodeData *> *new_tree3 = new AVLTree<int, ThirdTreeNodeData *>();
            new_tree3->add(songID, third_tree_data);
            SecondTreeNodeData *new_2_second_tree_data =
                    new SecondTreeNodeData(next_num_plays_list_node, new_tree3, new_tree3->getSmallest());
            new_2_second_tree_data->UpdateSmallest();
            new_num_plays_list_data->singerTree->add(artistID, new_2_second_tree_data);
            new_num_plays_list_data->updateSmallest();
            TreeNode<int, SecondTreeNodeData *> *new_second_tree_node = nullptr;
            new_num_plays_list_data->singerTree->searchNode(artistID, &new_second_tree_node);
            third_tree_data->setOriginArtist(new_second_tree_node);
            (*first_tree_data)->songs[songID] = next_num_plays_list_node;
        } else {
            (*new_second_tree_data)->songTree->add(songID, third_tree_data);
            (*new_second_tree_data)->UpdateSmallest();
            new_num_plays_list_data->updateSmallest();
            TreeNode<int, SecondTreeNodeData *> *new_second_tree_node = nullptr;
            new_num_plays_list_data->singerTree->searchNode(artistID, &new_second_tree_node);
            third_tree_data->setOriginArtist(new_second_tree_node);
            (*first_tree_data)->songs[songID] = next_num_plays_list_node;
        }
    }
    second_tree_data->songTree->remove(songID);
    second_tree_data->UpdateSmallest();
    num_plays_list_data->updateSmallest();
    if (second_tree_data->songTree->isEmpty()) {
        delete second_tree_data->songTree;
        delete second_tree_data;
        num_plays_list_data->singerTree->remove(artistID);
        num_plays_list_data->updateSmallest();
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

void SecondTreeNodeData::UpdateSmallest() {
    this->smallest_song = this->songTree->getSmallest();
}

void SecondTreeNodeData::setOriginNode(LinkedList<PlayCountNodeData *>::ListNode *new_originNode) {
    if (new_originNode == nullptr) return;
    this->originNode = new_originNode;
}

void ThirdTreeNodeData::setOriginArtist(TreeNode<int,
        SecondTreeNodeData *> *new_origin_artist) {
    if (new_origin_artist != nullptr) {
        this->originArtist = new_origin_artist;
    }
}

void MusicManager::PatrolFromSmallestSong(TreeNode<int, ThirdTreeNodeData *> *node3, int numOfSongs, int *artists,
                                          int *songs, int *counter, int size) {
    int internalCounter = 0;
    TreeNode<int, ThirdTreeNodeData *> *nodeFrom = node3->getParent();
    if (nodeFrom == nullptr) {
        songs[*counter] = node3->getKey();
        artists[*counter] = node3->getData()->originArtist->getKey();
        (*counter)++;
        internalCounter++;
        nodeFrom = node3;
        node3 = node3->getRightSon();
    }
    while (*counter < numOfSongs && internalCounter < size) {
        if (nodeFrom == node3->getParent()) {
            if (node3->getLeftSon() != nullptr) {
                nodeFrom = node3;
                node3 = node3->getLeftSon();
                continue;
            } else if (node3->getLeftSon() == nullptr && node3->getRightSon() != nullptr) {
                songs[*counter] = node3->getKey();
                artists[*counter] = node3->getData()->originArtist->getKey();
                (*counter)++;
                internalCounter++;
                nodeFrom = node3;
                node3 = node3->getRightSon();
                continue;
            } else if (node3->getRightSon() == nullptr && node3->getLeftSon() == nullptr) {
                songs[*counter] = node3->getKey();
                artists[*counter] = node3->getData()->originArtist->getKey();
                (*counter)++;
                internalCounter++;
                nodeFrom = node3;
                node3 = node3->getParent();
                continue;
            }
        } else if (nodeFrom == node3->getLeftSon()) {
            if (node3->getRightSon() == nullptr) {
                songs[*counter] = node3->getKey();
                artists[*counter] = node3->getData()->originArtist->getKey();
                (*counter)++;
                internalCounter++;
                nodeFrom = node3;
                node3 = node3->getParent();
                continue;
            } else if (node3->getRightSon() != nullptr) {
                songs[*counter] = node3->getKey();
                artists[*counter] = node3->getData()->originArtist->getKey();
                (*counter)++;
                internalCounter++;
                nodeFrom = node3;
                node3 = node3->getRightSon();
                continue;
            }
        } else if (nodeFrom == node3->getRightSon()) {
            nodeFrom = node3;
            node3 = node3->getParent();
            continue;
        }
    }
    return;
}

void MusicManager::PatrolFromSmallestSinger(TreeNode<int, SecondTreeNodeData *> *node2, int numOfSongs, int *artists,
                                            int *songs, int
                                            *counter, int size) {
    int internalCounter = 0;
    TreeNode<int, SecondTreeNodeData *> *nodeFrom = node2->getParent();
    if (nodeFrom == nullptr) {
        PatrolFromSmallestSong(node2->getData()->smallest_song, numOfSongs, artists, songs, counter,
                               node2->getData()->songTree->getSize());
        internalCounter++;
        nodeFrom = node2;
        node2 = node2->getRightSon();
    }
    while (*counter < numOfSongs && internalCounter < size) {
        if (nodeFrom == node2->getParent()) {
            if (node2->getLeftSon() != nullptr) {
                nodeFrom = node2;
                node2 = node2->getLeftSon();
                continue;
            } else if (node2->getLeftSon() == nullptr && node2->getRightSon() != nullptr) {
                PatrolFromSmallestSong(node2->getData()->smallest_song, numOfSongs, artists, songs, counter,
                                       node2->getData()->songTree->getSize());
                internalCounter++;
                nodeFrom = node2;
                node2 = node2->getRightSon();
                continue;
            } else if (node2->getRightSon() == nullptr && node2->getLeftSon() == nullptr) {
                PatrolFromSmallestSong(node2->getData()->smallest_song, numOfSongs, artists, songs, counter,
                                       node2->getData()->songTree->getSize());
                internalCounter++;
                nodeFrom = node2;
                node2 = node2->getParent();
                continue;
            }
        } else if (nodeFrom == node2->getLeftSon()) {
            if (node2->getRightSon() == nullptr) {
                PatrolFromSmallestSong(node2->getData()->smallest_song, numOfSongs, artists, songs, counter,
                                       node2->getData()->songTree->getSize());
                internalCounter++;
                nodeFrom = node2;
                node2 = node2->getParent();
                continue;
            } else if (node2->getRightSon() != nullptr) {
                PatrolFromSmallestSong(node2->getData()->smallest_song, numOfSongs, artists, songs, counter,
                                       node2->getData()->songTree->getSize());
                internalCounter++;
                nodeFrom = node2;
                node2 = node2->getRightSon();
                continue;
            }
        } else if (nodeFrom == node2->getRightSon()) {
            nodeFrom = node2;
            node2 = node2->getParent();
            continue;
        }
    }
    return;
}
