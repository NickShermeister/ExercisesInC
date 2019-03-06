/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


typedef regex_t Regex;


/* Returns a new Regex that matches the given pattern.
*
* pattern: string regex
* flags: flags passed to regcomp
* returns: new Regex
*/
Regex *make_regex(char* pattern, int flags) {
    int ret = 1;
    regex_t* regex = malloc(sizeof(regex_t)); //Need to make sure that there is space in the heap

    ret = regcomp(regex, pattern, flags);

    if (ret) {  //ret == 0 iff there was an error
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    return regex;
}

/* Checks whether a regex matches a string.
*
* regex: Regex pointer
* s: string
* returns: 1 if there's a match, 0 otherwise
*/
int regex_match(Regex *regex, char *s) {
    //Needed variables
    int ret;
    char msgbuf[100];
    //Actual comparison
    ret = regexec(regex, s, 0, NULL, 0);

    //What to do based on the return of regexec
    if (!ret) {
        return 1;
    } else if (ret == REG_NOMATCH) {
      // printf("No match.\n");
        return 0;
    } else {
        regerror(ret, regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 0;
    }

}

/* Frees a Regex.
*
* regex: Regex pointer
*/
void regex_free(Regex *regex) {
    regfree(regex); //Uses built-in function to free
}


/* Finds all tracks that match the given pattern.
*
* Prints track number and title.
*/
void find_track_regex(char pattern[])
{
    int i;
    Regex *regex = make_regex(pattern, REG_EXTENDED | REG_NOSUB);

    for (i=0; i<NUM_TRACKS; i++) {
      // printf("Hi\n");
        if (regex_match(regex, tracks[i])) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }

    }

    regex_free(regex);
}


int main (int argc, char *argv[])
{
    // char *pattern = "F";
    char *pattern = "F.*F.*";

    find_track_regex(pattern);

    return 0;
}
