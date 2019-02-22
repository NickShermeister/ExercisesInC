/*
  File made for exercise 2 in software systems at Olin College of Engineering
  Nicholas Sherman
  02/06/2019

  Goal of program: allows the user to enter integers, one per line, until the user hits Control-D, which is the end-of-file (EOF) character.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS 20 //Maximum number of ints to be added.
#define BUFF_SIZE 256 //Maximum amount of buffer characters because I assume you're a reasonable person and this is a power of 2

/*
Converts a character into an integer using atoi.
Input: a charater array intIn of length 5 or less.
Output: the converted integer value.
*/
int intConversion(char* intIn){
  int value = atoi(intIn); //Use atoi to get the integer value
  //We assume that your input is nonzero, and atoi returning 0 means that it was unreadable.
  if (value == 0){
    printf("Invalid number or 0. Please input another number.");
    value = 0;
  }
  //Make sure the value is within the bounds of an integer.
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

/*
Sums and prints the array of integers.
Inputs: allInts[] - List of all integers passed in
count - the number of integers that are being added.
*/
void calcAndPrint(int allInts[], int count){
  int sum = 0;
  int i;
  for (i = 0; i < count; i++){
    // printf("%i\n", allInts[i]);
    sum += allInts[i];
  }

  printf("The total sum is: %d\n", sum);
}

/*
Main function for program
*/
int main() {
  char number_to_be_added[BUFF_SIZE];
  int all_ints[MAX_INTS];
  int count;
  int val;
  count = 0;
  int exiting = 0;
  int i;
  int lenInput = 0;

  //Clears out the value of all_ints just in case
  for (i = 0; i < MAX_INTS; i++){
    all_ints[i] = 0;
  }
  printf("Welcome to Nick Sherman's lovely adder! You can add up to %i numbers.\n", MAX_INTS);

  while(exiting == 0){

    //Prompt user for input
    val = 0;
    puts("Enter the next non-zero integer: ");
    for (i = 0; i < MAX_INTS; i++){
      number_to_be_added[i] = 0;
    }
    scanf("%256s", number_to_be_added);
    lenInput = strlen(number_to_be_added);

    //React appropriately to input
    if(number_to_be_added[0] == NULL){
      exiting = 1;
      printf("Exiting to sum numbers now.");
      break;
    }
    else if (lenInput > 11){ //Need 11 characters for 1 int
      printf("You have entered a string that is too long. Try again.\n");
    }
    else if (count == MAX_INTS){
      printf("You've entered the maximum number of ints, please type control-d!\n");
    }
    else {
      val = intConversion(number_to_be_added);
      if (val != 0){
        all_ints[count] = val;
        count++;
      }
    }
  }

  calcAndPrint(all_ints, count);
  return 0;
}
