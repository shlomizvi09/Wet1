//
// Created by Arik on 12/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "LinkedList.h"
#include "AVLTree.h"
#include "library1.h"

class MusicManager;

class PlayCountNode;

class FirstTreeNode;

class SecondTreeNode;

class ThirdTreeNode;

// Music Manager struct //

class MusicManager {
public:
    AVLTree<int, FirstTreeNode> *Tree1;
    LinkedList<PlayCountNode> *PlayCountList;
    int TotalSongs;

    MusicManager() : TotalSongs(0) {
        Tree1 = new AVLTree<int, FirstTreeNode>;
        PlayCountList = new LinkedList<PlayCountNode>;
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


class PlayCountNode {
public:
    int plays;
    AVLTree<int, SecondTreeNode> *singerTree;
    TreeNode<int, class SecondTreeNode> *smallest;

    PlayCountNode(int numOfPlays, AVLTree<int, SecondTreeNode> *singerTree,
                  TreeNode<int, class SecondTreeNode> *smallest) : plays
                  (numOfPlays), singerTree
            (singerTree), smallest(smallest) {};

    PlayCountNode(const PlayCountNode &other) : plays(other.plays),
                                                singerTree(other.singerTree),
                                                smallest(other.smallest) {}

    PlayCountNode() {
        plays = 0;
        singerTree = nullptr;
        smallest = nullptr;
    }

    ~PlayCountNode() = default;

    void ChangeSmallest(TreeNode<int, class SecondTreeNode> *node){
        smallest=node;
    }

    bool operator==(const PlayCountNode *node) const {
        return (this->plays == node->plays);
    }

    bool operator!=(const PlayCountNode *node) const {
        return (this->plays != node->plays);
    }
};

class FirstTreeNode {
public:
    int numOfSongs;
    LinkedList<PlayCountNode>::ListNode **songs;

    FirstTreeNode() {
        numOfSongs = 0;
        songs = nullptr;
    }

    FirstTreeNode(int numOfSongs) : numOfSongs(numOfSongs) {
        songs = new LinkedList<PlayCountNode>::ListNode *[numOfSongs];
    }

    FirstTreeNode(const FirstTreeNode &other) :
            numOfSongs(other.numOfSongs) {
        delete[] songs;
        songs = new LinkedList<PlayCountNode>::ListNode *[numOfSongs];
        for (int i = 0; i < numOfSongs; ++i) {
            songs[i] = other.songs[i];
        }
    }

    ~FirstTreeNode() {
        delete[] songs;
    }
};

class SecondTreeNode {
public:
    LinkedList<struct PlayCountNode>::ListNode *originNode;
    AVLTree<int, ThirdTreeNode> *songTree;
    TreeNode<int, class ThirdTreeNode> *smallest;

    SecondTreeNode() : originNode(nullptr), songTree(nullptr),
                       smallest(nullptr) {};

    SecondTreeNode(LinkedList<class PlayCountNode>::ListNode *origin,
            AVLTree<int, ThirdTreeNode>
    *songTree, TreeNode<int, class ThirdTreeNode> *smallest) : originNode
    (origin),
                                                                songTree(songTree),
                                                                smallest(smallest) {};

    SecondTreeNode(const SecondTreeNode &other) : originNode(other.originNode),
                                                  songTree(other.songTree),
                                                  smallest(other.smallest) {};

    ~SecondTreeNode() = default;
};


class ThirdTreeNode {
public:
    SecondTreeNode *originArtist;

    ThirdTreeNode() : originArtist(nullptr) {};

    ThirdTreeNode(SecondTreeNode *origin) : originArtist(origin) {};

    ThirdTreeNode(const ThirdTreeNode &other) : originArtist(
            other.originArtist) {};

    ~ThirdTreeNode() = default;
};


#endif //WET1_MUSICMANAGER_H
