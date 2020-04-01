#ifndef __FAVORITE_H__
#define __FAVORITE_H__

#include <stdbool.h>
#include "error.h"
#include "film.h"

// Definition of a favorite structure
typedef struct {
    tFilm film;    
} tFavorite; 

// Data type to hold data related to a film/film in the platform
typedef struct tNode {
    tFavorite e;
    struct tNode *next;
} tFavoriteStackNode;

// Definition of a stack of favorites
typedef struct {
    tFavoriteStackNode *first;
} tFavoriteStack;

// Initialize a tFavorite object
tError favorite_init(tFavorite *object, tFilm film);

// Undo init - release a tFavorite object
void favorite_free(tFavorite *object);

// Duplicate a tFavorite data object
tError favorite_duplicate(tFavorite *dst, tFavorite src);

// Compare two favorites
bool favorite_compare (tFavorite f1, tFavorite f2);

// Duplicate a tFavoriteStack data object
tError favoriteStack_duplicate(tFavoriteStack *dst, tFavoriteStack src);

// Create the stack of favorite elements
void favoriteStack_create(tFavoriteStack *stack);

// Will return true if stack is empty
bool favoriteStack_empty(tFavoriteStack stack);

// Add an element in favorite stack
tError favoriteStack_push(tFavoriteStack *stack, tFavorite favorite);

// Returns a pointer to the element at the top of the stack
// If stack is empty, will return ERR_NOT_FOUND
tError favoriteStack_top(tFavorite *out, tFavoriteStack stack);

// Removes element at the top of the stack
// If empty, will return ERR_INVALID
tError favoriteStack_pop(tFavoriteStack *stack);

// Removes all elements in the stack
void favoriteStack_free(tFavoriteStack *stack);

// Compare two favorites stack
bool favoriteStack_compare(tFavoriteStack stack1, tFavoriteStack stack2);

// Iteratively compares two stacks
// true if they are equal (same elements, in same order)
// Note stacks will be killed (free'd) during compare
bool favoriteStack_compareIterative(tFavoriteStack *stack1, tFavoriteStack *stack2);

// Iteratively compares two stacks
// true if they are equal (same elements, in same order)
// Note stacks will be killed (free'd) during compare
bool favoriteStack_compareRecursive(tFavoriteStack *stack1, tFavoriteStack *stack2); 

// Recursively get the total length of the movies referenced 
unsigned favoriteStack_getFavsLengthInMinRecursive(tFavoriteStack *stack);

// Recursively get number os favorites films of a serie 
unsigned favoriteStack_getFavsCntPerSeriesRecursive(tFavoriteStack *stack, tSeries *serie);

// print the stack in the console
void printStack(tFavoriteStack stack);

// Returns if film is found in stack, according to film_equals()
bool favorite_filmExists(tFavoriteStack *stack, tFilm film);

#endif // __FAVORITE_H__