#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int endswith(char* string, char* suffix){

  int strlength = strlen(string);
  int i;
  int sufflen = strlen(suffix);

  if(sufflen > strlength){
    // printf("Sufflen > strlen.\n");
    return 0;
  }
  int istart = strlength - sufflen;

  for (i = istart; i < strlength; i++){
    if(string[i] != suffix[i-(istart)]){
      // printf("i is: %i\n", i);
      // printf("string val is: %c\n", string[i]);
      // printf("suffix val is: %c\n", suffix[i-(istart)]);
      // printf("Suffix search val is: %i\n", i-(istart));
      return 0;
    }
  }
  // printf("Suffix contained in str!");
  return 1;

}

int main(){
  char string[] = "abcde";
  char suffix[] = "0";
  int retval = endswith(string, suffix);
  printf("Retval is: %i\n", retval);
}
