#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "series.h"
#include "film.h"

// Initialize the user structure
tError film_init(tFilm* object, const char* title, const unsigned int lengthInMin, tSeries *series) {

    // Verify pre conditions
    assert(object != NULL);
    assert(series != NULL);

    object->title = (char*)malloc((strlen(title) + 1) * sizeof(char));

    if (object->title == NULL) {
        return ERR_MEMORY_ERROR;
    }

    strcpy(object->title, title);

    object->lengthInMin = lengthInMin;
    object->series = series;

    return OK;
}


// Releases memory allocated within a tFilm object
void film_free(tFilm* object) {

    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed 
    // using the free command. In this case, as we use malloc to 
    // allocate the fields, we have to free them
    if (object->title != NULL) {
        free(object->title);
        object->title = NULL;
    }
}

// Compare two tFilm objects by their title
bool film_equals(tFilm* film1, tFilm* film2) {

    // Verify pre conditions
    assert(film1 != NULL);
    assert(film2 != NULL);

    if (strcmp(film1->title, film2->title) != 0) {
        // Titles are different
        return false;
    }

    return true;
}

// Copy the data of a film to another film
tError film_cpy(tFilm* dst, tFilm* src) {

    // Verify pre conditions
    assert(dst != NULL);
    assert(src != NULL);

    // Just in case, free space used by destination object.
    film_free(dst);

    // Initialize the element with the new data
    return film_init(dst, src->title, src->lengthInMin, src->series);
}


// Get ptr to series to which this film belongs
tSeries* film_getSeries(tFilm* object) {

    // Verify pre conditions
    assert(object != NULL);

    return object->series;
}

// **** Functions related to management of tFilmTable objects

// Initializes a table of films
void filmTable_init(tFilmTable* table) {

    // Verify pre conditions
    assert(table != NULL);
    // The initialization of a table is to set it to the empty state. 
    // That is, with 0 elements. 
    table->size = 0;

    // Using dynamic memory, the pointer to the elements must be set to NULL 
    // (no memory allocated). This is the main difference with respect to 
    // the user of static memory, were data was allways initialized 
    // (tFilm elements[MAX_ELEMENTS])
    table->elements = NULL;
}


// Free resources stored by an existing tFilmTable data type.
void filmTable_free(tFilmTable* object) {
    // PR1 EX3

    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using 
    // the free command. In this case, as we use malloc/realloc to 
    // allocate the elements, and need to free them.
    if (object->elements != NULL) {
        free(object->elements);
        object->elements = NULL;
    }
    // As the table is now empty, assign the size to 0.
    object->size = 0;

}


// Add a new film in the table. In case the film already exists (same title), 
// it will return an error value ERR_DUPLICATED.
tError filmTable_add(tFilmTable* table, tFilm* film) {

    // PR1 EX3    
    int i;
    // Verify pre conditions
    assert(table != NULL);
    assert(film != NULL);

    for (i = 0; i<table->size; i++) {

        if (strcmp(table->elements[i].title, film->title) == 0) {
            return ERR_DUPLICATED;
        }
    }

    // The first step is to allocate the required space. There are two methods 
    // to manage the memory (malloc and realloc). Malloc allows to allocate a 
    // new memory block, while realloc allows to modify an existing memory block.    
    if (table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size = 1;

        // Since the table is empty, and we do not have any previous memory block, 
        // we have to use malloc. The amount of memory we need is the number of 
        // elements (will be 1) times the size of one element, which is computed 
        // by sizeof(type). In this case the type is tFilm.
        table->elements = (tFilm*)malloc(table->size * sizeof(tFilm));
    }
    else {
        // Table with elements

        // Increase the number of elements of the table
        table->size = table->size + 1;

        // Since the table is not empty, we already have a memory block. 
        // We need to modify the size of this block, using the realloc 
        // command. The amount of memory we need is the number of elements 
        // times the size of one element, which is computed by sizeof(type). 
        // In this case the type is tFilm. 
        // We provide the previous block of memory.
        table->elements = (tFilm*)realloc(table->elements, table->size * sizeof(tFilm));
    }

    // Check that the memory has been allocated
    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once we have the block of memory, which is an array of tFilm elements, 
    // we initialize the new element
    film_init(&(table->elements[table->size - 1]), film->title, film->lengthInMin, film->series);

    return OK;
}


/* a search for an film in the table received as a parameter, by its title.
* It will return a pointer to the tFilm type data if found, or NULL otherwise.
*/
tFilm* filmTable_find(tFilmTable* table, const char* title) {
    // PR1 EX3
    //return NULL;
    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(title != NULL);

    // Search over the table and return once we found the element.
    for (i = 0; i<table->size; i++) {
        if (strcmp(table->elements[i].title, title) == 0) {
            // We return the ADDRESS (&) of the element, 
            // which is a pointer to the element
            return &(table->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;

}

/* Removes an film received as a parameter from the table, based on its title.
* If an attempt is made to delete a device that
* does not exist in the table, the error value ERR_NOT_FOUND will be returned.
* Otherwise, it will return the OK value. If there is a problem managing memory,
* this function will return an error value ERR_MEMORY_ERROR.
*/
tError filmTable_remove(tFilmTable* table, tFilm* film){
    int i;
    bool found;

    // Verify pre conditions
    assert(table != NULL);
    assert(film != NULL);

    // To remove an element of a table, we will move all elements after this element 
    // one position, to fill the space of the removed element.
    found = false;
    for (i = 0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element 
        // (will never happend for the first one). We use the ADDRESS of the previous 
        // element &(table->elements[i-1]) as destination, and ADDRESS of the current 
        // element &(table->elements[i]) as source.
        if (found) {
            // Check the return code to detect memory allocation errors
            if (film_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        }
        else if (strcmp(table->elements[i].title, film->title) == 0) {
            // The current element is the element we want to remove. 
            // Set found flag to true to start element movement.
            found = true;
        }
    }

    // Once removed the element, we need to modify the memory used by the table.
    if (found) {
        // Modify the number of elements
        table->size = table->size - 1;

        // If we are removing the last element, we will assign the pointer 
        // to NULL, since we cannot allocate zero bytes
        if (table->size == 0) {
            table->elements = NULL;
        }
        else {
            // Modify the used memory. As we are modifying a previously 
            // allocated block, we need to use the realloc command.
            table->elements = (tFilm*)realloc(table->elements, table->size * sizeof(tFilm));

            // Check that the memory has been allocated
            if (table->elements == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            }
        }
    }
    else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }

    return OK;
}

// Returns the number of films in the tFilmTable table received as a parameter.
unsigned int filmTable_size(tFilmTable* table){

    // PR1 EX3
    //return 0;

    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. 
    // This value is stored in the "size" field.
    return table->size;

}

