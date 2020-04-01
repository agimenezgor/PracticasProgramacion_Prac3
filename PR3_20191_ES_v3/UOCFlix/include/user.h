#ifndef __USER__H__
#define __USER__H__

#include <stdbool.h>
#include "error.h"
#include "favorite.h"

// Data type to hold data related to a User in the platform
typedef struct {
    char* username;
    char* name;    
    char* mail;
    tFavoriteStack favorites;
} tUser;

// Table of tUser elements
typedef struct {
    unsigned int size;
    
    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS. 
    // That means that we are using the same amount of memory when the table is empty and 
    // when is full. We cannot add more elements than MAX_ELEMENTS.
    // tUser elements[MAX_ELEMENTS];
    
    // Using dynamic memory, the elements is a pointer to a region of memory. 
    // Initially, we have no memory (NULL), and we need to allocate memory 
    // when we want to add elements. We can add as many elements as we want, 
    // the only limit is the total amount of memory of our computer.
    tUser* elements;
    
} tUserTable;

// **** Functions related to management of tUser objects

// Initialize a user object
tError user_init(tUser* object, const char* username, const char* name, const char* mail);

// Release memory used by user object
void user_free(tUser* object);

// Compare two user objects
bool user_equals(tUser* user1, tUser* user2);

// Copy the data of a user to another user
tError user_cpy(tUser* dest, tUser* src);

// Remove the spaces at the beginning and end of the name (or name and surname), 
// capitalize individual words in string
tError user_trimCapitalizeName(tUser* object);

// Returns series with the most films in favorites for the user
// given as parameter. 
// Will return NULL if user has no favorites yet
tGenre user_getFavoriteGenre(tUser *object);

// Recursively get the total length of the movies referenced 
// in stack1's favorites 
unsigned user_getFavsLengthInMin(tUser *object);

// Recursively get the number of favorite films of a serie 
// in stacks favorites
unsigned user_getFavsCntPerSeries(tUser *user, tSeries * serie);

// Adds a favorite in stack of favorites of the user
tError user_addFavorite(tUser *object, tFilm film);

// **** Functions related to management of tUserTable objects

// Initialize the Table of users
void userTable_init(tUserTable* table);

// Release the memory used by userTable structure
void userTable_free(tUserTable* table);

// Get the size of the table
unsigned int userTable_size(tUserTable* table);

// Add a new user to the table
tError userTable_add(tUserTable* table, tUser* user);

// Compare two Table of users
bool userTable_equals(tUserTable* userTable1, tUserTable* userTable2);

// Get user by username
tUser* userTable_find(tUserTable* table, const char* username);

// Remove a user from the table
tError userTable_remove(tUserTable* table, tUser* user);

#endif // __USER__H__