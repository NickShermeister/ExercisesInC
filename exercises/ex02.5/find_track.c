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


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
/*
  Ex: [A-F] checks for all titles that contains one of the capital letters A - f


*/
void find_track_regex(char pattern[])
{
  int track_usage[NUM_TRACKS];
  int i;
  int status;
  regex_t reg;
  int regcomp_val;

  for (i = 0; i < NUM_TRACKS; i++){
    track_usage[i] = 0;
  }
  char* string;

  for (i = 0; i < NUM_TRACKS; i++){
    string = tracks[i];

    regcomp_val = regcomp(&reg, pattern, REG_EXTENDED|REG_NOSUB);
    if (regcomp_val != 0) {
      printf("Error within regcomp:\n");
      if (regcomp_val == REG_BADPAT) {
        printf("Invalid regular expression.\n");
      }
      else {
        printf("Error not specifically addressed in this code. Look up the following error message at http://pubs.opengroup.org/onlinepubs/7908799/xsh/regex.h.html:\n");

        switch (regcomp_val){
          case REG_EXTENDED:
            printf("REG_EXTENDED error.\n");
            break;
          case REG_ECOLLATE:
            printf("REG_ECOLLATE error.\n");
            break;
          case REG_ECTYPE:
            printf("REG_ECTYPE error.\n");
            break;
          case REG_ESUBREG:
            printf("REG_ESUBREG error.\n");
            break;
          case REG_EBRACK:
            printf("REG_EBRACK error.\n");
            break;
          case REG_EPAREN:
            printf("REG_EPAREN error.\n");
            break;
          case REG_EBRACE:
            printf("REG_EBRACE error.\n");
            break;
          case REG_BADBR:
            printf("REG_BADBR error.\n");
            break;
          case REG_ERANGE:
            printf("REG_ERANGE error.\n");
            break;
          case REG_ESPACE:
            printf("REG_ESPACE error.\n");
            break;
          case REG_BADRPT:
            printf("REG_BADRPT error.\n");
            break;
          case REG_ENOSYS:
            printf("REG_ENOSYS error.\n");
            break;

          default:
            printf("Unknown error message. Value of %i.\n", regcomp_val);

        }
      }
      exit(1);
    }

    status = regexec(&reg, string, (size_t) 0, NULL, 0);

    // printf("Status is: %i\n", status);
    if (status == 0) { //If status is 0, then it's not in the track.
      printf("Track %i: '%s'\n", i, tracks[i]);
      }
    else if (status == REG_ENOSYS){
      printf("Function is not suported, REG_ENOSYS returned.");
    }
  }

  regfree(&reg);
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    // find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
