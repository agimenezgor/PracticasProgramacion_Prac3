#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "test_pr2.h"
#include "user.h"
#include "film.h"
#include "series.h"
#include "view.h"
#include "favorite.h"

// Run all tests for PR2
bool run_pr2(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section) && ok;
    ok = run_pr2_ex2(section) && ok;
    ok = run_pr2_ex3(section) && ok;

    return ok;
}

// Run tests for PR2 exercice 1
bool run_pr2_ex1(tTestSection* test_section) {
    bool passed = true, failed = false;

    tFavoriteStack favStack;
    tFavorite favorite[3];
    tFilm episodesChernobyl[5];
    tFilm episodesBlackMirror[3];
    tSeries series[2];
    bool stack_created = false;

    tError err;
    tUser userBob;

    //Create some data for testing, to be used later

    series_init(&series[0], "Chernobyl", DRAMA);

    film_init(&episodesChernobyl[0], "1:23:45", 60, &series[0]);
    film_init(&episodesChernobyl[1], "Please Remain Calm", 65, &series[0]);
    film_init(&episodesChernobyl[2], "Open Wide, O Earth", 65, &series[0]);
    film_init(&episodesChernobyl[3], "The Happiness of All Mankind", 67, &series[0]);
    film_init(&episodesChernobyl[4], "Vichnaya Pamyat", 72, &series[0]);


    series_init(&series[1], "Black Mirror - Season 1", SCIENCE_FICTION);

    film_init(&episodesBlackMirror[0], "The National Anthem", 44, &series[1]);
    film_init(&episodesBlackMirror[1], "Fifteen Million Merits", 62, &series[1]);
    film_init(&episodesBlackMirror[2], "The Entire History of You", 49, &series[1]);

    favorite_init(&favorite[0], episodesChernobyl[3]);
    favorite_init(&favorite[1], episodesBlackMirror[2]);
    favorite_init(&favorite[2], episodesBlackMirror[0]);

    // TEST 1: Creation of the stack
    failed = false;
    start_test(test_section, "PR2_EX1_1", "Creation of the stack");

    favoriteStack_create(&favStack);

    if (favStack.first != NULL) {
        failed = true;
    }
    else {
        stack_created = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_1", true);
    }


    // TEST 2.1: Check emptyness of stack - empty stack
    failed = false;
    start_test(test_section, "PR2_EX1_2.1", "Stack created; Check if empty");

    if (!stack_created || !favoriteStack_empty(favStack)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_2.1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_2.1", true);
    }

    // TEST 3.1: Push elements into the stack
    failed = false;
    start_test(test_section, "PR2_EX1_3.1", "Stack created; Push elem in it");

    err = favoriteStack_push(&favStack, favorite[0]);

    if (err != OK) {
        failed = true;
    }
    else if (favStack.first == NULL) {
        failed = true;
    }
    else {
        if (favStack.first->next != NULL) {
            failed = true;
        }

        if (!film_equals(&favStack.first->e.film, &favorite[0].film)) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_3.1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_3.1", true);
    }

    // TEST 2.2: Now check again emptyness of stack
    failed = false;
    start_test(test_section, "PR2_EX1_2.2", "Stack created; Check if not empty");

    if (!stack_created || favoriteStack_empty(favStack)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_2.2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_2.2", true);
    }

    // TEST 3.2: Push more elements into the stack
    failed = false;
    start_test(test_section, "PR2_EX1_3.2", "Stack created; Push 2 more elem");

    err = favoriteStack_push(&favStack, favorite[1]);

    if (err != OK) {
        failed = true;
    }

    err = favoriteStack_push(&favStack, favorite[2]);

    if (err != OK) {
        failed = true;
    }

    if (!stack_created) {
        failed = true;
    }
    else if (favStack.first == NULL) {
        failed = true;
    }
    else if (favStack.first->next == NULL) {
        failed = true;
    }
    else if (!film_equals(&favStack.first->e.film, &favorite[2].film)) {
        failed = true;
    }
    else if (favStack.first->next->next == NULL) {
        failed = true;
    }
    else if (!film_equals(&favStack.first->next->e.film, &favorite[1].film)) {
        failed = true;
    }
    else if (favStack.first->next->next->next != NULL) {
        failed = true;
    }
    else if (!film_equals(&favStack.first->next->next->e.film, &favorite[0].film)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_3.2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_3.2", true);
    }

    // TEST 4: Create stack in tUser datatype
    failed = false;
    start_test(test_section, "PR2_EX1_4", "Create stack in tUser datatype");

    stack_created = false;
    err = user_init(&userBob, "bob", "Bob", "bob@uoc.edu");

    if (err != OK) {
        failed = true;
    }
    else if (userBob.favorites.first != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_4", true);
        stack_created = true;
    }


    // TEST 5.1: Add favorites for the user
    failed = false;
    start_test(test_section, "PR2_EX1_5.1", "User fav stack; Add favorite");

    user_addFavorite(&userBob, episodesBlackMirror[0]);

    if (!stack_created) {
        failed = true;
    }
    else if (userBob.favorites.first == NULL) {
        failed = true;
    }
    else {
        if (userBob.favorites.first->next != NULL) {
            failed = true;
        }
        else if (!film_equals(&(userBob.favorites.first->e.film), &episodesBlackMirror[0])) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_5.1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_5.1", true);
    }

    // TEST 5.2: Add more favorites for the user
    failed = false;
    start_test(test_section, "PR2_EX1_5.2", "User fav stack; Add more favorites");

    user_addFavorite(&userBob, episodesBlackMirror[1]);

    if (!stack_created) {
        failed = true;
    }
    else if (userBob.favorites.first == NULL) {
        failed = true;
    }
    else {
        if (userBob.favorites.first->next == NULL) {
            failed = true;
        }
        else if (!film_equals(&(userBob.favorites.first->e.film), &episodesBlackMirror[1])) {
            failed = true;
        }
        else if (userBob.favorites.first->next->next != NULL) {
            failed = true;
        }
        else if (!film_equals(&(userBob.favorites.first->next->e.film), &episodesBlackMirror[0])) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_5.2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_5.2", true);
    }

    film_free(&episodesChernobyl[0]);
    film_free(&episodesChernobyl[1]);
    film_free(&episodesChernobyl[2]);
    film_free(&episodesChernobyl[3]);
    film_free(&episodesChernobyl[4]);

    series_free(&series[0]);


    film_free(&episodesBlackMirror[0]);
    film_free(&episodesBlackMirror[1]);
    film_free(&episodesBlackMirror[2]);

    series_free(&series[1]);

    favorite_free(&favorite[0]);
    favorite_free(&favorite[1]);
    favorite_free(&favorite[2]);

    // leaked stack - we will test release function in next EX
    // leaked user - we will test release function in next EX

    return passed;
}

// Run tests for PR1 exercice 2
bool run_pr2_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;

    tFavoriteStack favStack;
    tFavorite favorite[3];
    tFilm episodesChernobyl[5];
    tFilm episodesBlackMirror[3];
    tSeries series[2];
    bool stack_created = true;

    tError err;
    tUser userBob;

    tFavorite testFav;

    series_init(&series[0], "Chernobyl", DRAMA);

    film_init(&episodesChernobyl[0], "1:23:45", 60, &series[0]);
    film_init(&episodesChernobyl[1], "Please Remain Calm", 65, &series[0]);
    film_init(&episodesChernobyl[2], "Open Wide, O Earth", 65, &series[0]);
    film_init(&episodesChernobyl[3], "The Happiness of All Mankind", 67, &series[0]);
    film_init(&episodesChernobyl[4], "Vichnaya Pamyat", 72, &series[0]);


    series_init(&series[1], "Black Mirror - Season 1", SCIENCE_FICTION);

    film_init(&episodesBlackMirror[0], "The National Anthem", 44, &series[1]);
    film_init(&episodesBlackMirror[1], "Fifteen Million Merits", 62, &series[1]);
    film_init(&episodesBlackMirror[2], "The Entire History of You", 49, &series[1]);

    favorite_init(&favorite[0], episodesBlackMirror[1]);
    favorite_init(&favorite[1], episodesChernobyl[2]);
    favorite_init(&favorite[2], episodesChernobyl[4]);


    // TEST 1: Peek on empty stack
    failed = false;
    start_test(test_section, "PR2_EX2_1.1", "Peek on empty stack/top");

    // --- Prepare stack
    favoriteStack_create(&favStack);

    if (favStack.first == NULL) {
        stack_created = true;
    }

    if (!stack_created 
        || ERR_NOT_FOUND != favoriteStack_top(&testFav, favStack)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_1.1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_1.1", true);
    }

    // TEST 2: Peek on stack with elems
    failed = false;
    start_test(test_section, "PR2_EX2_1.2", "Peek on stack/top w/ elems");

    // add some elements, before peek/top
    err = favoriteStack_push(&favStack, favorite[2]);

    if (err != OK) {
        failed = true;
    }

    err = favoriteStack_push(&favStack, favorite[1]);

    if (err != OK) {
        failed = true;
    }

    err = favoriteStack_top(&testFav, favStack);

    if (err != OK) {
        failed = true;
    }
    else {
        if (!film_equals(&testFav.film, &(favorite[1].film))) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_1.2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_1.2", true);
    }

    // TEST 3: Pop elem
    failed = false;
    start_test(test_section, "PR2_EX2_2.1", "Pop elem");

    // Remove one element by poping them
    err = favoriteStack_pop(&favStack);

    if (err != OK) {
        failed = true;
    }
    else {
        // Now first stack elem shoud be favorite[2]

        if (favStack.first == NULL) {
            failed = true;
        }
        else if (!film_equals(&(favStack.first->e.film), &(favorite[2].film))) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_2.1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_2.1", true);
    }

    // TEST 4: Pop last elem
    failed = false;
    start_test(test_section, "PR2_EX2_2.2", "Pop last elem");

    // Remove one element by poping them
    err = favoriteStack_pop(&favStack);

    if (err != OK) {
        failed = true;
    }
    else {
        // Now first stack elem shoud be favorite[2]

        if (favStack.first != NULL) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_2.2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_2.2", true);
    }

    // TEST 5: Pop empty stack
    failed = false;
    start_test(test_section, "PR2_EX2_2.3", "Pop empty stack");

    // Remove one element by poping them
    err = favoriteStack_pop(&favStack);

    if (err != ERR_INVALID) {
        failed = true;
    }

    if (favStack.first != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_2.3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_2.3", true);
    }

    // TEST 6: Free stack
    failed = false;
    start_test(test_section, "PR2_EX2_3", "Release/free stack");

    // add some elements, before free
    err = favoriteStack_push(&favStack, favorite[2]);

    if (err != OK) {
        failed = true;
    }

    err = favoriteStack_push(&favStack, favorite[1]);

    if (err != OK) {
        failed = true;
    }

    favoriteStack_free(&favStack);

    if (favStack.first != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_3", true);
    }

    // TEST 7: Implementation of user_free(...)
    failed = false;
    start_test(test_section, "PR2_EX2_4", "Release favorite stack in user");

    err = user_init(&userBob, "bob", "Bob", "bob@uoc.edu");

    if (err != OK) {
        failed = true;
    }

    err = user_addFavorite(&userBob, episodesChernobyl[3]);

    if (err != OK) {
        failed = true;
    }

    err = user_addFavorite(&userBob, episodesChernobyl[2]);

    if (err != OK) {
        failed = true;
    }

    err = user_addFavorite(&userBob, episodesBlackMirror[1]);

    if (err != OK) {
        failed = true;
    }

    user_free(&userBob);

    if (userBob.favorites.first != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_4", true);
    }
    
    // TEST 8: Implementation of user_getFavoriteGenre(...): User with no favorites
    failed = false;
    start_test(test_section, "PR2_EX2_5.1", "Fav genre, user with no favs yet");

    err = user_init(&userBob, "bob", "Bob", "bob@uoc.edu");

    if (err != OK) {
        failed = true;
    }
    
    if (GENRE_NOT_FOUND != user_getFavoriteGenre(&userBob)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_5.1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_5.1", true);
    }
    
    user_free(&userBob);
    
    // TEST 9: Implementation of user_getFavoriteGenre(...): User prefers Chernobyl / DRAMA
    failed = false;
    start_test(test_section, "PR2_EX2_5.2", "Fav genre, user likes Chernobyl");

    err = user_init(&userBob, "bob", "Bob", "bob@uoc.edu");

    if (err != OK) {
        failed = true;
    }
    
    err = user_addFavorite(&userBob, episodesChernobyl[4]);

    if (err != OK) {
        failed = true;
    }
    
    err = user_addFavorite(&userBob, episodesBlackMirror[2]);

    if (err != OK) {
        failed = true;
    }
    
    err = user_addFavorite(&userBob, episodesChernobyl[2]);

    if (err != OK) {
        failed = true;
    }
    
    if (DRAMA != user_getFavoriteGenre(&userBob)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_5.2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_5.2", true);
    }
    
    
    
    // TEST 10: Implementation of user_getFavoriteGenre(...): User prefers Black Mirror / SCIFI
    failed = false;
    start_test(test_section, "PR2_EX2_5.3", "Fav genre, user likes Black Mirror");
    
    err = user_addFavorite(&userBob, episodesBlackMirror[0]);

    if (err != OK) {
        failed = true;
    }
    
    err = user_addFavorite(&userBob, episodesBlackMirror[1]);

    if (err != OK) {
        failed = true;
    }
    
    if (SCIENCE_FICTION != user_getFavoriteGenre(&userBob)) {
        failed = true;
    }
    
    if (failed) {
        end_test(test_section, "PR2_EX2_5.3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_5.3", true);
    }
    user_free(&userBob);
    
    film_free(&episodesChernobyl[0]);
    film_free(&episodesChernobyl[1]);
    film_free(&episodesChernobyl[2]);
    film_free(&episodesChernobyl[3]);
    film_free(&episodesChernobyl[4]);

    series_free(&series[0]);


    film_free(&episodesBlackMirror[0]);
    film_free(&episodesBlackMirror[1]);
    film_free(&episodesBlackMirror[2]);

    series_free(&series[1]);

    favorite_free(&favorite[0]);
    favorite_free(&favorite[1]);
    favorite_free(&favorite[2]);

    return passed;
}

// Run tests for PR1 exercice 3
bool run_pr2_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;

    tFavorite favorite[3];
    tFilm episodesChernobyl[5];
    tFilm episodesBlackMirror[3];
    tSeries series[3];

    tUser userBob;

    series_init(&series[0], "Chernobyl", DRAMA);

    film_init(&episodesChernobyl[0], "1:23:45", 60, &series[0]);
    film_init(&episodesChernobyl[1], "Please Remain Calm", 65, &series[0]);
    film_init(&episodesChernobyl[2], "Open Wide, O Earth", 65, &series[0]);
    film_init(&episodesChernobyl[3], "The Happiness of All Mankind", 67, &series[0]);
    film_init(&episodesChernobyl[4], "Vichnaya Pamyat", 72, &series[0]);


    series_init(&series[1], "Black Mirror - Season 1", SCIENCE_FICTION);

    film_init(&episodesBlackMirror[0], "The National Anthem", 44, &series[1]);
    film_init(&episodesBlackMirror[1], "Fifteen Million Merits", 62, &series[1]);
    film_init(&episodesBlackMirror[2], "The Entire History of You", 49, &series[1]);

    favorite_init(&favorite[0], episodesBlackMirror[1]);
    favorite_init(&favorite[1], episodesChernobyl[2]);
    favorite_init(&favorite[2], episodesChernobyl[4]);

    series_init(&series[2], "Breaking Bad", DRAMA);

    // TEST 1: Recursively get the total length of the movies referenced
    failed = false;
    start_test(test_section, "PR2_EX3_1", "Total length of user favs");

    user_init(&userBob, "bob", "Bob", "bob@uoc.edu");

    if (user_getFavsLengthInMin(&userBob) != 0) {
        failed = true;
    }
    else{

        user_addFavorite(&userBob, episodesChernobyl[3]);	    // Length is 67min
        user_addFavorite(&userBob, episodesChernobyl[2]);		// Length is 65min
        user_addFavorite(&userBob, episodesBlackMirror[1]);     // Length is 62min

        if (user_getFavsLengthInMin(&userBob) != 194) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_1", true);
    }


    // TEST 2: Recursively get number of favorite films of a serie
    failed = false;
    int numSeries = 0;
    start_test(test_section, "PR2_EX3_2", "Count of user favs in series");


    numSeries = user_getFavsCntPerSeries(&userBob, &series[2]);

    if (numSeries != 0) {
        failed = true;
    }
    else{
        numSeries = user_getFavsCntPerSeries(&userBob, &series[0]);
        if (numSeries != 2) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_2", true);
    }
    
    int i;

    for (i = 0; i < sizeof episodesChernobyl / sizeof episodesChernobyl[0]; i++) {
        film_free(&episodesChernobyl[i]);
    }

    for (i = 0; i < sizeof episodesBlackMirror / sizeof episodesBlackMirror[0]; i++) {
        film_free(&episodesBlackMirror[i]);
    }

    for (i = 0; i < sizeof series / sizeof series[0]; i++) {
        series_free(&series[i]);
    }

    for (i = 0; i < sizeof favorite / sizeof favorite[0]; i++) {
        favorite_free(&favorite[i]);
    }

    user_free(&userBob);

    return passed;
}
