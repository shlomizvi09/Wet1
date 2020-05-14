//
// Created by Arik on 12/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "LinkedList.h"
#include "AVLTree.h"
#include "library1.h"

class MusicManager;

class PlayCountNodeData;

class FirstTreeNodeData;

class SecondTreeNodeData;

class ThirdTreeNodeData;

// Music Manager struct //

class MusicManager {
public:
    AVLTree<int, FirstTreeNodeData> *Tree1;
    LinkedList<PlayCountNodeData> *PlayCountList;
    int TotalSongs;

    MusicManager() : TotalSongs(0) {
        PlayCountList = new LinkedList<PlayCountNodeData>();
        Tree1 = new AVLTree<int, FirstTreeNodeData>();
    }

    ~MusicManager() {
        delete Tree1;
        delete PlayCountList;
    }
};

// Music Manager functions //

void *Init();

StatusType AddArtist(void *DS, int artistID, int numOfSongs);

StatusType RemoveArtist(void *DS, int artistID);

StatusType AddToSongCount(void *DS, int artistID, int songID);

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams);

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int
*songs);

void Quit(void **DS);


class PlayCountNodeData {
public:
    int plays;
    AVLTree<int, SecondTreeNodeData> *singerTree;
    TreeNode<int, class SecondTreeNodeData> *smallest;

    PlayCountNodeData(int numOfPlays, AVLTree<int, SecondTreeNodeData> *singerTree,
                      TreeNode<int, class SecondTreeNodeData> *smallest) : plays
                  (numOfPlays), singerTree
            (singerTree), smallest(smallest) {};

    PlayCountNodeData(const PlayCountNodeData &other) : plays(other.plays),
                                                        singerTree(other.singerTree),
                                                        smallest(other.smallest) {}

    PlayCountNodeData() {
        plays = 0;
        singerTree = nullptr;
        smallest = nullptr;
    }

    ~PlayCountNodeData() = default;

    void ChangeSmallest(TreeNode<int, class SecondTreeNodeData> *node){
        smallest=node;
    }

    void ChangePlays(int plays){
        this->plays=plays;
    }

    bool operator==(const PlayCountNodeData *node) const {
        return (this->plays == node->plays);
    }

    bool operator!=(const PlayCountNodeData *node) const {
        return (this->plays != node->plays);
    }
};

class FirstTreeNodeData {
public:
    int numOfSongs;
    PlayCountNodeData **songs;

    FirstTreeNodeData() {
        numOfSongs = 0;
        songs = nullptr;
    }

    FirstTreeNodeData(int numOfSongs) : numOfSongs(numOfSongs) {
        songs = new PlayCountNodeData*[numOfSongs];
    }

    ~FirstTreeNodeData() {
        delete[] songs;
    }
};

class SecondTreeNodeData {
public:
    LinkedList<PlayCountNodeData>::ListNode *originNode;
    AVLTree<int, ThirdTreeNodeData> *songTree;
    TreeNode<int, ThirdTreeNodeData> *smallest;

    SecondTreeNodeData() : originNode(nullptr), songTree(nullptr),
                           smallest(nullptr) {};


    SecondTreeNodeData(const SecondTreeNodeData &other) : originNode(other.originNode),
                                                          songTree(other.songTree),
                                                          smallest(other.smallest) {};

    ~SecondTreeNodeData() = default;

    void ChangeSmallest(TreeNode<int, ThirdTreeNodeData> *node) {
        this->smallest = node;
    }
};


class ThirdTreeNodeData {
public:
    TreeNode<int, SecondTreeNodeData> *originArtist;

    ThirdTreeNodeData() : originArtist(nullptr) {};

    ThirdTreeNodeData(TreeNode<int,SecondTreeNodeData> *origin): originArtist(origin){};

    ThirdTreeNodeData(const ThirdTreeNodeData &other) : originArtist(
            other.originArtist) {};

    ~ThirdTreeNodeData() = default;
};

/*LinkedList<PlayCountNodeData>::ListNode PlayCountNode;
TreeNode<int,FirstTreeNodeData> NodeTypeOne;
TreeNode<int,SecondTreeNodeData> NodeTypeTwo;
TreeNode<int,ThirdTreeNodeData> NodeTypeThree;
*/


#endif //WET1_MUSICMANAGER_H
