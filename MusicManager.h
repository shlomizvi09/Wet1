//
// Created by Arik on 12/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "LinkedList.h"
#include "AVLTree.h"
#include "library1.h"

typedef enum MusicManagerResult {
    MM_SUCCESS,
    MM_EXISTS,
    MM_NOT_EXISTS,
    MM_NULL_ARGUMENT,
    MM_BAD_ALLOC,
    MM_FAIL
} MusicManagerResult;

class MusicManager;

class PlayCountNodeData;

class FirstTreeNodeData;

class SecondTreeNodeData;

class ThirdTreeNodeData;

// Music Manager class //

class MusicManager {
    AVLTree<int, FirstTreeNodeData *> *Tree1;
    LinkedList<PlayCountNodeData *> *PlayCountList;
    int TotalSongs;

    friend class PlayCountNodeData;

    friend class FirstTreeNodeData;

    friend class SecondTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    MusicManager() : TotalSongs(0) {
        PlayCountList = new LinkedList<PlayCountNodeData *>();
        Tree1 = new AVLTree<int, FirstTreeNodeData *>();
    }

    ~MusicManager() {
        delete Tree1;
        delete PlayCountList;
    }

    MusicManagerResult AddToSongCount(int artistID, int songID);

    MusicManagerResult AddArtist(int artistID, int numOfSongs);

    MusicManagerResult RemoveArtist(int artistID);

    MusicManagerResult NumberOfStreams(int artistID, int songID, int *streams);

    void DeleteData(TreeNode<int, ThirdTreeNodeData *> *root,
                    TreeNode<int, FirstTreeNodeData *> *node1);

    MusicManagerResult Quit();

    void PatrolTree(TreeNode<int, SecondTreeNodeData *> *root,
                    TreeNode<int, FirstTreeNodeData *> *node1);

    void DeleteMainTree(TreeNode<int, FirstTreeNodeData *> *root);

    MusicManagerResult GetRecommendedSongs(int numOfSongs, int *artists, int *songs);

    void
    PatrolFromSmallestSong(TreeNode<int, ThirdTreeNodeData *> *node3, int numOfSongs, int *artists, int *songs, int
    *counter,int size);

    void PatrolFromSmallestSinger(TreeNode<int, SecondTreeNodeData *> *node2);

};

class PlayCountNodeData {
    int plays;
    AVLTree<int, SecondTreeNodeData *> *singerTree;
    TreeNode<int, class SecondTreeNodeData *> *smallest_singer;

    friend class MusicManager;

    friend class FirstTreeNodeData;

    friend class SecondTreeNodeData;

    friend class ThirdTreeNodeData;

public:

    PlayCountNodeData(int numOfPlays,
                      AVLTree<int, SecondTreeNodeData *> *singerTree,
                      TreeNode<int, class SecondTreeNodeData *> *smallest) : plays
                                                                                     (numOfPlays),
                                                                             singerTree
                                                                                     (singerTree),
                                                                             smallest_singer(
                                                                                     smallest_singer) {};

    /*PlayCountNodeData(const PlayCountNodeData &other) : plays(other.plays),
                                                        singerTree(other.singerTree),
                                                        smallest(other.smallest) {}*/

    PlayCountNodeData() : plays(0), singerTree(nullptr), smallest_singer(nullptr) {}

    PlayCountNodeData(int plays) : plays(plays), singerTree(nullptr), smallest_singer(nullptr) {}

    ~PlayCountNodeData() = default;

    void ChangeSmallest(TreeNode<int, SecondTreeNodeData *> *node) {
        smallest_singer = node;
    }

    void ChangePlays(int plays) {
        this->plays = plays;
    }

    void updateSmallest();

    bool operator==(const PlayCountNodeData *node) const {
        return (this->plays == node->plays);
    }

    bool operator!=(const PlayCountNodeData *node) const {
        return (this->plays != node->plays);
    }
};

class FirstTreeNodeData {
    int numOfSongs;
    LinkedList<PlayCountNodeData *>::ListNode **songs;

    friend class MusicManager;

    friend class PlayCountNodeData;

    friend class SecondTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    FirstTreeNodeData() {
        numOfSongs = 0;
        songs = nullptr;
    }

    FirstTreeNodeData(int numOfSongs) : numOfSongs(numOfSongs) {
        songs = new LinkedList<PlayCountNodeData *>::ListNode *[numOfSongs];
    }

    ~FirstTreeNodeData() {
        delete[] songs;
    }
};

class SecondTreeNodeData {
    LinkedList<PlayCountNodeData *>::ListNode *originNode;
    AVLTree<int, ThirdTreeNodeData *> *songTree;
    TreeNode<int, ThirdTreeNodeData *> *smallest_song;

    friend class MusicManager;

    friend class PlayCountNodeData;

    friend class FirstTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    SecondTreeNodeData() : originNode(nullptr), songTree(nullptr),
                           smallest_song(nullptr) {};

    SecondTreeNodeData(const SecondTreeNodeData &other)
            : originNode(other.originNode),
              songTree(other.songTree),
              smallest_song(other.smallest_song) {};

    SecondTreeNodeData(LinkedList<PlayCountNodeData *>::ListNode *originNode,
                       AVLTree<int, ThirdTreeNodeData *> *songTree,
                       TreeNode<int, ThirdTreeNodeData *> *smallest) : originNode(
            originNode), songTree(songTree),
                                                                       smallest_song(
                                                                               smallest_song) {};

    ~SecondTreeNodeData() = default;

    void setOriginNode(LinkedList<PlayCountNodeData *>::ListNode *new_originNode);

    void UpdateSmallest();
};

class ThirdTreeNodeData {
    TreeNode<int, SecondTreeNodeData *> *originArtist;

    friend class MusicManager;

    friend class PlayCountNodeData;

    friend class FirstTreeNodeData;

    friend class SecondTreeNodeData;

public:
    ThirdTreeNodeData() : originArtist(nullptr) {};

    ThirdTreeNodeData(TreeNode<int, SecondTreeNodeData *> *origin) : originArtist(
            origin) {};

    ThirdTreeNodeData(const ThirdTreeNodeData &other) : originArtist(
            other.originArtist) {};

    ~ThirdTreeNodeData() = default;

    void setOriginArtist(TreeNode<int,
            SecondTreeNodeData *> *new_origin_artist);
};

/*LinkedList<PlayCountNodeData>::ListNode PlayCountNode;
TreeNode<int,FirstTreeNodeData> NodeTypeOne;
TreeNode<int,SecondTreeNodeData> NodeTypeTwo;
TreeNode<int,ThirdTreeNodeData> NodeTypeThree;
*/
// Music Manager functions //-


#endif //WET1_MUSICMANAGER_H
