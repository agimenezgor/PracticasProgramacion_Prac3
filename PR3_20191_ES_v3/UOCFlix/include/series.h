#ifndef __SERIES_H__
#define __SERIES_H__

#include <stdbool.h>
#include "error.h"

typedef enum {
    GENRE_NOT_FOUND = 0,
    SCIENCE_FICTION = 1,
    COMEDY = 2,
    DRAMA = 3,
    MISTERY = 4,
    ACTION = 5,
    ADVENTURE = 6,
    CRIME = 7,
    GENRE_QTY = 8  // This value allows to loop over tGenre types
} tGenre;

// Data type to hold data related to a Series in the platform
typedef struct {
    char* title;
    tGenre genre;    
} tSeries;

// Initialize a series object
tError series_init(tSeries* object, const char* title, tGenre genre);

// Releases memory allocated within a tSeries object
void series_free(tSeries* object);

// Returns title string of a tSeries object
const char* series_getTitle(tSeries* object);

// Returns genre in a tSeries object
tGenre series_getGenre(tSeries* object);

// Change the title field of a tSeries object
tError series_mdfyTitle(tSeries* object, const char* newTitle); 

// Compare two tSeries objects for equality, by their title
bool series_equals(tSeries* serie1, tSeries* serie2);

/*  
Copy the content of a source tSeries data, to another destination tSeries data.
Both origin and destination must be previously instantiated (calling
series_init () over your pointer)
*/
tError series_cpy(tSeries* dst, tSeries* src); 

#endif // __SERIES_H__