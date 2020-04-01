#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "test_pr1.h"
#include "user.h"
#include "film.h"
#include "series.h"
#include "view.h"

// Run all tests for PR1
bool run_pr1(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR1", "Tests for PR1 exercices");

    section = testSuite_getSection(test_suite, "PR1");
    assert(section != NULL);

    ok = run_pr1_ex1(section) && ok;
    ok = run_pr1_ex2(section) && ok;
    ok = run_pr1_ex3(section) && ok;
    ok = run_pr1_ex4(section) && ok;
    ok = run_pr1_ex5(section) && ok;

    return ok;
}

// Run tests for PR1 exercice 1
bool run_pr1_ex1(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tUserTable users;
    tUser user1, user2, user3;
    tUser * userAux;

    // TEST 1: Initialize the table of users
    failed = false;
    start_test(test_section, "PR1_EX1_1", "Initialize the table of users");
    userTable_init(&users);

    if (userTable_size(&users) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_1", true);
    }

    // TEST 2: Initialize a user
    failed = false;

    start_test(test_section, "PR1_EX1_2", "Initialize a user");

    err = user_init(&user1, "user1", "name of user1", "user1@uoc.edu");

    if (err != OK)
        failed = true;

    err = user_init(&user2, "user1", "name of user1", "user1@uoc.edu");

    if (err != OK)
        failed = true;

    if (!user_equals(&user1, &user2)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_2", true);
    }

    // TEST 3: Add a new user
    failed = false;
    start_test(test_section, "PR1_EX1_3", "Add a new user");

    err = userTable_add(&users, &user1);
    if (err != OK) {
        failed = true;
    }
    if (userTable_size(&users) != 1) {
        failed = true;
    }
    userAux = userTable_find(&users, "user1");
    if (userAux == NULL) {
        failed = true;
    }
    else if (!user_equals(userAux, &user1)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_3", true);
    }

    // TEST 4: Add more users
    failed = false;
    start_test(test_section, "PR1_EX1_4", "Add more users");
    user_init(&user2, "user2", "name of user2", "user2@uoc.edu");
    user_init(&user3, "user3", "name of user3", "user3@uoc.edu");

    err = userTable_add(&users, &user2);
    if (err != OK) {
        failed = true;
    }
    if (userTable_size(&users) != 2) {
        failed = true;
    }
    userAux = userTable_find(&users, "user2");
    if (userAux == NULL) {
        failed = true;
    }
    if (!user_equals(userAux, &user2)) {
        failed = true;
    }

    err = userTable_add(&users, &user3);
    if (err != OK) {
        failed = true;
    }
    if (userTable_size(&users) != 3) {
        failed = true;
    }
    userAux = userTable_find(&users, "user3");
    if (userAux == NULL) {
        failed = true;
    }
    else if (!user_equals(userAux, &user3)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_4", true);
    }

    // TEST 5: Remove a user
    failed = false;
    start_test(test_section, "PR1_EX1_5", "Remove a user");

    userAux = userTable_find(&users, "user2");
    if (userAux == NULL) {
        failed = true;
    }
    err = userTable_remove(&users, &user2);
    if (err != OK) {
        failed = true;
    }
    if (userTable_size(&users) != 2) {
        failed = true;
    }
    userAux = userTable_find(&users, "user2");
    if (userAux != NULL) {
        failed = true;
    }
    userAux = userTable_find(&users, "user1");
    if (userAux == NULL) {
        failed = true;
    }
    userAux = userTable_find(&users, "user3");
    if (userAux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_5", true);
    }

    // TEST 6: Remove a non existing user
    failed = false;
    start_test(test_section, "PR1_EX1_6", "Remove a non existing user");

    err = userTable_remove(&users, &user2);
    if (err != ERR_NOT_FOUND) {
        failed = true;
    }
    if (userTable_size(&users) != 2) {
        failed = true;
    }
    userAux = userTable_find(&users, "user2");
    if (userAux != NULL) {
        failed = true;
    }
    userAux = userTable_find(&users, "user1");
    if (userAux == NULL) {
        failed = true;
    }
    userAux = userTable_find(&users, "user3");
    if (userAux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_6", true);
    }

    // Remove used memory
    user_free(&user1);
    user_free(&user2);
    user_free(&user3);

    userTable_free(&users);
    return passed;
}

// Run tests for PR1 exercice 2
bool run_pr1_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tSeries serie, serieCopy;

    // TEST 1: Initialize a serie
    failed = false;
    start_test(test_section, "PR1_EX2_1", "Initialize a serie");


    err = series_init(&serie, "Stranger Things", SCIENCE_FICTION);

    if (err != OK) {
        failed = true;
    }
    else
    {
        if (strcmp(serie.title, "Stranger Things") != 0) {
            failed = true;
        }
        if (serie.genre != 1) {
            failed = true;
        }
    }
    if (failed) {
        end_test(test_section, "PR1_EX2_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_1", true);
    }

    // TEST 2: Get information from series

    failed = false;
    start_test(test_section, "PR1_EX2_2", "Get information from series");

    if (strcmp(series_getTitle(&serie), "Stranger Things") != 0) {
        failed = true;
    }

    if (series_getGenre(&serie) != SCIENCE_FICTION) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX2_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_2", true);
    }

    // TEST 3: modify series name 
    failed = false;
    start_test(test_section, "PR1_EX2_3", "Modify series name ");

    err = series_mdfyTitle(&serie, "Chapter Eight: The Upside Down");

    if (err != OK) {
        failed = true;
    }
    else {

        if (strcmp(series_getTitle(&serie), "Chapter Eight: The Upside Down") != 0) {
            failed = true;
        }
    }

    if (failed) {
        end_test(test_section, "PR1_EX2_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_3", true);
    }


    // TEST 4: Compare a serie
    failed = false;
    start_test(test_section, "PR1_EX2_4", "Compare a serie");

    err = series_init(&serieCopy, "Chapter Eight: The Upside Down", COMEDY);
    if (series_equals(&serie, &serieCopy)){
        failed = true;
    }
    series_free(&serieCopy);

    series_init(&serieCopy, "Stranger Things", SCIENCE_FICTION);
    if (series_equals(&serie, &serieCopy)){
        failed = true;
    }
    series_free(&serieCopy);

    series_init(&serieCopy, "Chapter Eight: The Upside Down", SCIENCE_FICTION);
    if (!series_equals(&serie, &serieCopy)){
        failed = true;
    }
    series_free(&serieCopy);

    if (failed) {
        end_test(test_section, "PR1_EX2_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_4", true);
    }

    // TEST 5: Copy a serie
    failed = false;
    start_test(test_section, "PR1_EX2_5", "Copy a serie");

    err = series_cpy(&serieCopy, &serie);
    if (err != OK)
        failed = true;

    if (!series_equals(&serieCopy, &serie))
        failed = true;

    if (failed) {
        end_test(test_section, "PR1_EX2_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_5", true);
    }


    series_free(&serie);
    series_free(&serieCopy);
    return passed;
}

// Run tests for PR1 exercice 3
bool run_pr1_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;
    tError err;
    tSeries serie;
    tFilmTable filmTable;
    tFilm film[8];
    tFilm * filmAux;
    int i;

    // TEST 1: Initialize a table of films
    failed = false;
    start_test(test_section, "PR1_EX3_1", "Initialize a film");

    filmTable_init(&filmTable);

    if ((filmTable.elements != NULL) || (filmTable.size != 0)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_1", true);
    }

    // TEST 2: add film to the table
    failed = false;
    start_test(test_section, "PR1_EX3_2", "add film to the serie");

    series_init(&serie, "Stranger Things", SCIENCE_FICTION);

    film_init(&film[0], "Chapter One: The Vanishing of Will Byers", 47, &serie);

    err = filmTable_add(&filmTable, &film[0]);

    if (err != OK) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_2", true);
    }

    // TEST 3: Get table film size
    failed = false;
    start_test(test_section, "PR1_EX3_3", "Get table film size");

    film_init(&film[1], "Chapter Two: The Weirdo on Maple Street", 55, &serie);
    film_init(&film[2], "Chapter Three: Holly, Jolly", 51, &serie);
    film_init(&film[3], "Chapter Four: The Body", 49, &serie);
    film_init(&film[4], "Chapter Five: The Flea and the Acrobat", 52, &serie);
    film_init(&film[5], "Chapter Six: The Monster", 46, &serie);
    film_init(&film[6], "Chapter Seven: The Bathtub", 41, &serie);
    film_init(&film[7], "Chapter Eight: The Upside Down", 54, &serie);

    for (i = 1; i < 8; i++){
        filmTable_add(&filmTable, &film[i]);
    }

    if (filmTable_size(&filmTable) != 8){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_3", true);
    }

    // TEST 4: Find film
    failed = false;
    start_test(test_section, "PR1_EX3_4", "Find film");

    filmAux = filmTable_find(&filmTable, "Chapter Four: The Body");

    if (filmAux == NULL) {
        failed = true;
    }
    else if (strcmp(filmAux->title, "Chapter Four: The Body") != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_4", true);
    }

    // TEST 5: Add duplicated film
    failed = false;
    start_test(test_section, "PR1_EX3_5", "Add duplicated film");

    err = filmTable_add(&filmTable, &film[1]);

    if (err != ERR_DUPLICATED)
        failed = true;

    if (failed) {
        end_test(test_section, "PR1_EX3_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_5", true);
    }

    // TEST 6: Remove a film from the table
    failed = false;
    start_test(test_section, "PR1_EX3_6", "Remove a film");

    filmAux = filmTable_find(&filmTable, "Chapter Five: The Flea and the Acrobat");
    if (filmAux == NULL) {
        failed = true;
    }

    err = filmTable_remove(&filmTable, &film[4]);

    if (err != OK) {
        failed = true;
    }

    if (filmTable_size(&filmTable) != 7) {
        failed = true;
    }

    filmAux = filmTable_find(&filmTable, "Chapter Five: The Flea and the Acrobat");
    if (filmAux != NULL) {
        failed = true;
    }

    filmAux = filmTable_find(&filmTable, "Chapter Three: Holly, Jolly");
    if (filmAux == NULL) {
        failed = true;
    }

    filmAux = filmTable_find(&filmTable, "Chapter Eight: The Upside Down");
    if (filmAux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_6", true);
    }

    // TEST 7: Remove a non existing film

    failed = false;
    start_test(test_section, "PR1_EX3_7", "Remove a non existing film");

    err = filmTable_remove(&filmTable, &film[4]);

    if (err != ERR_NOT_FOUND) {
        failed = true;
    }

    if (filmTable_size(&filmTable) != 7) {
        failed = true;
    }

    filmAux = filmTable_find(&filmTable, "Chapter Five: The Flea and the Acrobat");
    if (filmAux != NULL) {
        failed = true;
    }

    filmAux = filmTable_find(&filmTable, "Chapter Three: Holly, Jolly");
    if (filmAux == NULL) {
        failed = true;
    }

    filmAux = filmTable_find(&filmTable, "Chapter Eight: The Upside Down");
    if (filmAux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_7", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_7", true);
    }

    // Remove used memory
    for (i = 0; i < 8; i++) {
        film_free(&film[i]);
    }

    series_free(&serie);
    filmTable_free(&filmTable);

    return passed;
}

// Run tests for PR1 exercice 4
bool run_pr1_ex4(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tUser userBob, userAlice, userSam;
    tSeries serieBreakingBad, serieStrangerThings;
    tFilmTable filmTable;
    tFilm filmBreakingBad[7];
    tFilm filmStrangerThings[8];
    tViewLog viewLog;
    tView view;
    tFilm* filmFound;
    tDateTime *dt;
    int i;

    user_init(&userBob, "bob", "Bob", "bob@uoc.edu");
    user_init(&userAlice, "alice", "Alice", "alice@uoc.edu");    
    user_init(&userSam, "sam", "Sam", "sam@uoc.edu");

    series_init(&serieBreakingBad, "Breaking Bad", DRAMA);

    filmTable_init(&filmTable);

    film_init(&filmBreakingBad[0], "Pilot", 58, &serieBreakingBad);
    film_init(&filmBreakingBad[1], "Cat's in the Bag...", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[2], "...And the Bag's in the River", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[3], "Cancer Man", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[4], "Gray Matter", 48, &serieBreakingBad);
    film_init(&filmBreakingBad[5], "Crazy Handful of Nothin'", 47, &serieBreakingBad);
    film_init(&filmBreakingBad[6], "A No-Rough-Stuff-Type Deal", 47, &serieBreakingBad);

    for (i = 0; i < 7; i++) {
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

    for (i = 0; i < 8; i++){
        filmTable_add(&filmTable, &filmStrangerThings[i]);
    }

    // TEST 1: Initialize a a view log
    failed = false;
    start_test(test_section, "PR1_EX4_1", "Initialize a a view log");

    viewLog_init(&viewLog);

    if ((viewLog.elements != NULL) || (viewLog.size != 0)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_1", true);
    }

    // TEST 2: add view to the log
    failed = false;
    start_test(test_section, "PR1_EX4_2", "Add view to the log");

    dt = setDateTime(30, 9, 2019, 22, 24);
    view_init(&view, dt, 5, &userAlice, &filmStrangerThings[0]);
    free(dt);

    err = viewLog_add(&viewLog, &view);
    view_free(&view);

    if (err != OK)
        failed = true;

    if (failed) {
        end_test(test_section, "PR1_EX4_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_2", true);
    }

    // TEST 3: search favorite film
    failed = false;
    start_test(test_section, "PR1_EX4_3", "Search favorite film");

    dt = setDateTime(2, 10, 2019, 21, 50);
    view_init(&view, dt, 5, &userAlice, &filmStrangerThings[1]);    
    free(dt);
    
    viewLog_add(&viewLog, &view);
    
    
    dt = setDateTime(1, 10, 2019, 23, 00);
    view_init(&view, dt, 3, &userBob, &filmBreakingBad[0]);
    free(dt);
    
    viewLog_add(&viewLog, &view);

    dt = setDateTime(30, 9, 2019, 22, 13);
    view_init(&view, dt, 5, &userBob, &filmBreakingBad[1]);
    free(dt);
    
    viewLog_add(&viewLog, &view);
    
    
    dt = setDateTime(30, 9, 2019, 23, 05);
    view_init(&view, dt, 4, &userBob, &filmBreakingBad[1]);
    free(dt);
    
    viewLog_add(&viewLog, &view);
    

    filmFound = viewLog_getFavFilm(&viewLog, &userAlice);
    if ((filmFound == NULL) || !film_equals(&filmStrangerThings[0], filmFound)){
        failed = true;
    }
    else if (!film_equals(&filmBreakingBad[1], viewLog_getFavFilm(&viewLog, &userBob))) {
        failed = true;
    }
    else if (viewLog_getFavFilm(&viewLog, &userSam) != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_3", true);
    }

    // TEST 4: user favourite genre 
    failed = false;

    start_test(test_section, "PR1_EX4_4", "User favourite genre ");

    if (SCIENCE_FICTION != viewLog_getFavGenre(&viewLog, &userAlice)){
        failed = true;
    }
    else if (DRAMA != viewLog_getFavGenre(&viewLog, &userBob)) {
        failed = true;
    }
    else if (viewLog_getFavGenre(&viewLog, &userSam) != GENRE_NOT_FOUND) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_4", true);
    }

    // Remove used memory
    user_free(&userAlice);
    user_free(&userBob);
    user_free(&userSam);
    series_free(&serieBreakingBad);
    series_free(&serieStrangerThings);

    for (i = 0; i < 7; i++) {
        film_free(&filmBreakingBad[i]);
    }
    for (i = 0; i < 8; i++) {
        film_free(&filmStrangerThings[i]);
    }

    filmTable_free(&filmTable);
    view_free(&view);
    viewLog_free(&viewLog);

    return passed;
}

// Run tests for PR1 exercice 5
bool run_pr1_ex5(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tUser testUser;

    // TEST 1: Remove spaces at the beginning of string
    failed = false;
    start_test(test_section, "PR1_EX5_1", "Remove leading spaces in name");

    err = user_init(&testUser, "----", "  Joan Pere", "test@uoc.edu");

    if (err != OK)
        failed = true;

    err = user_trimCapitalizeName(&testUser);

    if (err != OK)
        failed = true;

    if (strcmp(testUser.name, "Joan Pere"))
        failed = true;

    user_free(&testUser);

    if (failed) {
        end_test(test_section, "PR1_EX5_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX5_1", true);
    }

    // TEST 2: Remove spaces at the end of string
    failed = false;
    start_test(test_section, "PR1_EX5_2", "Remove ending spaces in name");

    err = user_init(&testUser, "----", "Joan Pere  ", "test@uoc.edu");

    if (err != OK)
        failed = true;

    err = user_trimCapitalizeName(&testUser);

    if (err != OK)
        failed = true;

    if (strcmp(testUser.name, "Joan Pere"))
        failed = true;

    user_free(&testUser);

    if (failed) {
        end_test(test_section, "PR1_EX5_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX5_2", true);
    }

    // TEST 3: Capitalize user's 'name' field with single word
    failed = false;
    start_test(test_section, "PR1_EX5_3", "Capitalize name, single word");

    err = user_init(&testUser, "----", "joAn", "test@uoc.edu");

    if (err != OK)
        failed = true;

    err = user_trimCapitalizeName(&testUser);

    if (err != OK)
        failed = true;

    if (strcmp(testUser.name, "Joan"))
        failed = true;

    user_free(&testUser);

    if (failed) {
        end_test(test_section, "PR1_EX5_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX5_3", true);
    }

    // TEST 4: Capitalize each word in user's name field
    failed = false;
    start_test(test_section, "PR1_EX5_4", "Capitalize name, multiple words");

    err = user_init(&testUser, "----", "joAN pere GAbriel", "test@uoc.edu");

    if (err != OK)
        failed = true;

    err = user_trimCapitalizeName(&testUser);

    if (err != OK)
        failed = true;

    if (strcmp(testUser.name, "Joan Pere Gabriel"))
        failed = true;

    user_free(&testUser);

    if (failed) {
        end_test(test_section, "PR1_EX5_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX5_4", true);
    }

    // TEST 5: Trim and capitalize each word in name
    failed = false;
    start_test(test_section, "PR1_EX5_5", "Cap. name & remove spaces both sides");

    err = user_init(&testUser, "----", "   maria campdevanol   ", "test@uoc.edu");

    if (err != OK)
        failed = true;

    err = user_trimCapitalizeName(&testUser);

    if (err != OK)
        failed = true;

    if (strcmp(testUser.name, "Maria Campdevanol"))
        failed = true;

    user_free(&testUser);

    if (failed) {
        end_test(test_section, "PR1_EX5_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX5_5", true);
    }

    return passed;
}