/*******************************************************************************
> CSpotify - 20T3 COMP1511 Assignment 2
| cspotify.c
|
| zID: z5306312
| Name: Leon Liao (Wang Liao
| Date: 06/11/2020
| Program Description:
| CSpotify goes into organisation of music 
| with things like song information, playlists 
| and personal music libraries. 
| CSpotify is our implementation of a song library 
| using linked lists as the primary data structure.
|
| Version 1.0.0: Assignment released.
|
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cspotify.h"

/******************************************************************************/

#define SEXAGESIMAL_STSTEM 60
#define INVALID_NUMBER -1
#define VALID 1
#define INVALID 0
#define SELECTED 1
#define UNSELECTED 0

/******************************************************************************/
// 'struct library' represents a library, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// playlists, though you may want to add other fields to it.
//
// You may choose to add or change fields in this struct.
struct library {
    struct playlist *head;
};

// 'struct playlist' represents a playlist. 
// You may choose to add or change fields in this struct.
struct playlist {
    char name[MAX_LEN];
    struct track *tracks;
    struct playlist *next;
    int selStat;
    int trackLength;
};

// 'struct trackLength' represents the length of a track. 
// You may choose to add or change fields in this struct.
struct trackLength {
    int minutes;
    int seconds;
};

// 'struct track' represents a track. 
// You may choose to add or change fields in this struct.
struct track {
    char title[MAX_LEN];
    char artist[MAX_LEN];
    struct trackLength length;
    struct track *next;
};

/******************************************************************************/
// Other structs.

/******************************************************************************/
// Prototypes for any extra functions.
//
// Change string from upper to lower.
void upper_to_lower(char string[MAX_LEN]);
//
// Formulate a Soundex encoding form a string.
char *soundex_algorithm(char string[MAX_LEN]);
//
// Check alphanumeric for artist.
int check_artist_alphanumeric(char string[MAX_LEN]);
//
// Check alphanumeric.
int check_alphanumeric(char string[MAX_LEN]);
//
// Create a Playlist.
Playlist creat_playlist(char name[MAX_LEN], int selStat);
//
// Create a Track.
Track creat_track(
    char title[MAX_LEN], 
    char artist[MAX_LEN], 
    int minutes, 
    int seconds
);
//
// Function prototypes for helper functions. 
static void print_playlist(int number, char playlistName[MAX_LEN]);
static void print_selected_playlist(int number, char playlistName[MAX_LEN]);
static void print_track(
    char title[MAX_LEN], char artist[MAX_LEN], int minutes, 
    int seconds
);

/******************************************************************************/
// You need to implement the following functions.
// In other words, write code to make the function work as described 
// in cspotify.h

/*********
> STAGE 1
*********/

// Create a new Library and return a pointer to it.
Library create_library(void) {
    Library newLibrary = malloc(sizeof(struct library));
    newLibrary->head = NULL;
    return newLibrary;
}

// Add a new Playlist to the Library.
//
// Make this Playlist ''selected''.
// Alphanumeric.
int add_playlist(Library library, char playlistName[MAX_LEN]) {
    // Check the given Playlist name is alphanumeric.
    if (check_alphanumeric(playlistName) == INVALID) {
        return ERROR_INVALID_INPUTS;
    }    
    // If the Library has no Playlists.
    if (library->head == NULL) {
        Playlist addPlaylist = creat_playlist(playlistName, SELECTED);
        library->head = addPlaylist;
    }    
    // If the Library has Playlists.
    else if (library->head != NULL) {
        Playlist currPlaylist = library->head;
        Playlist addPlaylist = creat_playlist(playlistName, UNSELECTED);
        while (currPlaylist->next != NULL) {
            currPlaylist = currPlaylist->next;
        }
        currPlaylist->next = addPlaylist;
    } 
     
    return SUCCESS;
}

// Print out the Library.
//
// Use print_playlist, print_selected_playlist and print_track.
void print_library(Library library) {

    // Order number from 0.
    int orderNum = 0;
    Playlist currPlaylist = library->head;   
    while (currPlaylist != NULL) { 
       
        // Print Playlists up to whether they are selected.
        if (currPlaylist->selStat == SELECTED) {
            print_selected_playlist(orderNum, currPlaylist->name);
        } else {
            print_playlist(orderNum, currPlaylist->name);
        }
        
        // Print Tracks wtithin the Playlists.
        Track currTrack = currPlaylist->tracks;       
        while (currTrack != NULL) {
            print_track(
                currTrack->title, currTrack->artist, 
                currTrack->length.minutes, currTrack->length.seconds 
            );            
            currTrack = currTrack->next;
        }
                
        currPlaylist = currPlaylist->next;
        orderNum++;
    }            
}

// Rename the name of an existing Playlist.
//
// Find the playlistName in the Library of Playlists,
// and change its name to the name given in newPlaylistName.
int rename_playlist(Library library, char playlistName[MAX_LEN],
    char newPlaylistName[MAX_LEN]) {
    
    // Check the given Playlist name is alphanumeric.
    if (check_alphanumeric(newPlaylistName) == INVALID) {
        return ERROR_INVALID_INPUTS;
    } else { 
       
        // Find the matched Playlist from the Library.
        Playlist currPlaylist = library->head;
        Playlist matchedPlaylist = NULL;
        // Traverse Playlists.
        while (currPlaylist != NULL) {
            // If the names are same, match!
            if (strcmp(playlistName, currPlaylist->name) == 0) {
                matchedPlaylist = currPlaylist;
            }
            currPlaylist = currPlaylist->next;
        }        
        
        // If the given Playlist is not founded after traverse.
        if (matchedPlaylist == NULL) {
            return ERROR_NOT_FOUND;
        }
        
        // Using strcpy function to rename the name of matched Playlist
        // with newPlaylistName.
        strcpy(matchedPlaylist->name, newPlaylistName);
    }
    
    return SUCCESS;
}


/*********
> STAGE 2
*********/

// Selects the next Playlist in the Library.
//
// Change the selected Playlist in the Library 
// to the Playlist after the currently selected Playlist.
void select_next_playlist(Library library) {
    
    // If Library is empty.
    if (library->head == NULL) {
        return;
    } else {
    
        Playlist currPlaylist = library->head;
        Playlist nextPlaylist = NULL;   
        while (currPlaylist != NULL) {        
            // When the current Playlist is the last one.
            // And if it is selected,
            if (currPlaylist->next == NULL 
             && currPlaylist->selStat == SELECTED) {             
                // Set the first one as the new selected Playlist.
                currPlaylist->selStat = UNSELECTED;
                library->head->selStat = SELECTED;
            }             
            // When the current Playlist is not the last one. 
            // And if it is selected,
            else if (currPlaylist->next != NULL 
                  && currPlaylist->selStat == SELECTED) {
                // Find the next playlist.
                currPlaylist->selStat = UNSELECTED;
                nextPlaylist = currPlaylist->next;               
            }
            currPlaylist = currPlaylist->next;
        }
        
        // Set the next Playlist as selected one.
        if (nextPlaylist != NULL) {
            nextPlaylist->selStat = SELECTED;
        }
    }
}

// Selects the previous Playlist in the Library.
//
// Change the Playlist that is selected 
// to the Playlist before the currently selected Playlist.
void select_previous_playlist(Library library) {
    
    // If Library is empty.
    if (library->head == NULL) {
        return;
    }     
    
    Playlist currPlaylist = library->head;
    Playlist prePlaylist = NULL;
    Playlist lastPlaylist = NULL;
    // When the current Playlist is the first Playlist but not selected.
    if (currPlaylist->selStat != SELECTED) {
        // Traverse following Playlists.
        while (currPlaylist != NULL) {
            // When find the selected one,
            // set it as unselected and set the previous one as selected.
            if (currPlaylist->selStat == SELECTED) {
                currPlaylist->selStat = UNSELECTED;
                prePlaylist->selStat = SELECTED;
            }
            prePlaylist = currPlaylist;
            currPlaylist = currPlaylist->next;
        }
    } 
    
    // When the selected current Playlist is the first Playlist, 
    else if (currPlaylist->selStat == SELECTED) {
        currPlaylist->selStat = UNSELECTED;
        // When currPlaylist == NULL (end of the while loop,
        // set lastPlaylist as the last Playlist, 
        while (currPlaylist != NULL) {
            lastPlaylist = currPlaylist;
            currPlaylist = currPlaylist->next;
        }
        
        // Set the lastPlaylist as the selected one.
        lastPlaylist->selStat = SELECTED;
    }
}

// Add a new Track to the selected Playlist.
//
// Go through the selected Playlist 
// and add a new Track node at the position specified by position.
int add_track(Library library, char title[MAX_LEN], char artist[MAX_LEN], 
    int trackLengthInSec, int position) {    
    
    // If Library is empty.
    if (library->head == NULL) {
        return ERROR_NOT_FOUND;
    } else {    
        
        Playlist currPlaylist = library->head;
        Playlist selPlaylist = NULL;
        while (currPlaylist != NULL) {
            if (currPlaylist->selStat == SELECTED) {
                selPlaylist = currPlaylist;
            }
            currPlaylist = currPlaylist->next;
        }
        
        // Limit the scale of valid inputs.
        if (
            check_alphanumeric(title) == INVALID 
            || check_alphanumeric(artist) == INVALID
            || position < 0 
            || position > selPlaylist->trackLength
            || trackLengthInSec < 0
            ) {
            return ERROR_INVALID_INPUTS;
        }
        
        int trackMin = trackLengthInSec / SEXAGESIMAL_STSTEM;
        int trackSec = trackLengthInSec % SEXAGESIMAL_STSTEM;
        // Create a new Track node.
        Track addTrack = creat_track(title, artist, trackMin, trackSec);
        
        // Add a new Track node at the position specified by position.
        Track currTrack = selPlaylist->tracks;
        
        // When the position is the beginning of the Playlist.
        if (position == 0) {
            // Order: addTrack->currTrack.
            addTrack->next = currTrack;
            selPlaylist->tracks = addTrack;
            // Length of track + 1.
            selPlaylist->trackLength++;
        } 
        // When the position is the end of the Playlist.
        else if (position == selPlaylist->trackLength) {
            while (currTrack->next != NULL) {
                currTrack = currTrack->next;
            }
            // Order: currTrack->addTrack.
            currTrack->next = addTrack;
            // Length of track + 1.
            selPlaylist->trackLength++;
        } 
        // When the position is between 
        // the beginning and the end of the Playlist.
        else if (position > 0 && position < selPlaylist->trackLength) {
            int i = 1;
            while (i < position && currTrack != NULL) {
                currTrack = currTrack->next;
                i++;
            }
            addTrack->next = currTrack->next;
            currTrack->next = addTrack;
            selPlaylist->trackLength++;
        }
    }
    
    return SUCCESS;
}

// Calculate the total length of the selected Playlist in minutes and seconds.
//
// Go through and calculate the length of 
// the currently selected Playlist in the Library.
void playlist_length(
    Library library, int *playlistMinutes, 
    int *playlistSeconds
) { 
    
    // If Library is empty.   
    if (library->head == NULL) {
        *playlistMinutes = INVALID_NUMBER;
        *playlistSeconds = INVALID_NUMBER;
        return;
    } else {
    
        // Find the selected Playlist for calculating the length of it.   
        Playlist currPlaylist = library->head;
        Playlist selPlaylist = NULL;
        while (currPlaylist != NULL) {
            if (currPlaylist->selStat == SELECTED) {
                selPlaylist = currPlaylist;
            }
            currPlaylist = currPlaylist->next;
        }                
        *playlistMinutes = 0;
        *playlistSeconds = 0;
        if (selPlaylist->tracks == NULL) {
            return;   
        }

        Track currTrack = selPlaylist->tracks;
        while (currTrack != NULL) {
            // The total number of minutes in the Playlist 
            // should be stored inside the memory pointed to 
            // by the playlistMinutes pointer.
            *playlistMinutes += currTrack->length.minutes;
            // The total number of seconds in the Playlist 
            // should be stored in the memory pointed to 
            // by the playlistSeconds pointer.
            *playlistSeconds += currTrack->length.seconds;
            currTrack = currTrack->next;
        }
        
        // If *playlistSeconds = 60, set it to 0.
        // *playlistMinutes + 1.
        *playlistMinutes = *playlistMinutes 
                         + *playlistSeconds / SEXAGESIMAL_STSTEM;
        *playlistSeconds = *playlistSeconds % SEXAGESIMAL_STSTEM;
    }
}


/*********
> STAGE 3
*********/

// Delete the first instance of the given track in the selected Playlist
// of the Library.
void delete_track(Library library, char track[MAX_LEN]) {
    
    // If Library is empty.  
    if (library->head == NULL) {
        return;
    }

    Playlist currPlaylist = library->head;
    Playlist selPlaylist = NULL;
    while (currPlaylist != NULL) {
        if (currPlaylist->selStat == SELECTED) {
            selPlaylist = currPlaylist;
        }
        currPlaylist = currPlaylist->next;
    }    
    if (selPlaylist->tracks == NULL) {
        return;   
    }
    
    Track currTrack = selPlaylist->tracks;
    if (strcmp(track, currTrack->title) == 0) {
        Track temTrack = selPlaylist->tracks;
        // Delete the first Track.
        selPlaylist->tracks = selPlaylist->tracks->next;
        free(temTrack);
    } else {
        while (currTrack->next != NULL) {
            if (strcmp(track, currTrack->title) == 0) {
                Track temTrack = currTrack;
                // Delete remaining Tracks.
                currTrack->next = currTrack->next->next;
                free(temTrack);
            }
            currTrack = currTrack->next;
        }
    }    
}

// Delete the selected Playlist and select the next Playlist in the Library.
//
// Delete the entire selected Playlist 
// as well as all the Tracks within this Playlist.
void delete_playlist(Library library) {
    
    // If Library is empty.      
    if (library->head == NULL) {
        return;
    } else {        
        
        Playlist currPlaylist = library->head;
        Playlist selPlaylist = NULL;
        Playlist prePlaylist = NULL;
        Playlist selPrePlaylist = NULL;
        while (currPlaylist != NULL) {
            if (currPlaylist->selStat == SELECTED) {
                // Find the selected Playlist.
                selPlaylist = currPlaylist;
                // Find the selected previous Playlist.
                selPrePlaylist = prePlaylist;
            }
            // Find the prevoius Playlist.
            prePlaylist = currPlaylist;
            currPlaylist = currPlaylist->next;
        }
        
        // Delete all the Tracks within this Playlist.
        Track currTrack = selPlaylist->tracks;
        while (currTrack != NULL) {
            // Use temporary Track to avoid access to 
            // the memory that has already been freed.
            Track temTrack = currTrack;
            currTrack = currTrack->next;
            free(temTrack);
        }
        
        // Delete the entire selected Playlist.
        //
        // Delete the first Playlist.
        if (selPlaylist == library->head) {      
            library->head = library->head->next;    
            if (library->head != NULL) {
                library->head->selStat = SELECTED;
            }
            free(selPlaylist);
        } 
        // Delete the last Playlist.
        else if (selPlaylist->next == NULL) {
            library->head->selStat = SELECTED;
            library->head->next = NULL;
            free(selPlaylist);
        } 
        // Delete remaining Playlists.
        else {            
            selPlaylist->next->selStat = SELECTED;
            selPrePlaylist->next = selPlaylist->next;
            free(selPlaylist);
        }        
    }
}

// Delete an entire Library and its associated Playlists and Tracks.
void delete_library(Library library) {
    
    // If Library is empty.  
    if (library->head == NULL) {
        free(library);
        return;
    } else {
        
        // Delete all Playlists.
        Playlist currPlaylist = library->head;
        while (currPlaylist != NULL) {
            // Delete all Tracks within each Playlist.
            Track currTrack = currPlaylist->tracks;
            while (currTrack != NULL) {
                // Use temporary Track to avoid access to 
                // the memory that has already been freed.
                Track temTrack = currTrack;
                currTrack = currTrack->next;
                free(temTrack);
            }
            // Use temporary Playlist to avoid access to 
            // the memory that has already been freed.
            Playlist temPlaylist = currPlaylist;
            currPlaylist = currPlaylist->next;
            free(temPlaylist);
        }
    }
    
    free(library);
}


/*********
> STAGE 4
*********/

// Cut the given track in selected Playlist and paste it into the given 
// destination Playlist.
//
// It should remove the first Track instance which matches the given trackName 
// from the selected Playlist and add it into the end of 
// the Playlist with the given destination Playlist name.
int cut_and_paste_track(Library library, char trackTitle[MAX_LEN], 
    char destPlaylist[MAX_LEN]) {
    
    // If Library is empty.  
    if (library->head == NULL) {
        return ERROR_NOT_FOUND;
    } 
    
    Playlist currPlaylist = library->head;
    Playlist selPlaylist = NULL;
    Playlist tgtPlaylist = NULL;
    while (currPlaylist != NULL) {
        if (currPlaylist->selStat == SELECTED) {
            // Find the selected Playlist.
            selPlaylist = currPlaylist;
        } else if (strcmp(currPlaylist->name, destPlaylist) == 0) {
            // Find the target Playlist.
            tgtPlaylist = currPlaylist;
        }
        currPlaylist = currPlaylist->next;
    }
    if (tgtPlaylist == NULL) {
        return ERROR_NOT_FOUND;
    }
    
    Track currTrack = selPlaylist->tracks;
    Track tgtTrack = NULL;
    while (currTrack != NULL) {
        // Find the target Track.
        if (strcmp(currTrack->title, trackTitle) == 0) {
            if (currTrack == selPlaylist->tracks) {
                selPlaylist->tracks = selPlaylist->tracks->next;
            } 
            currTrack->next = NULL;
            tgtTrack = currTrack;
        }
        currTrack = currTrack->next;
    }    
    if (tgtTrack == NULL) {
        return ERROR_NOT_FOUND;
    }
    
    // If target Playlist has no Tracks.
    if (tgtPlaylist->tracks == NULL) {
        // Add given track to its head.
        tgtPlaylist->tracks = tgtTrack;
    } 
    // If target Playlist already has Tracks.
    else {
        // Traversing to the end by using counter Track.
        Track cntTrack = tgtPlaylist->tracks;
        while (cntTrack->next != NULL) {
            cntTrack = cntTrack->next;
        }
        // Add given target Track to the end of the target Playlist.
        cntTrack->next = tgtTrack;
    }
        
    return SUCCESS;
}

// Print out all Tracks with artists that have the same Soundex Encoding 
// as the given artist.
//
// Go through the given Library and print out all Tracks with artists 
// that have the same Soundex encoding as the given search term.
// Use the given help function print_track.
void soundex_search(Library library, char artist[MAX_LEN]) {
    
    // If Library is empty.
    if (library->head == NULL) {
        return;
    }
    
    // Check alphanumeric for artist.
    if (check_artist_alphanumeric(artist) == INVALID) {
        return;
    }
    
    // Go through the Library.
    Playlist currPlaylist = library->head;
    while (currPlaylist != NULL) {
        Track currTrack = currPlaylist->tracks;
        while (currTrack != NULL) {
            // Find artists that have the same Soundex encoding 
            // as the given search term.
            char *encoding1 = soundex_algorithm(artist);
            char *encoding2 = soundex_algorithm(currTrack->artist);
            if (strcmp(encoding1, encoding2) == 0) {
                // Print out the matching Tracks.
                print_track(
                    currTrack->title,
                    currTrack->artist,
                    currTrack->length.minutes,
                    currTrack->length.seconds
                );
            }
            free(encoding1);
            free(encoding2);
            currTrack = currTrack->next;
        }
        currPlaylist = currPlaylist->next;
    }
}


/*********
> STAGE 5
*********/

// Move all Tracks matching the Soundex encoding of the given artist 
// to a new Playlist.
//
// Go through the entire Library and move all Tracks 
// with artists that have the same Soundex Encoding 
// as the given artist into a new Playlist named with the given artist
int add_filtered_playlist(Library library, char artist[MAX_LEN]) {
    return SUCCESS;
}

// Reorder the selected Playlist in the given order 
// specified by the order array.
void reorder_playlist(Library library, int order[MAX_LEN], int length) {
    
    // If Library is empty.
    if (library->head == NULL) {
        return;
    }
}

/*****************
> Helper Functions
*****************/
//
// Change string from upper to lower.
void upper_to_lower(char string[MAX_LEN]) {
    int i = 0;
    while (string[i] != '\0') {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            string[i] += 32;
        }
        i++;
    }
}
//
// Formulate a Soundex encoding form a string.
char *soundex_algorithm(char string[MAX_LEN]) {
    // Retain the first letter.
    //    
    // Change encoding from upper to lower.
    char *encoding = malloc (sizeof (char[MAX_LEN]));
    strcpy(encoding, string);
    upper_to_lower(encoding);
        
    char firstLetter = encoding[0];
    encoding[0] = firstLetter - 32;
    
    int i = 0;
    while (encoding[i] != '\0') {
        // Map all occurrence of a, e, i, o, u, y, h, w, to zero (0).
        if (
               encoding[i] == 'a' || encoding[i] == 'e' || encoding[i] == 'i' 
            || encoding[i] == 'o' || encoding[i] == 'u' || encoding[i] == 'y' 
            || encoding[i] == 'h' || encoding[i] == 'w'
            ) {
            encoding[i] = '0';
        }
        // Replace all consonants after the first letter with digits.
        // - b, f, p, v -> 1
        else if (
               encoding[i] == 'b' || encoding[i] == 'f' || encoding[i] == 'p' 
            || encoding[i] == 'v'
        ) {
            encoding[i] = '1';
        }
        // - c, g, j, k, q, s, x, z -> 2
        else if (
               encoding[i] == 'c' || encoding[i] == 'g' || encoding[i] == 'j' 
            || encoding[i] == 'k' || encoding[i] == 'q' || encoding[i] == 's' 
            || encoding[i] == 'x' || encoding[i] == 'z'
                ) {
            encoding[i] = '6';
        }
        // - d, t -> 3
        else if (encoding[i] == 'd' || encoding[i] == 't') {
            encoding[i] = '6';
        }
        // - l -> 4
        else if (encoding[i] == 'l') {
            encoding[i] = '6';
        }
        // - m, n -> 5
        else if (encoding[i] == 'm' || encoding[i] == 'n') {
            encoding[i] = '6';
        }
        // - r -> 6
        else if (encoding[i] == 'r') {
            encoding[i] = '6';
        }        
        
        // Replace all adjacent same digits with one digit, 
        // and then remove all the zero (0) digits.
        //
        // If the first digit matches 
        // the numerical encoding of the first letter, 
        // remove the digit.
        else if (encoding[i] == encoding[i + 1] || encoding[i] == '0') {
            encoding[i] = encoding[i + 1];
        }
        
        i++;
    }
    
    // Append 3 zeros if result contains less than 3 digits. 
    // Remove all except first letter and 3 digits after it.
    while (i < 4) {
        encoding[i] = '0';
        i++;
    }
    
    return encoding;
}
//
// Check alphanumeric for artist name.
int check_artist_alphanumeric(char string[MAX_LEN]) {
    int i = 0;
    
    // Not alphanumeric if return 0.
    while (string[i] != '\0' && string[i] != '\n') {
        if (!(
            (string[i] >= 'a' && string[i] <= 'z') 
         || (string[i] >= 'A' && string[i] <= 'Z') 
        )) {
            return INVALID;
        }
        i++;
    }    
    
    // Alphanumeric if return 1.
    return VALID;
}
//
// Create a Track.
Track creat_track(
    char title[MAX_LEN], 
    char artist[MAX_LEN], 
    int minutes, 
    int seconds
) {
    Track track = malloc(sizeof (struct track));
    strcpy(track->title, title);
    strcpy(track->artist, artist);
    track->length.minutes = minutes;
    track->length.seconds = seconds;
    track->next = NULL;
    
    return track;
}
//
// Create a Playlist.
Playlist creat_playlist(char name[MAX_LEN], int selStat) {
    Playlist playlist = malloc(sizeof (struct playlist));
    strcpy(playlist->name, name);
    playlist->tracks = NULL;
    playlist->next = NULL;
    playlist->selStat = selStat;
    playlist->trackLength = 0;
    
    return playlist;
}
//
// Check alphanumeric.
int check_alphanumeric(char string[MAX_LEN]) {
    int i = 0;
    
    // Not alphanumeric if return 0.
    while (string[i] != '\0' && string[i] != '\n') {
        if (!(
               (string[i] >= 'a' && string[i] <= 'z') 
            || (string[i] >= 'A' && string[i] <= 'Z') 
            || (string[i] >= '0' && string[i] <= '9')
        )) {
            return INVALID;
        }
        i++;
    }   
    
    // Alphanumeric if return 1.
    return VALID;
}

static void print_playlist(int number, char playlistName[MAX_LEN]) {
    printf("[ ] %d. %s\n", number, playlistName);
}

static void print_selected_playlist(int number, char playlistName[MAX_LEN]) {
    printf("[*] %d. %s\n", number, playlistName);
}

static void print_track(
    char title[MAX_LEN], char artist[MAX_LEN], int minutes, 
    int seconds
) {
    printf("       - %-32s    %-24s    %02d:%02d\n", title, artist, 
        minutes, seconds);
}
