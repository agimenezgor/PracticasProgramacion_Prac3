#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "test_pr3.h"
#include "user.h"
#include "film.h"
#include "series.h"
#include "view.h"
#include "favorite.h"
#include "popularity.h"

// Run all tests for PR3
bool run_pr3(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");

    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);

    ok = run_pr3_ex1(section) && ok;
    ok = run_pr3_ex2(section) && ok;
    ok = run_pr3_ex3(section) && ok;

    return ok;
}

// Run tests for PR3 exercice 1
bool run_pr3_ex1(tTestSection* test_section) {
    bool passed = true, failed = false;

    tUser user, *userBobPtr, *userAlicePtr, *userSamPtr, *userSallyPtr;
    tUserTable userTable;
    tFilm film[7];
    tSeries series;
    tViewLog viewLog;
    tView view;
    tDateTime *dt;
    tFilmStats fs, fs1, fs2;
    tPopularity pop;

    // Create & fill table of users
    userTable_init(&userTable);

    user_init(&user, "bob", "Bob", "bob@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    user_init(&user, "alice", "Alice", "alice@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    user_init(&user, "sam", "Sam", "sam@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    user_init(&user, "sally", "Sally", "sally@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    // We store their positions/order they've been added in the array
    // for easy access later (viewLog, favorites)
    userBobPtr = &(userTable.elements[0]);
    userAlicePtr = &(userTable.elements[1]);
    userSamPtr = &(userTable.elements[2]);
    userSallyPtr = &(userTable.elements[3]);

    series_init(&series, "Series Name", COMEDY);

    film_init(&film[0], "Film0", 100, &series);
    film_init(&film[1], "Film1", 101, &series);
    film_init(&film[2], "Film2", 102, &series);
    film_init(&film[3], "Film3", 103, &series);
    film_init(&film[4], "Film4", 104, &series);
    film_init(&film[5], "Film5", 105, &series);
    film_init(&film[6], "Film6", 106, &series);

    // Create and fill viewLog 

    // Bob: 0, 1, 2
    // Alice: 1, 2, 3, 4
    // Sam: 4
    // Sally: 1, 6

    viewLog_init(&viewLog);

    // Bob   
    dt = setDateTime(1, 10, 2019, 23, 00);
    view_init(&view, dt, 3, userBobPtr, &film[0]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    dt = setDateTime(30, 9, 2019, 22, 13);
    view_init(&view, dt, 1, userBobPtr, &film[1]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    dt = setDateTime(30, 9, 2019, 23, 05);
    view_init(&view, dt, 4, userBobPtr, &film[2]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    // Alice    
    dt = setDateTime(30, 7, 2019, 22, 13);
    view_init(&view, dt, 5, userAlicePtr, &film[1]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    dt = setDateTime(30, 6, 2019, 23, 05);
    view_init(&view, dt, 9, userAlicePtr, &film[2]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    dt = setDateTime(30, 6, 2019, 23, 05);
    view_init(&view, dt, 2, userAlicePtr, &film[3]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    dt = setDateTime(10, 10, 2019, 23, 00);
    view_init(&view, dt, 6, userAlicePtr, &film[4]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    // Sam    
    dt = setDateTime(10, 10, 2019, 23, 00);
    view_init(&view, dt, 6, userAlicePtr, &film[4]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    // Sally    
    dt = setDateTime(7, 10, 2019, 23, 00);
    view_init(&view, dt, 5, userSallyPtr, &film[1]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    dt = setDateTime(8, 10, 2019, 23, 00);
    view_init(&view, dt, 3, userSallyPtr, &film[6]);
    free(dt);

    viewLog_add(&viewLog, &view);
    view_free(&view);

    // Create and fill list of favorites in each user    

    // Bob: 2, 3
    // Alice: 1, 2, 4
    // Sam: 2, 4
    // Sally: none

    user_addFavorite(userBobPtr, film[2]);
    user_addFavorite(userBobPtr, film[3]);
    user_addFavorite(userAlicePtr, film[1]);
    user_addFavorite(userAlicePtr, film[2]);
    user_addFavorite(userAlicePtr, film[4]);
    user_addFavorite(userSamPtr, film[2]);
    user_addFavorite(userSamPtr, film[4]);

    // TEST 1: View count in viewLog == 0
    failed = false;
    start_test(test_section, "PR3_EX1_1A_1", "View count in viewLog == 0");

    // views are

    // Bob: 0, 1, 2
    // Alice: 1, 2, 3, 4
    // Sam: 4
    // Sally: 1, 6

    if (popularity_getCntView(&viewLog, &film[5]) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_1A_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1A_1", true);
    }

    // TEST 2: View count in viewLog > 0
    failed = false;
    start_test(test_section, "PR3_EX1_1A_2", "View count in viewLog > 0");

    // views are

    // Bob: 0, 1, 2
    // Alice: 1, 2, 3, 4
    // Sam: 4
    // Sally: 1, 6

    if (popularity_getCntView(&viewLog, &film[0]) != 1) {
        failed = true;
    }

    if (popularity_getCntView(&viewLog, &film[3]) != 1) {
        failed = true;
    }

    if (popularity_getCntView(&viewLog, &film[6]) != 1) {
        failed = true;
    }

    if (popularity_getCntView(&viewLog, &film[2]) != 2) {
        failed = true;
    }

    if (popularity_getCntView(&viewLog, &film[4]) != 2) {
        failed = true;
    }

    if (popularity_getCntView(&viewLog, &film[1]) != 3) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_1A_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1A_2", true);
    }

    // TEST 3: favorite_filmExists, existing film in favorites
    failed = false;
    start_test(test_section, "PR3_EX1_1B_1", "Film in user favs, existing");

    // favorites are:

    // Bob: 2, 3
    // Alice: 1, 2, 4
    // Sam: 2, 4
    // Sally: none

    // Check for existing films

    if (!favorite_filmExists(&(userBobPtr->favorites), film[3])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userAlicePtr->favorites), film[1])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userAlicePtr->favorites), film[2])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userAlicePtr->favorites), film[4])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userSamPtr->favorites), film[2])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userSamPtr->favorites), film[4])) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_1B_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1B_1", true);
    }

    // TEST 3: favorite_filmExists, non-existing film in favorites
    failed = false;
    start_test(test_section, "PR3_EX1_1B_2", "Film in user favs, non-existing");

    // Check first if some film exist (did we implement something?)
    if (favorite_filmExists(&(userSallyPtr->favorites), film[6])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userBobPtr->favorites), film[2])) {
        failed = true;
    }

    // Check for non-existing films
    if (favorite_filmExists(&(userBobPtr->favorites), film[0])) {
        failed = true;
    }

    if (favorite_filmExists(&(userBobPtr->favorites), film[1])) {
        failed = true;
    }

    if (favorite_filmExists(&(userAlicePtr->favorites), film[3])) {
        failed = true;
    }

    if (favorite_filmExists(&(userAlicePtr->favorites), film[6])) {
        failed = true;
    }

    if (favorite_filmExists(&(userSamPtr->favorites), film[1])) {
        failed = true;
    }

    if (favorite_filmExists(&(userSallyPtr->favorites), film[0])) {
        failed = true;
    }

    if (favorite_filmExists(&(userSallyPtr->favorites), film[1])) {
        failed = true;
    }

    if (favorite_filmExists(&(userSallyPtr->favorites), film[6])) {
        failed = true;
    }

    if (!favorite_filmExists(&(userBobPtr->favorites), film[2])) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_1B_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1B_2", true);
    }

    // TEST 5: Count in userFavorites == 0
    failed = false;
    start_test(test_section, "PR3_EX1_1C_1", "Count in userFavorites == 0");

    // favorites are:

    // Bob: 2, 3
    // Alice: 1, 2, 4
    // Sam: 2, 4
    // Sally: none

    if (popularity_getCntUsrFavd(&userTable, &film[0]) != 0) {
        failed = true;
    }

    if (popularity_getCntUsrFavd(&userTable, &film[5]) != 0) {
        failed = true;
    }

    if (popularity_getCntUsrFavd(&userTable, &film[6]) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_1C_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1C_1", true);
    }

    // TEST 6: Count in userFavorites > 0
    failed = false;
    start_test(test_section, "PR3_EX1_1C_2", "Count in userFavorites > 0");

    // favorites are:

    // Bob: 2, 3
    // Alice: 1, 2, 4
    // Sam: 2, 4
    // Sally: none

    if (popularity_getCntUsrFavd(&userTable, &film[3]) != 1) {
        failed = true;
    }

    if (popularity_getCntUsrFavd(&userTable, &film[1]) != 1) {
        failed = true;
    }

    if (popularity_getCntUsrFavd(&userTable, &film[4]) != 2) {
        failed = true;
    }

    if (popularity_getCntUsrFavd(&userTable, &film[2]) != 3) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_1C_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1C_2", true);
    }

    // TEST 7: Get statistics for a film
    failed = false;
    start_test(test_section, "PR3_EX1_2A", "Get statistics for films 0 to 6");

    // views are

    // Bob: 0, 1, 2
    // Alice: 1, 2, 3, 4
    // Sam: 4
    // Sally: 1, 6

    // favorites are:

    // Bob: 2, 3
    // Alice: 1, 2, 4
    // Sam: 2, 4
    // Sally: none

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[0]);
    if (fs.numUserViews != 1 || fs.numUserFavorited != 0) {
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[1]);
    if (fs.numUserViews != 3 || fs.numUserFavorited != 1) {
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[2]);
    if (fs.numUserViews != 2 || fs.numUserFavorited != 3) {
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[3]);
    if (fs.numUserViews != 1 || fs.numUserFavorited != 1) {
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[4]);
    if (fs.numUserViews != 2 || fs.numUserFavorited != 2) {
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[5]);
    if (fs.numUserViews != 0 || fs.numUserFavorited != 0) {
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &film[6]);
    if (fs.numUserViews != 1 || fs.numUserFavorited != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_2A", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_2A", true);
    }

    // TEST 8: Create popularity element
    failed = false;
    start_test(test_section, "PR3_EX1_2B", "Create popularity element");

    fs.numUserFavorited = 123;
    fs.numUserViews = 321;

    if (OK != popularity_init(&pop, fs, film[6])) {
        failed = true;
    }

    if (!failed)
    {
        if (0 != strcmp(pop.film.title, "Film6")) {
            failed = true;
        }

        if (pop.film.lengthInMin != 106) {
            failed = true;
        }

        if (pop.film.series != &series) {
            failed = true;
        }

        if (pop.stats.numUserViews != 321 || pop.stats.numUserFavorited != 123) {
            failed = true;
        }
    }

    popularity_free(&pop);

    if (failed) {
        end_test(test_section, "PR3_EX1_2B", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_2B", true);
    }

    // TEST 9: Compare popularity
    failed = false;
    start_test(test_section, "PR3_EX1_2C", "Compare statistics");

    fs1 = popularity_getFilmStats(&viewLog, &userTable, &film[0]);  // numUserViews == 1 - numUserFavorited == 0
    fs2 = popularity_getFilmStats(&viewLog, &userTable, &film[6]);  // numUserViews == 1 - numUserFavorited == 0
    if (0 != popularity_compare(fs1, fs2)) {
        failed = true;
    }

    fs1 = popularity_getFilmStats(&viewLog, &userTable, &film[1]);  // numUserViews == 3 - numUserFavorited == 1
    fs2 = popularity_getFilmStats(&viewLog, &userTable, &film[2]);  // numUserViews == 2 - numUserFavorited == 3
    if (-1 != popularity_compare(fs1, fs2)) {
        failed = true;
    }

    fs1 = popularity_getFilmStats(&viewLog, &userTable, &film[2]);  // numUserViews == 2 - numUserFavorited == 3
    fs2 = popularity_getFilmStats(&viewLog, &userTable, &film[4]);  // numUserViews == 2 - numUserFavorited == 2
    if (1 != popularity_compare(fs1, fs2)) {
        failed = true;
    }

    fs1 = popularity_getFilmStats(&viewLog, &userTable, &film[5]);  // numUserViews == 0 - numUserFavorited == 0
    fs2 = popularity_getFilmStats(&viewLog, &userTable, &film[6]);  // numUserViews == 1 - numUserFavorited == 0
    if (-1 != popularity_compare(fs1, fs2)) {
        failed = true;
    }

    fs1 = popularity_getFilmStats(&viewLog, &userTable, &film[1]);  // numUserViews == 3 - numUserFavorited == 1
    fs2 = popularity_getFilmStats(&viewLog, &userTable, &film[3]);  // numUserViews == 1 - numUserFavorited == 1
    if (1 != popularity_compare(fs1, fs2)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX1_2C", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_2C", true);
    }

    // Free everything

    viewLog_free(&viewLog);

    film_free(&film[0]);
    film_free(&film[1]);
    film_free(&film[2]);
    film_free(&film[3]);
    film_free(&film[4]);
    film_free(&film[5]);
    film_free(&film[6]);

    series_free(&series);

    userTable_free(&userTable);

    return passed;
}


#define BREAKING_BAD 7
#define STRANGER_THINGS 8
#define NUMBER_FILMS 4

// Run tests for PR3 exercice 2
bool run_pr3_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;

    tPopularityList popularityList;
    tPopularity populars[NUMBER_FILMS];
    tPopularityListNode* tmp;

    tError err;
    tUser user, *userBobPtr, *userAlicePtr;
    tUserTable userTable;
    tSeries serieBreakingBad, serieStrangerThings;
    tFilmTable filmTable;
    tFilm filmBreakingBad[BREAKING_BAD];
    tFilm filmStrangerThings[STRANGER_THINGS];
    tFilmStats fs;
    tViewLog viewLog;
    tView view;
    tDateTime *dt;
    int i;

    // Create & fill table of users
    userTable_init(&userTable);

    user_init(&user, "bob", "Bob", "bob@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    user_init(&user, "alice", "Alice", "alice@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    user_init(&user, "sam", "Sam", "sam@uoc.edu");
    userTable_add(&userTable, &user);
    user_free(&user);

    // We store their positions/order they've been added in the array
    // for easy access later (viewLog, favorites)
    userBobPtr = &(userTable.elements[0]);
    userAlicePtr = &(userTable.elements[1]);

    series_init(&serieBreakingBad, "Breaking Bad", DRAMA);

    filmTable_init(&filmTable);

    film_init(&filmBreakingBad[0], "Pilot", 58, &serieBreakingBad);
    film_init(&filmBreakingBad[1], "Cat's in the Bag...", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[2], "...And the Bag's in the River", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[3], "Cancer Man", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[4], "Gray Matter", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[5], "Crazy Handful of Nothin'", 47, &serieBreakingBad);
    film_init(&filmBreakingBad[6], "A No-Rough-Stuff-Type Deal", 47, &serieBreakingBad);

    for (i = 0; i < BREAKING_BAD; i++) {
        filmTable_add(&filmTable, &filmBreakingBad[i]);
    }

    series_init(&serieStrangerThings, "Stranger Things", SCIENCE_FICTION);

    film_init(&filmStrangerThings[0], "Chapter One: The Vanishing of Will Byers", 47, &serieStrangerThings);
    film_init(&filmStrangerThings[1], "Chapter Two: The Weirdo on Maple Street", 55, &serieStrangerThings);
    film_init(&filmStrangerThings[2], "Chapter Three: Holly, Jolly", 51, &serieStrangerThings);
    film_init(&filmStrangerThings[3], "Chapter Four: The Body", 49, &serieStrangerThings);
    film_init(&filmStrangerThings[4], "Chapter Five: The Flea and the Acrobat", 52, &serieStrangerThings);
    film_init(&filmStrangerThings[5], "Chapter Six: The Monster", 46, &serieStrangerThings);
    film_init(&filmStrangerThings[6], "Chapter Seven: The Bathtub", 41, &serieStrangerThings);
    film_init(&filmStrangerThings[7], "Chapter Eight: The Upside Down", 54, &serieStrangerThings);

    for (i = 0; i < STRANGER_THINGS; i++){
        filmTable_add(&filmTable, &filmStrangerThings[i]);
    }

    viewLog_init(&viewLog);

    dt = setDateTime(30, 9, 2019, 22, 24);
    view_init(&view, dt, 5, userAlicePtr, &filmStrangerThings[0]);
    free(dt);

    dt = setDateTime(2, 10, 2019, 21, 50);
    view_init(&view, dt, 5, userAlicePtr, &filmStrangerThings[1]);
    free(dt);

    viewLog_add(&viewLog, &view);

    dt = setDateTime(1, 10, 2019, 23, 00);
    view_init(&view, dt, 3, userBobPtr, &filmBreakingBad[0]);
    free(dt);

    viewLog_add(&viewLog, &view);

    dt = setDateTime(30, 9, 2019, 22, 13);
    view_init(&view, dt, 5, userBobPtr, &filmBreakingBad[1]);
    free(dt);

    viewLog_add(&viewLog, &view);


    dt = setDateTime(30, 9, 2019, 23, 05);
    view_init(&view, dt, 4, userBobPtr, &filmBreakingBad[1]);
    free(dt);

    viewLog_add(&viewLog, &view);

    dt = setDateTime(1, 10, 2019, 22, 24);
    view_init(&view, dt, 4, userBobPtr, &filmStrangerThings[0]);
    free(dt);

    // TEST 1: Create list of tPopularity elems
    start_test(test_section, "PR3_EX2_1", "Create list of tPopularity elems");
    failed = false;

    popularityList.first = popularityList.last = (tPopularityListNode *)0xABAD1DEA;
    popularityList.size = UINT_MAX;

    popularityList_create(&popularityList);

    if (popularityList.first != NULL){
        failed = true;
    }

    if (popularityList.last != NULL){
        failed = true;
    }

    if (popularityList.size != 0){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_1", true);
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &filmStrangerThings[0]);
    err = popularity_init(&populars[0], fs, filmStrangerThings[0]);
    if (err != OK){
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &filmStrangerThings[1]);
    err = popularity_init(&populars[1], fs, filmStrangerThings[1]);
    if (err != OK){
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &filmBreakingBad[0]);
    err = popularity_init(&populars[2], fs, filmBreakingBad[0]);
    if (err != OK){
        failed = true;
    }

    fs = popularity_getFilmStats(&viewLog, &userTable, &filmBreakingBad[1]);
    err = popularity_init(&populars[3], fs, filmBreakingBad[1]);
    if (err != OK){
        failed = true;
    }

    // TEST 2: Insert tPopularity elem in list
    start_test(test_section, "PR3_EX2_2", "Insert tPopularity elem in list");
    failed = false;

    for (i = 0; i<NUMBER_FILMS; i++){
        err = popularityList_insert(&popularityList, populars[i], i + 1);
        if (err != OK){
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_2", true);
    }


    // TEST 3: Insert tPopularity elem, wrong idx
    start_test(test_section, "PR3_EX2_3", "Insert tPopularity elem, wrong idx");
    failed = false;

    err = popularityList_insert(&popularityList, populars[0], 7);
    if (err != ERR_INVALID_INDEX) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_3", true);
    }

    // TEST 4: Delete tPopularity elem from list
    start_test(test_section, "PR3_EX2_4", "Delete tPopularity elem from list");
    failed = false;

    err = popularityList_delete(&popularityList, 3);
    if (err != OK){
        failed = true;
    }

    err = popularityList_delete(&popularityList, 1);
    if (err != OK){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_4", true);
    }

    // TEST 5: Get tPopularity elem
    start_test(test_section, "PR3_EX2_5", "Get tPopularity elem from list");
    failed = false;

    tmp = popularityList_get(&popularityList, 1);
    if ((tmp == NULL) || !film_equals(&(tmp->e.film), &filmStrangerThings[1])) {
        failed = true;
    }

    tmp = popularityList_get(&popularityList, 2);
    if ((tmp == NULL) || !film_equals(&(tmp->e.film), &filmBreakingBad[1])) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_5", true);
    }

    // TEST 7: Get wrong index from list 
    start_test(test_section, "PR3_EX2_6", "Get wrong index from list");
    failed = false;

    // Get existing index
    tmp = popularityList_get(&popularityList, 2);
    if ((tmp == NULL) || !film_equals(&(tmp->e.film), &filmBreakingBad[1])) {
        failed = true;
    }

    // Now get non-existing index
    tmp = popularityList_get(&popularityList, 5);
    if (tmp != NULL){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_6", true);
    }

    // TEST 8: Check if list is empty
    start_test(test_section, "PR3_EX2_7", "Check if list is empty");
    failed = false;

    if (popularityList_empty(&popularityList)){
        failed = true;
    }

    popularityList_free(&popularityList);
    if (!popularityList_empty(&popularityList)){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX2_7", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_7", true);
    }


    // Remove used memory
    userTable_free(&userTable);

    for (i = 0; i < BREAKING_BAD; i++) {
        film_free(&filmBreakingBad[i]);
    }

    for (i = 0; i < STRANGER_THINGS; i++) {
        film_free(&filmStrangerThings[i]);
    }

    filmTable_free(&filmTable);

    series_free(&serieBreakingBad);
    series_free(&serieStrangerThings);

    view_free(&view);
    viewLog_free(&viewLog);

    for (i = 0; i < NUMBER_FILMS; i++) {
        popularity_free(&populars[i]);
    }


    return passed;
}

#define LIST_SIZE_FOR_EX3   10

// Run tests for PR3 exercice 3
bool run_pr3_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;

    // Create test environment
    tFilm film, fooFilm;
    tFilmStats fs;
    tPopularity pop[LIST_SIZE_FOR_EX3];
    tPopularityList popList, emptyList;
    char someTitle[30];
    tSeries series;
    tError err;
    tPopularity e_src, e_dst;
    tPopularityListNode *pNode_src, *pNode_dst;
    int position, randomPosition;
    bool list_created = false;

    // Test env - list creation
    popList.first = emptyList.first = (tPopularityListNode *) 0x0001;
    popList.last = emptyList.last = (tPopularityListNode *) 0x0001;
    popularityList_create(&popList);
    popularityList_create(&emptyList);
    
    if (popList.first == NULL && popList.last == NULL && popList.size == 0
        && emptyList.first == NULL && emptyList.last == NULL && emptyList.size == 0) {
        list_created = true;
    }

    series_init(&series, "default_serie", COMEDY);

    srand(42);

    film_init(&fooFilm, "Foo Film", 100, &series);

    if (list_created) {
        for (int i = 0; i < sizeof(pop) / sizeof(tPopularity); ++i) {
            sprintf(someTitle, "Title for film %d", i + 1);
            film_init(&film, someTitle, 100, &series);

            fs.numUserFavorited = rand() % 50;
            fs.numUserViews = rand() % 500;

            err = popularity_init(&(pop[i]), fs, film);
                        
            if (err != OK) {                
                list_created = false;
                break;
            }

            film_free(&film);

            err = popularityList_insert(&popList, pop[i], i + 1);
            
            if (err != OK) {
                list_created = false;
                break;
            }
        }
    }    

    // Enable if you want to see list
    // popularityList_print(popList);

    // TEST 1: Find film in an empty list
    failed = false;
    start_test(test_section, "PR3_EX3_1", "Find film in an empty list");

    if (list_created) {
        film = popularityList_get(&popList, 1)->e.film;
        position = popularityList_getPosByFilm(&emptyList, &film);

        if (position != -1) {
            failed = true;
        }

    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX3_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_1", true);
    }

    // TEST 2: Find random film
    failed = false;
    start_test(test_section, "PR3_EX3_2", "Find random film in list");


    if (list_created) {
        randomPosition = (rand() % popList.size) + 1;

        film = popularityList_get(&popList, randomPosition)->e.film;

        position = popularityList_getPosByFilm(&popList, &film);

        if (position != randomPosition) {
            failed = true;
        }

    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX3_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_2", true);
    }

    // TEST 3: Find non-existing film in list
    failed = false;
    start_test(test_section, "PR3_EX3_3", "Find non-existing film in list");

    if (list_created) {
        // Find existing film, just to ensure it's implemented
        film = popularityList_get(&popList, 1)->e.film;

        position = popularityList_getPosByFilm(&popList, &film);

        if (position != 1) {
            failed = true;
        }

        position = popularityList_getPosByFilm(&popList, &fooFilm);

        if (position != -1) {
            failed = true;
        }
    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX3_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_3", true);
    }

    // TEST 4: Swap two elems, out of bounds
    failed = false;
    start_test(test_section, "PR3_EX3_2A_1", "Swap two elems, out of bounds");

    if (list_created) {
        // Both indexes > LIST_SIZE_FOR_EX3
        err = popularityList_swap(&popList, LIST_SIZE_FOR_EX3 + 1, LIST_SIZE_FOR_EX3 + 1);

        if (err != ERR_INVALID_INDEX) {
            failed = true;
        }

        // One index is 0
        err = popularityList_swap(&popList, 0, LIST_SIZE_FOR_EX3);

        if (err != ERR_INVALID_INDEX) {
            failed = true;
        }

        // One index is 0
        err = popularityList_swap(&popList, 0, LIST_SIZE_FOR_EX3);

        if (err != ERR_INVALID_INDEX) {
            failed = true;
        }

        // Both indexes are 0
        err = popularityList_swap(&popList, 0, 0);

        if (err != ERR_INVALID_INDEX) {
            failed = true;
        }
    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX3_2A_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_2A_1", true);
    }

    // TEST 5: Swap two elements, 1<->9  
    failed = false;
    start_test(test_section, "PR3_EX3_2A_2", "Swap two elements, 1<->9");

    if (list_created) {
        // Exchange pos 1 and 9
        pNode_src = popularityList_get(&popList, 1);
        if (pNode_src != NULL) {
            e_src = pNode_src->e;
            pNode_dst = popularityList_get(&popList, 9);

            if (pNode_dst != NULL) {
                e_dst = pNode_dst->e;
                err = popularityList_swap(&popList, 1, 9);

                if (err != OK) {
                    failed = true;
                }
                else {
                    pNode_src = popularityList_get(&popList, 1);
                    pNode_dst = popularityList_get(&popList, 9);

                    if (!film_equals(&(pNode_src->e.film), &(e_dst.film))
                        || pNode_src->e.stats.numUserFavorited != e_dst.stats.numUserFavorited
                        || pNode_src->e.stats.numUserViews != e_dst.stats.numUserViews) {
                        failed = true;
                    }

                    if (!film_equals(&(pNode_dst->e.film), &(e_src.film))
                        || pNode_dst->e.stats.numUserFavorited != e_src.stats.numUserFavorited
                        || pNode_dst->e.stats.numUserViews != e_src.stats.numUserViews) {
                        failed = true;
                    }

                    if (popList.size != LIST_SIZE_FOR_EX3) {
                        failed = true;
                    }

                    // If you want to see list
                    // popularityList_print(popList);                
                }
            }
            else {
                failed = true;
            }
        }
        else {
            failed = true;
        }
    }
    else {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR3_EX3_2A_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_2A_2", true);
    }

    // TEST 6: Swap two elements, 4<->10
    failed = false;
    start_test(test_section, "PR3_EX3_2A_3", "Swap two elements, 10<->4");

    if (list_created) {
        // Exchange pos 10 and 4
        pNode_src = popularityList_get(&popList, 10);
        if (pNode_src != NULL) {
            e_src = pNode_src->e;
            pNode_dst = popularityList_get(&popList, 4);

            if (pNode_dst != NULL) {
                e_dst = pNode_dst->e;
                err = popularityList_swap(&popList, 10, 4);

                if (err != OK) {
                    failed = true;
                }
                else {
                    pNode_src = popularityList_get(&popList, 10);
                    pNode_dst = popularityList_get(&popList, 4);

                    if (!film_equals(&(pNode_src->e.film), &(e_dst.film))
                        || pNode_src->e.stats.numUserFavorited != e_dst.stats.numUserFavorited
                        || pNode_src->e.stats.numUserViews != e_dst.stats.numUserViews) {
                        failed = true;
                    }

                    if (!film_equals(&(pNode_dst->e.film), &(e_src.film))
                        || pNode_dst->e.stats.numUserFavorited != e_src.stats.numUserFavorited
                        || pNode_dst->e.stats.numUserViews != e_src.stats.numUserViews) {
                        failed = true;
                    }

                    // exchange them again - original position
                    err = popularityList_swap(&popList, 10, 4);

                    if (err != OK) {
                        failed = true;
                    }
                    else {
                        pNode_src = popularityList_get(&popList, 10);
                        pNode_dst = popularityList_get(&popList, 4);

                        if (!film_equals(&(pNode_src->e.film), &(e_src.film))
                            || pNode_src->e.stats.numUserFavorited != e_src.stats.numUserFavorited
                            || pNode_src->e.stats.numUserViews != e_src.stats.numUserViews) {
                            failed = true;
                        }

                        if (!film_equals(&(pNode_dst->e.film), &(e_dst.film))
                            || pNode_dst->e.stats.numUserFavorited != e_dst.stats.numUserFavorited
                            || pNode_dst->e.stats.numUserViews != e_dst.stats.numUserViews) {
                            failed = true;
                        }

                        if (popList.size != LIST_SIZE_FOR_EX3) {
                            failed = true;
                        }
                    }

                    // If you want to see list
                    // popularityList_print(popList);                
                }
            }
            else {
                failed = true;
            }
        }
        else {
            failed = true;
        }
    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR3_EX3_2A_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_2A_3", true);
    }

    // If you want to see list
    // printf("Before sorting:\n\n");
    // popularityList_print(popList);

    // TEST 7: Bubble-sort, ascending order
    failed = false;
    start_test(test_section, "PR3_EX3_2B", "Bubble-sort, ascending order");

    if (list_created) {
        if (OK != popularityList_bubbleSort(&popList)) {
            failed = true;
        }
        else {
            for (int i = 1; i < popList.size; ++i) {

                // Check all elems in descending order, pos i is always < pos i + 1
                pNode_src = popularityList_get(&popList, i);
                pNode_dst = popularityList_get(&popList, i + 1);

                if (popularity_compare(pNode_src->e.stats, pNode_dst->e.stats) == -1) {
                    failed = true;
                }
            }
        }
    }
    else {
        failed = true;
    }

    // If you want to see list
    // printf("After sorting:\n\n");
    // popularityList_print(popList);

    if (failed) {
        end_test(test_section, "PR3_EX3_2B", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_2B", true);
    }

    if (list_created) {
        for (int i = 0; i < sizeof(pop) / sizeof(tPopularity); ++i) {
            popularity_free(&(pop[i]));
        }
        popularityList_free(&popList);
    }
    
    series_free(&series);
    film_free(&fooFilm);

    return passed;
}

