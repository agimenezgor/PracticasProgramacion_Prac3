#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "favorite.h"
#include "film.h"

// Initialize a tFavorite object
tError favorite_init(tFavorite *object, tFilm film) {

    assert(object != NULL);
    assert(film.title != NULL);
    assert(film.series != NULL);

    return film_init(&object->film, film.title, film.lengthInMin, film.series);
}

// Release a tFavorite object
void favorite_free(tFavorite *object) {

    if (object != NULL) {
        film_free(&object->film);
    }

    // Note we do not free(object), as we assumed that in favorite_init(..), it was received as allocated/existing
}

// Duplicate a tFavorite data object
tError favorite_duplicate(tFavorite *dst, tFavorite src) {

    assert(dst != NULL);
    assert(src.film.title != NULL);
    assert(src.film.series != NULL);

    return favorite_init(dst, src.film);
}

// Duplicate a tFavoriteStack / makes a copy
tError favoriteStack_duplicate(tFavoriteStack *dst, tFavoriteStack src) {

    tFavoriteStackNode *nodeR, *nodeW;

    // Initialize new stack
    favoriteStack_create(dst);

    // Read and instantiate (if needed), first node in dst
    // Read pointer in nodeR (original stack)
    // Write pointer in nodeW (duplicated stack)
    nodeR = src.first;

    if (nodeR == NULL)
        return OK;  // leave empty, as original stack is empty

    dst->first = (tFavoriteStackNode*)malloc(sizeof(tFavoriteStackNode));
    nodeW = dst->first;

    while (1) {
        favorite_duplicate(&(nodeW->e), nodeR->e);

        // Create new node in new stack, if still another node
        // in input stack
        if (nodeR->next != NULL) {
            nodeW->next = (tFavoriteStackNode*)malloc(sizeof(tFavoriteStackNode));

            if (nodeW->next == NULL)
                return ERR_MEMORY_ERROR;

            // place write pointer
            nodeW = nodeW->next;
            // move read pointer to next position
            nodeR = nodeR->next;
        }
        else {
            nodeW->next = NULL;     // stack ends here
            break;  // exit loop
        }
    }

    return OK;
}


// Create the stack of favorite elements
void favoriteStack_create(tFavoriteStack *stack) {
    // PR2 EX1
    assert(stack != NULL);

    stack->first = NULL;
}

// Will return true if stack is empty
bool favoriteStack_empty(tFavoriteStack stack) {
    // PR2 EX1
    return (stack.first == NULL);
}

// Add an element in favorite stack
tError favoriteStack_push(tFavoriteStack *stack, tFavorite favorite) {
    // PR2 EX1
    tFavoriteStackNode *newNode;
    tError err;

    // create a new stack node that will be added in the stack: Reserve memory
    newNode = (tFavoriteStackNode *)malloc(sizeof(tFavoriteStackNode));

    if (newNode == NULL)
        return ERR_MEMORY_ERROR;

    // create a new favorite in that node
    err = favorite_init(&newNode->e, favorite.film);

    if (err != OK)
        return ERR_MEMORY_ERROR;

    // create a new node that will be added in the stack: Fill contents
    err = favorite_duplicate(&newNode->e, favorite);

    if (err != OK)
        return err;

    // insert in first position
    newNode->next = stack->first;
    stack->first = newNode;

    return OK;
}

// Returns a pointer to the element at the top of the stack
// If stack is empty, will return ERR_NOT_FOUND
tError favoriteStack_top(tFavorite *out, tFavoriteStack stack) {
    // PR2 EX2    
    if (favoriteStack_empty(stack)) {
        return ERR_NOT_FOUND;
    }

    return favorite_duplicate(out, stack.first->e);
}

// Removes element at the top of the stack
// If empty, will return ERR_INVALID
tError favoriteStack_pop(tFavoriteStack *stack) {
    // PR2 EX2
    tFavoriteStackNode *node = NULL;

    if (stack->first == NULL)
        return ERR_INVALID;

    node = stack->first;
    stack->first = stack->first->next;

    favorite_free(&(node->e));
    free(node);

    return OK;
}


// Removes all elements in the stack
void favoriteStack_free(tFavoriteStack *stack) {
    // PR2 EX2
    assert(stack != NULL);

    tFavoriteStackNode *currNode = NULL;
    tFavoriteStackNode *nextNode = NULL;

    currNode = stack->first;

    while (currNode != NULL) {
        nextNode = currNode->next;

        free(currNode);

        currNode = nextNode;
    }

    stack->first = NULL;
}

// Compare two favorites stack
bool favoriteStack_compare(tFavoriteStack stack1, tFavoriteStack stack2) {
    bool equals;
    tFavoriteStack f1_dup, f2_dup;

    // Make a copy of the stacks to avoid modifications
    favoriteStack_duplicate(&f1_dup, stack1);
    favoriteStack_duplicate(&f2_dup, stack2);

    // Compare both queues
    //equals = favoriteStack_compareRecursive(&f1_dup, &f2_dup);
    equals = favoriteStack_compareIterative(&f1_dup, &f2_dup);

    // Remove the remaining elements
    favoriteStack_free(&f1_dup);
    favoriteStack_free(&f2_dup);

    return equals;
}

// Iteratively compares two stacks
// true if they are equal (same elements, in same order)
// Note stacks will be killed (free'd) during compare
bool favoriteStack_compareIterative(tFavoriteStack *stack1, tFavoriteStack *stack2) {
    bool equals = true;
    tFavorite f1, f2;

    // Check base cases:
    // 1) Both stacks are empty
    if (favoriteStack_empty(*stack1) && favoriteStack_empty(*stack2)) {
        return true;
    }
    // 2) One stack is empty and the other not
    if (favoriteStack_empty(*stack1) || favoriteStack_empty(*stack2)) {
        return false;
    }

    // While the stacks have elements and all previous elements were equal, check for next elements    
    while (equals && !favoriteStack_empty(*stack1)
        && !favoriteStack_empty(*stack2)) {
        // Check if one of the stacks is empty
        if ((favoriteStack_empty(*stack1) && !favoriteStack_empty(*stack2))
            || (!favoriteStack_empty(*stack1) && favoriteStack_empty(*stack2))) {
            // Stacks have different number of elements
            equals = false;
        }
        else {
            // Both stacks have elements. 
            // Take top elements
            favoriteStack_top(&f1, *stack1);
            favoriteStack_top(&f2, *stack2);

            // Compare the headers
            if (!favorite_compare(f1, f2)) {
                // The elements are different.
                equals = false;
            }

            // Remove head elements from stacks
            favoriteStack_pop(stack1);
            favoriteStack_pop(stack2);
        }
    }

    return equals;

}

// Iteratively compares two stacks
// true if they are equal (same elements, in same order)
// Note stacks will be killed (free'd) during compare
bool favoriteStack_compareRecursive(tFavoriteStack *stack1, tFavoriteStack *stack2) {

    tFavorite f1, f2;

    // Check base cases:
    // 1) Both stacks are empty
    if (favoriteStack_empty(*stack1) && favoriteStack_empty(*stack2)) {
        return true;
    }

    // 2) One stack is empty and the other not
    if (favoriteStack_empty(*stack1) || favoriteStack_empty(*stack2)) {
        return false;
    }

    // 3) The head elements of the stack are different
    // Take head elements
    favoriteStack_top(&f1, *stack1);
    favoriteStack_top(&f2, *stack2);


    // compare the head elements
    if (!favorite_compare(f1, f2)) {
        // The elements are different.
        return false;
    }

    // Remove head elements from stack
    favoriteStack_pop(stack1);
    favoriteStack_pop(stack2);

    // Recursion. Two stacks are equal if the heads are equal and the stacks without the head are equal. 
    // Compare the remaining stacks once removed their elements the head.        
    return favoriteStack_compareRecursive(stack1, stack2);
}

// Compare two favorites
bool favorite_compare(tFavorite f1, tFavorite f2) {
    // Compare the values of both structures    
    return film_equals(&f1.film, &f2.film);
}

// Recursively get the total length of the movies referenced 
unsigned favoriteStack_getFavsLengthInMinRecursive(tFavoriteStack *stack){
    tFavorite f;

    // Check base cases:

    // stacks is empty
    if (favoriteStack_empty(*stack)) {
        return 0;
    }

    // Take head elements
    favoriteStack_top(&f, *stack);

    // Remove head element from stack
    favoriteStack_pop(stack);

    // Recursion. 
    return f.film.lengthInMin + favoriteStack_getFavsLengthInMinRecursive(stack);
}

// Recursively get number os favorites films of a serie 
unsigned favoriteStack_getFavsCntPerSeriesRecursive(tFavoriteStack *stack, tSeries *serie){
    tFavorite f;
    int cnt = 0;

    // Check base cases:
    // stacks is empty
    if (favoriteStack_empty(*stack)) {
        return 0;
    }

    // Take head elements
    favoriteStack_top(&f, *stack);

    if (f.film.series != NULL && series_equals(f.film.series, serie)){
        cnt = 1;
    }
    // Remove head elements from stack
    favoriteStack_pop(stack);

    // Recursion.
    return cnt + favoriteStack_getFavsCntPerSeriesRecursive(stack, serie);
}

// Helper function - Print a stack in the console - use for debugging
void printStack(tFavoriteStack stack) {
    tFavoriteStackNode *nodePtr = stack.first;
    int i = 0;

    while (nodePtr != NULL) {
        printf("%d %s - %s \n", i, nodePtr->e.film.title, nodePtr->e.film.series->title);
        nodePtr = nodePtr->next;
        i++;
    }

    printf("\n");
}

// Returns if film is found in stack, according to film_equals()
bool favorite_filmExists(tFavoriteStack *stack, tFilm film) {
    // PR3_EX1
	// Check preconditions
	assert(stack != NULL);
	
	// Declar an auxiliar stack
	tFavoriteStack *stackAux;
	stackAux = (tFavoriteStack *)malloc(sizeof(tFavoriteStack));
	favoriteStack_create(stackAux);
	favoriteStack_duplicate(stackAux, *stack);
	
	// Check if the stack are empty
	bool stackEmpty = false;
	if(stackAux->first == NULL){
		stackEmpty = true;
	}
	
	// Boolean to know if the films are equals
	bool equals = false;
	
	// Find in the stack
	while(stackEmpty == false && equals != true){
		if(stackAux->first == NULL){
			stackEmpty = true;
		}
		if(&(stackAux->first->e.film) != NULL){
			equals = film_equals(&stackAux->first->e.film, &film);
		}
		if(equals == false){
			favoriteStack_pop(stackAux);
		}
	}
	
	// Free auxiliar stack
	free(stackAux);
 
    return equals;
}
