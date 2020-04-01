#ifndef __POPULARITY_H__
#define __POPULARITY_H__

#include "film.h"
#include "favorite.h"
#include "user.h"
#include "view.h"

typedef struct {
    unsigned int numUserViews;
    unsigned int numUserFavorited;
} tFilmStats;

// Definition of popularity element
typedef struct {
    tFilm film;
    tFilmStats stats;
} tPopularity;

// Definition of a node for a double-linked list
typedef struct _tPopularityListNode {
    tPopularity e;
    struct _tPopularityListNode* next;
    struct _tPopularityListNode* prev;
} tPopularityListNode;

// Definition of a list of ratings
typedef struct {
    tPopularityListNode* first;
    tPopularityListNode* last;
    int size;
} tPopularityList;

// Number of views of a certain film on a viewLog
unsigned int popularity_getCntView(tViewLog *viewLog, tFilm *film);

// Number of users with that film in their favs' stack - assumes each user is 
// only once in table
unsigned int popularity_getCntUsrFavd(tUserTable *userTable, tFilm *film);

// Get stats of a film, based on viewLog and favorite contents of 
// users in userTable
tFilmStats popularity_getFilmStats(tViewLog *viewLog, tUserTable *userTable, tFilm *film);

// Creates a popularity element out of a film and a stats
tError popularity_init(tPopularity* object, tFilmStats fs, tFilm film);

// Releases data pointed by popularity element
void popularity_free(tPopularity* object);

// Compare stats of two films, 1 if s1 wins, -1 if s2 wins, 0 if tie
int popularity_compare(tFilmStats s1, tFilmStats s2);

// Create the popularity list
void popularityList_create(tPopularityList* list);

// Insert/adds a new popularity to the popularity list
tError popularityList_insert(tPopularityList* list, tPopularity popularity, int index);

// Deletes a popularity from the popularity list
tError popularityList_delete(tPopularityList* list, int index);

// Gets popularity from given position, NULL if out of bounds
tPopularityListNode* popularityList_get(tPopularityList* list, int index);

// Gets true if list is empty
bool popularityList_empty(tPopularityList* list);

// Remove all data for a popularity list
void popularityList_free(tPopularityList* list);

// given a list of films' popularity, returns the position of the film in the list
int popularityList_getPosByFilm(tPopularityList* list, tFilm *film);

// Swap two elements in the list
tError popularityList_swap(tPopularityList* list, int index_dst, int index_src);

// Sorts input list using bubbleSort algorithm
tError popularityList_bubbleSort(tPopularityList *list);

// Helper function, print list contents
void popularityList_print(tPopularityList list);

#endif // __POPULARITY_H__