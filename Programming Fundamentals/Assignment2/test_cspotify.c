/*******************************************************************************
> CSpotify - 20T3 COMP1511 Assignment 2
| test_cspotify.c
|
| zID: z5306312
| Name: Leon Liao (Wang Liao
| Date: 15/11/2020
|
| Version 1.0.0: Assignment released.
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_cspotify.h"
#include "cspotify.h"
#include "capture.h"

/*********************************************
> Test Functions
| These tests are explained in test_cspotify.h
*********************************************/

/*********
> STAGE 1
*********/

// Test function for 'add_playlist'
void test_add_playlist(void) {

    // Test 1: Does add_playlist return SUCCESS and add 
    // when adding one Playlist with a valid name?
    Library testLibrary1 = create_library();

    int result1 = add_playlist(testLibrary1, "Favourites");
    if (result1 != SUCCESS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    char printText[10000];
    CAPTURE(print_library(testLibrary1), printText, 10000);
    if (!string_contains(printText, "Favourites")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 2: Does add_playlist return ERROR_INVALID_INPUTS
    // and not add the Playlist into the Library
    // when trying to add a Playlist with an invalid name?
    Library testLibrary2 = create_library();
    
    int result2 = add_playlist(testLibrary2, "***");
    if (result2 != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    // Test 3: Does add_playlist add the multiple Playlists into the Library
    // when trying to add Playlists with an valid name?
    Library testLibrary3 = create_library();

    add_playlist(testLibrary3, "AB");
    add_playlist(testLibrary3, "CD");
    
    CAPTURE(print_library(testLibrary3), printText, 10000);
    if (!string_contains(printText, "[*] 0. AB\n[ ] 1. CD")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    printf("MEETS SPEC\n");
}

// Test function for 'rename_playlist'
void test_rename_playlist(void) {
   
    // Test 1: Does rename_playlist return ERROR_NOT_FOUND 
    // when trying to rename a Playlist when the Library is empty
    Library testLibrary1 = create_library();

    int result = rename_playlist(testLibrary1, "Favourites", "Dislikes");
    if (result != ERROR_NOT_FOUND) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 2: Does rename_playlist successfully rename a Playlist
    // when a valid new Playlist name is given to 
    // rename an existing Playlist in the Library?
    Library testLibrary2 = create_library();
    
    add_playlist(testLibrary2, "Favourites");
    
    rename_playlist(testLibrary2, "Favourites", "Dislikes");
    
    char printText[10000];
    CAPTURE(print_library(testLibrary2), printText, 10000);
    if (!string_contains(printText, "Dislikes")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    // Test 3: Does rename_playlist successfully rename 
    // multiple Playlists when a valid new Playlist name is given to 
    // rename an existing Playlist in the Library?
    Library testLibrary3 = create_library();
    
    add_playlist(testLibrary3, "BLACKPINK");
    
    rename_playlist(testLibrary3, "BLACKPINK", "Michael");
    rename_playlist(testLibrary3, "Michael", "Leon");
    
    CAPTURE(print_library(testLibrary3), printText, 10000);
    if (!string_contains(printText, "Leon")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    printf("MEETS SPEC\n");
}


/*********
> STAGE 2
*********/

// Test function for 'add_track'
void test_add_track(void) {
    // Test 1: Does add_track successfully add 
    // multiple (more than 3 Tracks) Tracks 
    // to the Library?
    Library testLibrary1 = create_library();
    
    add_playlist(testLibrary1, "Favourites");
    
    add_track(testLibrary1, "1st", "name", 61, 0);
    add_track(testLibrary1, "2nd", "name", 61, 1);
    add_track(testLibrary1, "3rd", "name", 61, 2);
    add_track(testLibrary1, "4th", "name", 61, 1);
    
    char printText[10000];
    CAPTURE(print_library(testLibrary1), printText, 10000);
    if (!(string_contains(
            printText, 
            "1st                                 name                        01:01\n       - 4th"
        )
        && string_contains(
            printText, 
            "4th                                 name                        01:01\n       - 2nd"
        )
        && string_contains(
            printText, 
            "2nd                                 name                        01:01\n       - 3rd"
        ) 
        && string_contains(
            printText, 
            "3rd                                 name                        01:01"
        ))) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    // Test 2: Library is empty.
    Library testLibrary2 = create_library();
    
    int result2 = add_track(testLibrary2, "title1", "artist1", 61, 0);
    if (result2 != ERROR_NOT_FOUND) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    // Test 3: Does add_track return ERROR_INVALID_INPUTS
    // and not add Tracks into the Playlist
    // when trying to add Tracks with invalid names?
    Library testLibrary3 = create_library();
    
    add_playlist(testLibrary3, "2020BEST");
    
    int result31 = add_track(testLibrary3, "***", "artist1", 61, 0);
    if (result31 != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    int result32 = add_track(testLibrary3, "title2", "artist2", -1, 0);
    if (result32 != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    int result33 = add_track(testLibrary3, "title3", "artist3", 61, -1);
    if (result33 != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    printf("MEETS SPEC\n");
}

// Test function for 'playlist_length'
void test_playlist_length(void) {
    
    // Test 1: Does playlist_length work for Tracks 
    // with lengths greater than 60 seconds?
    Library testLibrary1 = create_library();
    
    add_playlist(testLibrary1, "Original");
    add_track(testLibrary1, "title1", "artist1", 61, 0);
    
    char printText[10000];
    int playlistMinutes1, playlistSeconds1;
    playlist_length(testLibrary1, &playlistMinutes1, &playlistSeconds1);
    CAPTURE(printf(
        "Selected playlist total length: ""%d minutes %d seconds\n", 
        playlistMinutes1, 
        playlistSeconds1);, 
        printText, 
        10000
    );
    
    if (!string_contains(
            printText, "Selected playlist total length: 1 minutes 1 seconds"
        )) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    // Test 2: Library is empty.
    Library testLibrary2 = create_library();
    
    int playlistMinutes2, playlistSeconds2;
    playlist_length(testLibrary2, &playlistMinutes2, &playlistSeconds2);
    CAPTURE(printf(
        "Selected playlist total length: ""%d minutes %d seconds\n", 
        playlistMinutes2, 
        playlistSeconds2);, 
        printText, 
        10000
    );
    
    if (!string_contains(
            printText, "Selected playlist total length: -1 minutes -1 seconds"
        )) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    printf("MEETS SPEC\n");
}


/*********
> STAGE 3
*********/

// Test function for 'delete_playlist'
void test_delete_playlist(void) {
    
    // Test 1: Does delete_playlist work if
    // the selected Playlist is the first Playlist
    // in the Library?
    Library testLibrary1 = create_library();
    
    add_playlist(testLibrary1, "1st");
    
    delete_playlist(testLibrary1);
    
    char printText[10000];
    CAPTURE(print_library(testLibrary1), printText, 10000);
    if (string_contains(printText, "1st")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 2: Does delete_playlist work if
    // the selected Playlist is not the first Playlist
    // in the Library?
    Library testLibrary2 = create_library();
    
    add_playlist(testLibrary2, "1st");
    add_playlist(testLibrary2, "2nd");
    
    select_next_playlist(testLibrary2);
    
    delete_playlist(testLibrary2);
    
    CAPTURE(print_library(testLibrary2), printText, 10000);
    if (!string_contains(printText, "[*] 0. 1st")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    printf("MEETS SPEC\n");
}


/*********
> STAGE 4
*********/

// Test function for 'soundex_search'
void test_soundex_search(void) {
    // Test 1: Does test_soundex_search work if
    // the input is invalid?
    Library testLibrary1 = create_library();
    
    add_playlist(testLibrary1, "2020BEST");
    add_track(testLibrary1, "PrettySavage", "BLACKPINK", 316, 0);
    
    char printText[10000];
    CAPTURE(soundex_search(testLibrary1, "***"), printText, 10000);
    
    if (string_contains(printText, "PrettySavage")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    // Test 2: Does test_soundex_search successfully encode 
    // multiple (more than 3 names) names?
    Library testLibrary2 = create_library();
    
    add_playlist(testLibrary2, "Workout");
    
    add_track(testLibrary2, "Red", "Robart", 100, 0);
    add_track(testLibrary2, "Red", "Taylor", 100, 1);
    add_track(testLibrary2, "Yellow", "Rebert", 500, 2);
    add_track(testLibrary2, "Green", "robert", 100, 3);
    
    CAPTURE(soundex_search(testLibrary2, "Robert"), printText, 10000);
    if (!(string_contains(printText, "Red                                 Robart                      01:40\n       - Yellow")
        && string_contains(printText, "Yellow                              Rebert                      08:20\n       - Green")
        && string_contains(printText, "Green                               robert                      01:40"))) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    printf("MEETS SPEC\n");
}


/*********
> EXTRA
*********/

//  Your extra tests (Not worth marks)
void extra_tests(void) {
    // TODO: Add any extra tests you have here
    printf("MEETS SPEC\n");
}

/*****************
> Helper Functions
*****************/

// Find the string 'needle' in 'haystack'
int string_contains(char *haystack, char *needle) {
    return strstr(haystack, needle) != NULL;
}
