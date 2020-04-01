#ifndef __FILM_H__
#define __FILM_H__

#include "series.h"

// Data type to hold data related to a film/film in the platform
typedef struct { 
    char* title;    
    unsigned short lengthInMin;
    tSeries *series;
} tFilm;

// Table of tFilm elements
typedef struct {
    unsigned int size;    
    tFilm* elements;
} tFilmTable;

// **** Functions related to management of tFilm objects

// Initialize the user structure
tError film_init(tFilm* object, const char* title, const unsigned int lengthInMin, tSeries *series);

// Releases memory allocated within a tFilm object
void film_free(tFilm* object);

// Compare two tFilm objects by their title
bool film_equals(tFilm* film1, tFilm* film2);

// Copy the data of a film to another film
tError film_cpy(tFilm* dst, tFilm* src);

// Get ptr to series to which this film belongs
tSeries* film_getSeries(tFilm* object);

// **** Functions related to management of tFilmTable objects

// Initializes a table of films
void filmTable_init(tFilmTable* table);

// Free resources stored by an existing tFilmTable data type.
void filmTable_free(tFilmTable* table);

// Add a new film in the table. In case the film already exists (same title), it will return an error value ERR_DUPLICATED.
tError filmTable_add(tFilmTable* table, tFilm* film);

 /* a search for an film in the table received as a parameter, by its title. 
  * It will return a pointer to the tFilm type data if found, or NULL otherwise.
  */
tFilm* filmTable_find (tFilmTable* table, const char* title);

/* Removes an film received as a parameter from the table, based on its 
 * title. If an attempt is made to delete a device that 
 * does not exist in the table, the error value ERR_NOT_FOUND will be returned. 
 * Otherwise, it will return the OK value. If there is a problem managing memory, 
 * this function will return an error value ERR_MEMORY_ERROR.
 */
tError filmTable_remove(tFilmTable* table, tFilm* film);

// Returns the number of films in the tFilmTable table received as a parameter.
unsigned int filmTable_size(tFilmTable* table);

#endif // __FILM_H__
