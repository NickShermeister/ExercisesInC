/* Simple word counting completed for Software Systems 2019 at Olin College.
Creator: Nicholas Sherman

*/
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFERSIZE 1024

void iterator(gpointer key, gpointer value, gpointer user_data) {
  // printf("Size of key: %d\n", sizeof(key));
  // printf("keyval: %d\n", key);
  char* tempkey = (char*) key;
  // printf("tempkey: %s\n", tempkey);
 printf(user_data, key, value);
}

int main(int argc, char** argv) {
  //Make sure that we're starting at the right arg; we know this based on what we take in (every valid arg increments this).
  int start = 1;
  int opt;
  FILE *out;
  int num_args = 0;

  while((opt = getopt(argc, argv, "f")) != -1)
  {
    num_args++;
      switch(opt)
      {
          case 'f':
            start++;
            out = fopen(argv[start], "r");
            if(out == NULL){
              printf("File entered is not a valid file. Please try again.");
              return -1;
            }
            break;

          default:
            printf("That is not a valid input arguments. Input file as -f filename. Input was: %c\n", opt);
            return -1;
      }
  }

  if(num_args == 0){
    printf("No file entered. Opening answers.txt.\n");
    out = fopen("answers.txt", "r");
  }

  char x[BUFFERSIZE]; //in case there are some really long words
  char y[BUFFERSIZE];
  char * pointer1;
  char * pointer2;

  GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

  if(hash == NULL){
    printf("Unable to create hash table.\n");
    return -1;
  }

  int temp;
  int total_wordcount = 0;

  while (fscanf(out, " %1023s", x) == 1) {
    total_wordcount++;
    temp = 1;
    pointer1 = &x[0];
    pointer2 = &y[0];
    // puts(x);
    while (*pointer1)
    {
       if (ispunct(*pointer1))
       {  // Skip because [punct]
          pointer1++;
          // printf("Is punctuation!: %c\n", *pointer1);
       }
       else if (isupper(*pointer1))
       {
          // All lowercase is probably better
          *pointer2 = tolower(*pointer1);
          pointer2++;
          pointer1++;
       }
       else
       {
          // Copy character
          // printf("Is not punctuation! %c\n", *pointer1);
          *pointer2 = *pointer1;
          pointer1++;
          pointer2++;
       }
    }

    if(g_hash_table_contains(hash, y)){
      temp = g_hash_table_lookup(hash, y);
      g_hash_table_replace(hash, g_strdup(y), (temp + 1));
    }
    else {
       g_hash_table_insert(hash, g_strdup(y), temp);
    }

    memset(x, 0, BUFFERSIZE);
    memset(y, 0, BUFFERSIZE);

  }

  g_hash_table_foreach(hash, (GHFunc)iterator, "The number of occurances of %s:\t\t %d\n");

  printf("The total word count was: %d\n", total_wordcount);
  //Fun fact: apparently "villa" is the last unique word in BOTH frankenstein and sherlock holmes!!!!! Feel free to try using the two .txt files in this directory.

 g_hash_table_destroy(hash);
 fclose(out);

 return 0;
}
