#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "user.h"
#include "film.h"
#include "view.h"

// **** Functions related to management of tView objects

// Initialize a tView object
tError view_init(tView* object, tDateTime *timestamp, short score, tUser *user, tFilm *film) {
    // PR1 EX4        
    assert(object != NULL);
    assert(score < 10);
    assert(timestamp->day <= 31);
    assert(timestamp->month <= 12);
    assert(timestamp->hour < 24);
    assert(timestamp->minute <= 60);
    
    tError errUser, errFilm;

    object->timestamp = *timestamp;
    object->score = score;
    
    object->user = (tUser *)malloc(sizeof(tUser));
    errUser = user_init(object->user, user->username, user->name, user->mail);
    
    object->film = (tFilm *)malloc(sizeof(tFilm));
    errFilm = film_init(object->film, film->title, film->lengthInMin, film->series);
    
    if (errUser != OK)
        return errUser;    
    else if (errFilm != OK)
        return errFilm;
    else
        return OK;
}

// Free the resources stored by an existing tView object
void view_free(tView* object) {
    // PR1 EX4    
    if (object->user != NULL) {
        free(object->user);
        object->user = NULL;
    }
    
    if (object->film != NULL) {
        free(object->film);
        object->film = NULL;
    }
}

// **** Functions related to management of tViewLog objects

// Add a new visualization in the table, received as a parameter.
tError viewLog_add(tViewLog* table, tView* view) {
    // PR1 EX4
    //return ERR_NOT_IMPLEMENTED;
    // Verify pre conditions
    assert(table != NULL);
    assert(view != NULL);

    // The first step is to allocate the required space. There are two methods 
    // to manage the memory (malloc and realloc). Malloc allows to allocate a new 
    // memory block, while realloc allows to modify an existing memory block.    
    if (table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size = 1;

        // Since the table is empty, and we do not have any previous memory 
        // block, we have to use malloc. The amount of memory we need is the 
        // number of elements (will be 1) times the size of one element, which 
        // is computed by sizeof(type). In this case the type is tView.
        table->elements = (tView*)malloc(table->size * sizeof(tView));
    }
    else {
        // Table with elements

        // Increase the number of elements of the table
        table->size = table->size + 1;

        // Since the table is not empty, we already have a memory block. 
        // We need to modify the size of this block, using the realloc command. 
        // The amount of memory we need is the number of elements times 
        // the size of one element, which is computed by sizeof(type). 
        // In this case the type is tView. We provide the previous block of memory.
        table->elements = (tView*)realloc(table->elements, table->size * sizeof(tView));
    }

    // Check that the memory has been allocated
    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once we have the block of memory, which is an array 
    // of tView elements, we initialize the new element

    view_init(&(table->elements[table->size - 1]), &view->timestamp, view->score, view->user, view->film);

    return OK;
}

// Initializes a visualization table.
void viewLog_init(tViewLog* table) {
    // PR1 EX4
    // Verify pre conditions
    assert(table != NULL);


    // The initialization of a table is to set it to the empty state. 
    // That is, with 0 elements. 
    table->size = 0;

    // Using dynamic memory, the pointer to the elements must be set 
    // to NULL (no memory allocated). This is the main difference with 
    // respect to the user of static memory, were data was always 
    // initialized (tView elements[MAX_ELEMENTS])
    table->elements = NULL;
}

// Release memory stored by an existing tViewLog object
void viewLog_free(tViewLog* table) {
    // PR1 EX4    

    // Verify pre conditions
    assert(table != NULL);

    // All memory allocated with malloc and realloc needs to be freed 
    // using the free command. In this case, as we use malloc/realloc 
    // to allocate the elements, and need to free them.
    if (table->elements != NULL) {
        free(table->elements);
        table->elements = NULL;
    }


    // As the table is now empty, assign the size to 0.
    table->size = 0;
}

// Given a username and a table of type tViewLog, it performs a search 
// of the episode with the highest score (not negative) displayed by the 
// user, offering us a pointer to it. In case of a tie, offer among the 
// winning genres the episode that is first on the list. 
// If the user can't be found in the list, return NULL.
tFilm *viewLog_getFavFilm(tViewLog* table, tUser* user) {
    // PR1 EX4

    // Verify pre conditions
    assert(table != NULL);
    assert(user != NULL);


    int i;
    tFilm *favFilm = NULL;
    short score = 0;

    if (table->size == 0)
        return NULL;

    for (i = 0; i<table->size; i++){

        if (user_equals(table->elements[i].user, user)) {

            if (score < table->elements[i].score) {
                favFilm = table->elements[i].film;
                score = table->elements[i].score;
            }
        }
    }

    return favFilm;
}


// Given a username and a table of type tViewLog, it returns the 
// genre for which a user has made more visualizations. In case of a tie, 
// offer the first one on the list. In case the user does not have 
// visualizations, return ERR_NOT_FOUND.
tGenre viewLog_getFavGenre(tViewLog* table, tUser* user) {
    // PR1 EX4

    // Verify pre conditions
    assert(table != NULL);
    assert(user != NULL);
    int i;
    int visualizations[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int maxVisualization = 0;
    tFilm *film;
    tSeries *series;
    tGenre genre = 0;

    for (i = 0; i<table->size; i++) {
        if (user_equals(table->elements[i].user, user)) {
            film = table->elements[i].film;
            series = film_getSeries(film);
            genre = series_getGenre(series);
            visualizations[genre]++;
        }
    }

    for (i = 0; i<8; i++) {
        if (visualizations[i] > maxVisualization) {
            genre = i;
            maxVisualization = visualizations[i];
        }
    }

    return genre;

}

// helper func to get tDateTime for a given timestamp in year, month...
tDateTime* setDateTime(unsigned char day, unsigned char month, unsigned short year,
    unsigned char hour, unsigned char minute) {

    assert(month <= 12);
    assert(day <= 31);      // just to keep it simple
    assert(hour < 24);
    assert(minute < 60);

    tDateTime *timestamp;
    timestamp = (tDateTime*)malloc(sizeof(tDateTime));

    timestamp->year = year;
    timestamp->month = month;
    timestamp->day = day;

    timestamp->hour = hour;
    timestamp->minute = minute;

    return timestamp;
}