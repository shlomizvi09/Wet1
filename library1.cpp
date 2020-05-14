#include "library1.h"
#include "MusicManager.h"
using std::bad_alloc;

void *Init() {
    MusicManager *DS;
    try {
        DS = new MusicManager();
    }
    catch (...) {
        DS = nullptr;
    }

    return (void *) DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (numOfSongs <= 0 || DS == nullptr || artistID <= 0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *)DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->AddArtist(artistID, numOfSongs);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_EXISTS)
        return FAILURE;
    return SUCCESS;
}

StatusType RemoveArtist(void *DS, int artistID){
    if(DS== nullptr||artistID<=0)
        return INVALID_INPUT;
    MusicManager *ds = (MusicManager *)DS;
    MusicManagerResult tmpResult;
    try {
        tmpResult = ds->RemoveArtist(artistID);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    }
    if (tmpResult == MM_NOT_EXISTS)
        return FAILURE;
    return SUCCESS;
}


