/*
  A student implementation of the Linux tee function.
  Done by Nicholas Sherman for Software Systems
  2/22/19


  #3
  What worked:
  Tackling the code 1 section at a time
  Knowing what to google

  What didn't work/slowed me down:
  Not fully defining the problem beforehand (thinking that I needed --help, --output-error, and --Version)
  Not asking the NINJAs for clarifying questions

  What I would do differently next time:
  Ask the NINJAs for complete clarification beforehand.
  Read the man pages of functions I'm not familiar with a little sooner instead of trying to copy examples


  #4: (In comparison to the professional solution) What I don't see in my code is:
  Any structures at all for the list
  All the include statements
  Better failure checking (I hae relatively few points to catch someone's failures)
  The declaration of the functions earlier in the code than I make them.
  The signal function? I don't know what that is; it's related to the -i flag
  There is a second function, "add" that adds stuff to the LIST struct
  The professional version uses "warn" for if something is wrong and exits with an exitvalue of 1.


*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFERSIZE 2
#define MAX_OUTS 10
int main (int argc, char *argv[]){
  // printf("Argc: %i\n", argc);
  //Variable declarations
  unsigned char buffer[BUFFERSIZE];
  int i;
  //Make sure that we're starting at the right arg; we know this based on what we take in (every valid arg increments this).
  int start = 1;
  int append = 0;
  FILE *outs[MAX_OUTS];
  int opt;

  //Loop through args
  while((opt = getopt(argc, argv, "ahi")) != -1)
  {
      switch(opt)
      {
          case 'i':
            //TODO: If time allows, implement.
            printf("-i is not currently implemented due to the creator caring about his sleep.\n");
            start++;
            return -1;
            break;
          case 'a':
            append = 1;
            // printf("Now appending.\n");
            start++;
            break;
          case 'h':
            printf("The only implemented option is -a.\n");
            start++;
            return -1;
            break;
          default:
            printf("That is not a valid input arguments. Refer to -h for what inputs are valid. Input was: %c\n", optopt);
            return -1;
      }
  }

  //Step 1: open file, writing over old contents if necessary
  for(i = start; i < argc; i++){
    printf("Attempt %i\n", i);
    printf("%s\n", argv[i]);
    if(append == 0){
      outs[i-start] = fopen(argv[i], "w");
    }
    else {
      outs[i-start] = fopen(argv[i], "a");
    }
  }


  //Step 2: Read from stdio
  while(fgets(buffer, BUFFERSIZE, stdin) != NULL)
  {
    //Step 3: append/write to file(s) and stdout
    fprintf(stdout, "%c", buffer[0]);
    for(i = start; i < argc; i++){
      fprintf(outs[i-start], "%c", buffer[0]);
    }
  }

  //Step 4: close files
  for(i = start; i < argc; i++){
    fclose(outs[i-start]);
  }

  //Step 5-return. Or is it profit?
  return 0;
}
