#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include "popularity.h"
#include "view.h"
#include "film.h"
#include "user.h"

// Number of views of a certain film on a viewLog
unsigned int popularity_getCntView(tViewLog *viewLog, tFilm *film) {
    // PR3_EX1

	// Check preconditions
	assert(viewLog != NULL);
	
	
	int i, amount = 0; 
	
	// Boolean for found equal films
	bool founded = false;
	
	// Find equal films and count the total amount
	for(i = 0; i < viewLog->size; i++){
		founded = (film_equals(viewLog->elements[i].film, film));
		if(founded == true){
			amount++;
		}
	}
	
    return amount;
}

// Number of users with that film in their favs' stack - assumes each user is 
// only once in table
unsigned int popularity_getCntUsrFavd(tUserTable *userTable, tFilm *film) {
    // PR3_EX1
	
    // Check preconditions
	assert(userTable != NULL);
	assert(film != NULL);
	
	int amount = 0;
	int aux = 0;
	
	// Declare and start a auxiliar stack
	tFavoriteStack *stackAux;
	stackAux = (tFavoriteStack *)malloc(sizeof(tFavoriteStack));
	favoriteStack_create(stackAux);
	
	// booleans for find if the stack are empty and if the films are equals
	bool stackEmpty = false;
	bool equals = false;
	
	
	while(aux != userTable->size){
		favoriteStack_duplicate(stackAux, userTable->elements[aux].favorites);
		
		stackEmpty = false;
		
		if(stackAux->first == NULL){
			stackEmpty = true;
		}
		
		// Find in the favorite stack 
		while(stackEmpty == false){
			if(&(stackAux->first->e.film) != NULL){
				equals = film_equals(&stackAux->first->e.film, film);
			}
			if(equals == true){
				amount++;
			}
			favoriteStack_pop(stackAux);
			if(stackAux->first == NULL){
				stackEmpty = true;
			}
		}
		aux++;
	}
	
	// Free auxiliar stack
	free(stackAux);
	
    return amount;
}

// Get stats of a film, based on viewLog and favorite contents of 
// users in userTable.
tFilmStats popularity_getFilmStats(tViewLog *viewLog, tUserTable *userTable, tFilm *film) {
    // PR3_EX1
    tFilmStats fs = { 0, 0 };
    
	// Check preconditions
	assert(viewLog != NULL);
	assert(userTable != NULL);
	assert(film != NULL);
	
	// Amount of visualizations of the film
	int i, amount = 0;
	bool equals = false;
	
	// Count the amount of films are equals
	for(i = 0; i < viewLog->size; i++){
		equals = film_equals(viewLog->elements[i].film, film);
		if(equals == true){
			amount++;
		}
	}
	// Amount of visualizations of the film
	fs.numUserViews = amount;
	
	
	// Number of users that have the film in favorites 
	fs.numUserFavorited = popularity_getCntUsrFavd(userTable, film);
	
    return fs;
}

// Creates a popularity element out of a film and a stats
tError popularity_init(tPopularity* object, tFilmStats fs, tFilm film) {
    // PR3_EX1
         
    // Check preconditions
	assert(object != NULL);
	
	// Copy the stadistics
	object->stats = fs;
	
	// Init the film
	film_init(&(object->film), film.title, film.lengthInMin, film.series);

        
    return OK;
}

// Releases data pointed by popularity element
void popularity_free(tPopularity* object) {
    // PR3_EX1 
	
	// Check preconditions
	assert(object != NULL);
	
	// Free film
	film_free(&object->film);
}

// Compare stats of two films, 1 if s1 wins, -1 if s2 wins, 0 if tie
int popularity_compare(tFilmStats s1, tFilmStats s2) {
    // PR3_EX1
	
	// variable
	int win;
	
	// Compare
	// Case 1: win the film with more favorite number 
	if(s1.numUserFavorited > s2.numUserFavorited){
		// Win film 1
		win = 1;
	}
	else if(s1.numUserFavorited < s2.numUserFavorited){ 
		// Win film 2
		win = -1;
	}
	// Case 2: if there is a tie, win the film with more visualizations
	else{
		if(s1.numUserViews > s2.numUserViews){ 
			// Win film 1
			win = 1;
		}
		else if(s1.numUserViews < s2.numUserViews){ 
			// Win film 2
			win = -1;
		}
		// Case 3: if there is a tie, return 0;
		else{ 
			win = 0;
		}
	}
	
    return win;
}

// Create the popularity list
void popularityList_create(tPopularityList* list) {
    // PR3_EX2
	
	// Check preconditions
	assert(list != NULL);
	
	// Initialize size
	list->size = 0;
	
	// Initialize first node
	list->first = NULL;
	
	// Initialize last node
	list->last = NULL;
}

// Insert/adds a new popularity to the popularity list

// Note no popularity_duplicate(..) method is provided
// popularity elem, and their pointers, maybe copied with '='
// referencing existing tFilm and tFilmStats passed by param
// node must be though allocated

tError popularityList_insert(tPopularityList* list, tPopularity popularity, int index) {
    // PR3_EX2
    
	// Check preconditions
	assert(list != NULL);
	
	// Allocate memory
    if (list->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        list->size = 1;
        list->first = (tPopularityListNode*)malloc(list->size * sizeof(tPopularityListNode));
		list->last = (tPopularityListNode*)malloc(list->size * sizeof(tPopularityListNode));
    }
    else {
        // Table with elements

        // Increase the number of elements of the table
        list->size = list->size + 1;
		list->first = (tPopularityListNode*)realloc(list->first, list->size * sizeof(tPopularityListNode));
		list->last = (tPopularityListNode*)realloc(list->last, list->size * sizeof(tPopularityListNode));
    }

    // Check that the memory has been allocated
    if (list->first == NULL || list->last == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }
	
	// Save in temporal node
	tPopularityListNode *temp;
	tPopularityListNode *prev;
	
	temp = (tPopularityListNode*) malloc(sizeof(tPopularityListNode));
	
	if(temp == NULL){
		return ERR_MEMORY_ERROR;
	}
	else{
		temp->e = popularity;
		if(index == 1){
			temp->next = list->first;
			list->first = temp;
		}
		else{
			prev = popularityList_get(list, index - 1);
			if(prev != NULL){
				temp->next = prev->next;
				prev->next = temp;
			}
			else{
				return ERR_INVALID_INDEX;
			}
		}
	}
	
    return OK;
}

// Deletes a popularity from the popularity list
tError popularityList_delete(tPopularityList* list, int index) {
    // PR3_EX2
	
	// Check preconditions
	assert(list != NULL);
	
	// Declare auxiliar nodes
	tPopularityListNode *temp;
	tPopularityListNode *prev;
	
	
	if(index == 1){
		temp = list->first;
		if(popularityList_empty(list)){
			return ERR_EMPTY_LIST;
		}
		else{
			list->first = temp->next;
			free(temp);
		}
	}
	else{
		prev = popularityList_get(list, index - 1);
		
		if(prev != NULL){
			temp = prev->next;
			if(temp == NULL){
				return ERR_INVALID_INDEX;
			}
			else{
				prev->next = temp->next;
				free(temp);
			}
		}
		else{
			return ERR_INVALID_INDEX;
		}
	}
	
    return OK;
}

// Gets popularity from given position, NULL if out of bounds
tPopularityListNode* popularityList_get(tPopularityList* list, int index) {
    // PR3_EX2
	
	// Check preconditions
	assert(list != NULL);
	
	// Declare a temporal node
	tPopularityListNode *prev;
	
	// We assign at the auxiliar node the first node of the list
	prev = list->first;
	
	// Find the position
	int i = 1;
	while(i < index && prev != NULL){
		prev = prev->next;
		i++;
	}
	
	// If the position are incorrect, return null
	if(index <= 0 || index > (list->size + 1)){
		return NULL;
	}
	
    return prev;
}

// Gets true if list is empty
bool popularityList_empty(tPopularityList* list) {
    // PR3_EX2
	
	// Check preconditions
	assert(list != NULL);
	
	// Check if the list are empty
	if(list->first == NULL){
		return true;
	}
	
    return false;
}

// Remove all data for a popularity list
void popularityList_free(tPopularityList* list) {
    // PR3_EX2
	
	// Check preconditions
	assert(list != NULL);
	
	// Declare an auxiliar node
	tPopularityListNode *auxNode;
	
	// Free the list 
	while(!popularityList_empty(list)){
		auxNode = list->first;
	
		list->first = list->first->next;
		
		free(auxNode);
		
		list->size = list->size - 1;
		if(list->size == 0){
			list->first = NULL;
		}
	}
}

// given a list of films' popularity, returns the position of the film in the list
int popularityList_getPosByFilm(tPopularityList* list, tFilm *film) {
    // PR3_EX3
	
	// Check preconditions
	assert(list != NULL);
	assert(film != NULL);
	
	// variable position
	int position = 1;
	
	// Declare an auxiliar node
	tPopularityListNode *auxNode;
	
	//variable film founded
	bool founded = false;
	
	if(popularityList_empty(list)){
		return -1;
	}
	else{
		while(position < list->size && !founded){
			auxNode = popularityList_get(list, position);
			founded = film_equals(&auxNode->e.film, film);
			position++;
		}
		if(founded){
			return position - 1;
		}
	}
	
	
	
    return -1;
}

// Swap two elements in the list
tError popularityList_swap(tPopularityList* list, int index_dst, int index_src) {
    // PR3_EX3
	
	// Check preconditions
	assert(list != NULL);
	
	// Declare an auxiliar popularity
	tPopularity aux;
	
	// Declare a auxiliary nodes
	tPopularityListNode *dstNode;
	tPopularityListNode *srcNode;
	
	// Check index preconditions
	if(index_dst > list->size || index_src > list->size || index_dst < 1 || index_src < 1 || index_dst == index_src){
		return ERR_INVALID_INDEX;
	}
	
	// Get positions
	dstNode = popularityList_get(list, index_dst);
	srcNode = popularityList_get(list, index_src);
	
	// Swap
	aux = srcNode->e;
	srcNode->e = dstNode->e;
	dstNode->e = aux;
	
    return OK;
}

// Sorts input list using bubbleSort algorithm
tError popularityList_bubbleSort(tPopularityList *list) {
    // PR3_EX3
	
	// Check preconditions
	assert(list != NULL);
	
	// Declare auxiliary nodes
	tPopularityListNode *prev;
	tPopularityListNode *next;
	
	
	// Variable of the winning state
	int win;
	
	// Variable of the index
	int index = 1;
	
	// Bubblesort function
	for(int i = 0; i < list->size + 1; i++){
		prev = list->first;
		next = prev->next;
		for(int j = i; j < list->size - 1; j++){
			win = popularity_compare(prev->e.stats, next->e.stats);
			if(win == -1){
				popularityList_swap(list, index, index + 1);
			}
			prev = prev->next;
			next = next->next;
			index++;
		}
		index = 1;
	}
	
	
    return OK;
}

// Helper function, print list contents
void popularityList_print(tPopularityList list) {
    tPopularityListNode *pLNode;
	
	printf("===== List Contents:\n\n");

    for (int i = 0; i < list.size; ++i) {
        pLNode = popularityList_get(&list, i + 1);
        printf("\tElemPos: %d:\tnumUserFavorited: %d;\tnumUserViews: %d;\tfilm_title: \"%s\"\n",
            i + 1,
            pLNode->e.stats.numUserFavorited,
            pLNode->e.stats.numUserViews,
            pLNode->e.film.title);
    }

    printf("\n===== End Of List: %d elems\n", list.size);
}
