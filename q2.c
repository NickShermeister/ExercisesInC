#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strplit(char* string, char sep, char* first, char* second){
  int i;
  int strlength = strlen(string);
  int loc = -1;
  // printf("%c\n", sep);

  for(i = 0; i < strlength; i++){
    // printf("%c\n", string[i]);
    if (string[i] == sep){
      loc = i;
      break;
    }
  }

  for (i = 0; i < loc; i++){
    first[i] = string[i];
  }

  for (i = loc+1; i < strlength; i++){
    second[i-loc-1] = string[i];
  }

  return;
}

int main() {
  char* string = "abcdecf";
  char sep = 'c';
  char* first = malloc(10*sizeof(char));
  char* second = malloc(10*sizeof(char));
  printf("%s\n", first);
  printf("%s\n", second);
  strplit(string, sep, first, second);
  printf("%s\n", first);
  printf("%s\n", second);

  return 0;
}
