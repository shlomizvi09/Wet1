//
// Created by Arik on 12/05/2020.
//

#ifndef WET1_MUSICMANNEGER_H
#define WET1_MUSICMANNEGER_H

#include "LinkedList.h"
#include "AVLTree.h"

class MusicManneger;

class PlayCountNode;

class FirstTreeNode;

class SecondTreeNode;

class ThirdTreeNode;

class MusicManneger {
    AVLTree<int, FirstTreeNode> *Tree1;
    LinkedList<PlayCountNode> *PlayCountList;
    int TotalSongs;
public:
    MusicManneger() : TotalSongs(0) {
        Tree1 = new AVLTree<int, FirstTreeNode>;
        PlayCountList = new LinkedList<PlayCountNode>;
    }

    ~MusicManneger(){
        delete Tree1;
        delete PlayCountList;
    }
};



class PlayCountNode {
public:
    int plays;
    AVLTree<int, SecondTreeNode> *singerTree;
    SecondTreeNode *smallest;

    PlayCountNode(int numOfPlays, AVLTree<int, SecondTreeNode> *singerTree,
                  SecondTreeNode *smallest) : plays(numOfPlays), singerTree
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

    bool operator==(const PlayCountNode *node) const {
        return (this->plays == node->plays);
    }
};

class FirstTreeNode {
public:
    int numOfSongs;
    PlayCountNode **songs;

    FirstTreeNode() {
        numOfSongs = 0;
        songs = nullptr;
    }

    FirstTreeNode(int numOfSongs) : numOfSongs(numOfSongs) {
        songs = new PlayCountNode *[numOfSongs];
    }

    FirstTreeNode(const FirstTreeNode &other) :
            numOfSongs(other.numOfSongs) {
        delete[] songs;
        songs = new PlayCountNode *[numOfSongs];
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
    PlayCountNode *originNode;
    AVLTree<int, ThirdTreeNode> *songTree;
    ThirdTreeNode *smallest;

    SecondTreeNode() : originNode(nullptr), songTree(nullptr),
                       smallest(nullptr) {};

    SecondTreeNode(PlayCountNode *origin, AVLTree<int, ThirdTreeNode>
    *songTree, ThirdTreeNode *smallest) : originNode(origin),
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


#endif //WET1_MUSICMANNEGER_H
