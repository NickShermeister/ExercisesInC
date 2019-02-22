/*
  File made for exercise 2 in software systems at Olin College of Engineering
  Nicholas Sherman
  02/06/2019

  Goal of program: allows the user to enter integers, one per line, until the user hits Control-D, which is the end-of-file (EOF) character.
*/

/*
TODO:
- Print error message if someone enters something that is too long into the input buffer.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS 3 //Maximum number of ints to be added.

#define BUFF_SIZE 256 //Maximum amount of buffer characters because I assume you're a reasonable person and this is a power of 2

/*
Converts a character into an integer using atoi.
Input: a charater array intIn of length 5 or less.
Output: the converted integer value.
*/
int intConversion(char* intIn){
  int value = atoi(intIn);
  if (value == 0){
    printf("Invalid number or 0. Please input another number.");
    value = 0;
  }
  else if (value < -2147483648){
    printf("That value's out of range. Please input another number.\n");
    value = 0;
  }
  else if (value > 2147483647){
    printf("That value's out of range. Please input another number.\n");
    value = 0;
  }
  return value;
}


int main() {
  int overflow;
  char tempchar;
  char number_to_be_added[BUFF_SIZE]; //Need 11 characters for 1 int, 1 character for end of array, and 1 character to know if people went over.
  int all_ints[MAX_INTS];
  int count;
  int charretreived;
  int val;
  count = 0;
  int exiting = 0;
  int sum;
  int i;
  int lenInput = 0;

  //Clears out the value of all_ints just in case
  for (i = 0; i < MAX_INTS; i++){
    all_ints[i] = 0;
  }

  while(exiting == 0){
    //Individual get each characters
    //Keep track of how many we have taken; if we have taken the max amount and the next line isn't EOF errors
    //Otherwise, send to other. cool.
    charretreived = 0;
    val = 0;
    puts("Enter the next integer: ");
    scanf("%11s", number_to_be_added);

    if (feof(stdin)){ //While there is no end of file in stdin
      printf("Your input was too long. Flushing; please retry with an integer.\n");
      fflush(stdin);
      fflush(stdout);
    }
    else {
      lenInput = strlen(number_to_be_added);
      if(*number_to_be_added == NULL){
        exiting = 1;
        printf("Exiting to sum numbers now.");
        break;
      }
      else if (lenInput > 11){
        printf("You have entered a string that is too long. Try again.\n");
      }
      else if (count == MAX_INTS){
        printf("You've entered the maximum number of ints, please type control-d!\n");
        // exiting = 1;
        // break;
      }
      else {
        val = intConversion(number_to_be_added);
        all_ints[count] = val;
        count++;
      }
    }


  }

  sum = 0;
  for (i = 0; i < count; i++){
    sum += all_ints[i];
  }

printf("The total sum is: %d\n", sum);

  return 0;
}
