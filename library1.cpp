#include "library1.h"
#include "MusicManager.h"

using std::bad_alloc;

void *Init() {
  try {
    MusicManager *DS = new MusicManager();
    return (void *) DS;
  }
  catch (...) {
    return nullptr;
  }

}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
  if (numOfSongs <= 0 || DS == nullptr || artistID <= 0)
    return INVALID_INPUT;
  MusicManager *ds = (MusicManager *) DS;
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

StatusType RemoveArtist(void *DS, int artistID) {
  if (DS == nullptr || artistID <= 0)
    return INVALID_INPUT;
  MusicManager *ds = (MusicManager *) DS;
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

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
  if (songID < 0 || DS == nullptr || artistID <= 0)
    return INVALID_INPUT;
  MusicManager *ds = (MusicManager *) DS;
  MusicManagerResult tmpResult;
  try {
    tmpResult = ds->NumberOfStreams(artistID, songID, streams);
  } catch (std::bad_alloc &e) {
    return ALLOCATION_ERROR;
  }
  if (tmpResult == MM_FAIL)
    return INVALID_INPUT;
  if (tmpResult == MM_NOT_EXISTS)
    return FAILURE;
  return SUCCESS;
}

StatusType AddToSongCount(void *DS, int artistID, int songID) {
  if (DS == nullptr || artistID <= 0 || songID < 0) {
    return INVALID_INPUT;
  }
  MusicManager *ds = (MusicManager *) DS;
  MusicManagerResult tmpResult;
  try {
    tmpResult = ds->AddToSongCount(artistID, songID);
  } catch (std::bad_alloc &e) {
    return ALLOCATION_ERROR;
  }
  if (tmpResult == MM_NOT_EXISTS || tmpResult == MM_NULL_ARGUMENT) {
    return FAILURE;
  }
  if (tmpResult == MM_FAIL) {
    return INVALID_INPUT;
  }
  return SUCCESS;
}

void Quit(void **DS) {
  MusicManager *ds = (MusicManager *) *DS;
  if (ds->Quit() == MM_SUCCESS)
    delete ds;
  *DS = nullptr;
}



