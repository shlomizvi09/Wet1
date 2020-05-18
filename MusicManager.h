//
// Created by Arik on 12/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "LinkedList.h"
#include "AVLTree.h"
#include "library1.h"

// possible results of our data structure //
typedef enum MusicManagerResult {
    MM_SUCCESS,
    MM_EXISTS,
    MM_NOT_EXISTS,
    MM_NULL_ARGUMENT,
    MM_BAD_ALLOC,
    MM_FAIL
} MusicManagerResult;

// Data structure that hold all the singer and their song //
class MusicManager;

// Data contained on the linked list, which is determined by number of plays of its songs and the smallest singer //
class PlayCountNodeData;

// a singer, number of song he has, and an array of pointers to determine how many streams each song has //
class FirstTreeNodeData;

// a singer, originNode of number of plays, all his songs that has that number of plays, and pointer so smallest
// song  //
class SecondTreeNodeData;

// a song that has a certain number of plays and a pointer to the artist performing this song //
class ThirdTreeNodeData;

// Music Manager class //
class MusicManager {
    AVLTree<int, FirstTreeNodeData *> *Tree1;       // main Tree //
    LinkedList<PlayCountNodeData *> *PlayCountList; // play count list //
    int TotalSongs;                                 // total amount of songs at the system //

    friend class PlayCountNodeData;

    friend class FirstTreeNodeData;

    friend class SecondTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    // default constructor //
    MusicManager() : TotalSongs(0) {
        PlayCountList = new LinkedList<PlayCountNodeData *>();
        Tree1 = new AVLTree<int, FirstTreeNodeData *>();
    }

    // default destructor //
    ~MusicManager() {
        delete Tree1;
        delete PlayCountList;
    }

    // adds one play to a given song of a given artist //
    MusicManagerResult AddToSongCount(int artistID, int songID);

    // inserts an artist with all his song //
    MusicManagerResult AddArtist(int artistID, int numOfSongs);

    // removes an artist with all his songs //
    MusicManagerResult RemoveArtist(int artistID);

    // return the number of streams of a given song to *streams //
    MusicManagerResult NumberOfStreams(int artistID, int songID, int *streams);

    // deletes the data in all the nodes of a type 3 tree //
    void DeleteData(TreeNode<int, ThirdTreeNodeData *> *root,
                    TreeNode<int, FirstTreeNodeData *> *node1);

    // removes all artists and their songs from MusicManager //
    MusicManagerResult Quit();

    // deletes the data of a given type 2 tree //
    void PatrolTree(TreeNode<int, SecondTreeNodeData *> *root,
                    TreeNode<int, FirstTreeNodeData *> *node1);

    // deletes the data of type 1 tree //
    void DeleteMainTree(TreeNode<int, FirstTreeNodeData *> *root);

    // writes the numOfSongs most played songs in MusicManager to *artists and *songs in the right order //
    MusicManagerResult GetRecommendedSongs(int numOfSongs, int *artists, int *songs);

    // goes through type 3 tree from his smallest node and updates *artists and *songs in the right order //
    void
    PatrolFromSmallestSong(TreeNode<int, ThirdTreeNodeData *> *node3, int numOfSongs, int *artists, int *songs, int
    *counter, int size);

    // goes through type 2 tree from his smallest and calls "PatrolFromSmallestSong" in each nude //
    void PatrolFromSmallestSinger(TreeNode<int, SecondTreeNodeData *> *node2, int numOfSongs, int *artists, int
    *songs, int *counter, int size);


};

class PlayCountNodeData {
    int plays;                                               // all the songs of this nude have plays number of streams //
    AVLTree<int, SecondTreeNodeData *> *singerTree;          // pointer to singer tree //
    TreeNode<int, SecondTreeNodeData *> *smallest_singer;    // pointer to the smallest singer //

    friend class MusicManager;

    friend class FirstTreeNodeData;

    friend class SecondTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    // constructor the gets all the fields of PlayCountNodeData //
    PlayCountNodeData(int numOfPlays,
                      AVLTree<int, SecondTreeNodeData *> *singerTree,
                      TreeNode<int, class SecondTreeNodeData *> *smallest_singer) : plays
                                                                                            (numOfPlays),
                                                                                    singerTree
                                                                                            (singerTree),
                                                                                    smallest_singer(smallest_singer) {};

    // default constructor //
    PlayCountNodeData() : plays(0), singerTree(nullptr), smallest_singer(nullptr) {}

    // constructor that gets only number of plays //
    PlayCountNodeData(int plays) : plays(plays), singerTree(nullptr), smallest_singer(nullptr) {}

    // default destructor //
    ~PlayCountNodeData() {
     //   printf("play_node_data_delete\n");
    }

    // when called, updates the smallest singer in the type 2 tree //
    void updateSmallest();
};

class FirstTreeNodeData {
    int numOfSongs;                                     // number of songs that the singer has //
    LinkedList<PlayCountNodeData *>::ListNode **songs;  // array of pointers, which determines the number of stream each
    // cell has (cell index represents a song index) //

    friend class MusicManager;

    friend class PlayCountNodeData;

    friend class SecondTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    // default constructor //
    FirstTreeNodeData() {
        numOfSongs = 0;
        songs = nullptr;
    }

    // constructor that gets the number of songs the artist has //
    FirstTreeNodeData(int numOfSongs) : numOfSongs(numOfSongs) {
        songs = new LinkedList<PlayCountNodeData *>::ListNode *[numOfSongs];
    }

    // destructor //
    ~FirstTreeNodeData() {
        delete[] songs;
     //   printf("first_node_data_delete\n");

    }
};

class SecondTreeNodeData {
    LinkedList<PlayCountNodeData *>::ListNode *originNode; // num of plays node that artist have //
    AVLTree<int, ThirdTreeNodeData *> *songTree;           // all songs this artists have with given streams //
    TreeNode<int, ThirdTreeNodeData *> *smallest_song;     // smallest ID of a song //

    friend class MusicManager;

    friend class PlayCountNodeData;

    friend class FirstTreeNodeData;

    friend class ThirdTreeNodeData;

public:
    // default constructor //
    SecondTreeNodeData() : originNode(nullptr), songTree(nullptr),
                           smallest_song(nullptr) {};

    // copy constructor //
    SecondTreeNodeData(const SecondTreeNodeData &other)
            : originNode(other.originNode),
              songTree(other.songTree),
              smallest_song(other.smallest_song) {};

    // constructor that gets al ths fields //
    SecondTreeNodeData(LinkedList<PlayCountNodeData *>::ListNode *originNode,
                       AVLTree<int, ThirdTreeNodeData *> *songTree,
                       TreeNode<int, ThirdTreeNodeData *> *smallest_song) : originNode(
            originNode), songTree(songTree),
                                                                            smallest_song(
                                                                                    smallest_song) {};

    // default destructor //
    ~SecondTreeNodeData(){
     //   printf("second_node_data_delete\n");

    }

    // changes his origin node to be *new_originNode //
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

    ~ThirdTreeNodeData(){
        printf("third_node_data_delete\n");

    }

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
