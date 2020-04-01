#ifndef __VIEW__H__
#define __VIEW__H__

#include <stdbool.h>
#include "error.h"
#include "user.h"
#include "film.h"

typedef struct {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
} tDateTime;

// Data type to hold data related to a View in the platform
typedef struct {       
    tUser *user;
    tFilm *film;
    tDateTime timestamp;
    unsigned short minutes;
    short score;
} tView;

// Table of tView objects
typedef struct {
    unsigned int size;
    tView* elements;
} tViewLog;

// **** Functions related to management of tView objects

// Initialize a tView object
tError view_init(tView* view, tDateTime *timestamp, short score, tUser *user, tFilm *film); 
    
// Free the resources stored by an existing tView object
void view_free(tView* object);

// **** Functions related to management of tViewLog objects

// Add a new visualization in the table, received as a parameter.
tError viewLog_add(tViewLog* table, tView* view);

// Initializes a visualization table.
void viewLog_init(tViewLog* table);

// Release memory stored by an existing tViewLog object
void viewLog_free(tViewLog* table);

// Given a username and a table of type tViewLog, it performs a search 
// of the episode with the highest score (not negative) displayed by the 
// user, offering us a pointer to it. In case of a tie, offer among the 
// winning genres the episode that is first on the list. 
// If the user can't be found in the list, return NULL.
tFilm *viewLog_getFavFilm(tViewLog* object, tUser* user);

// Given a username and a table of type tViewLog, it returns the 
// genre for which a user has made more visualizations. In case of a tie, 
// offer the first one on the list. In case the user does not have 
// visualizations, return ERR_NOT_FOUND.
tGenre viewLog_getFavGenre(tViewLog* table, tUser* user); 

// helper func to get tDateTime for a given timestamp in year, month...
tDateTime* setDateTime(unsigned char day, unsigned char month, unsigned short year, 
                        unsigned char hour, unsigned char minute);

#endif // __VIEW___H__