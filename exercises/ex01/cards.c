/*
A basic card counting funciton, created for Software Systems spring 2019 at Olin College.
Author: Nicholas Sherman
Date: 1/27/2019
*/

#include <stdio.h>
#include <stdlib.h>

/*
  Function that takes in the character that the user inputted and returns the corresponding value as an integer.

  card_name: character string of length 4 which is the character array the user input.
*/
int card_switch(char card_name[3]){
  int value;
  value = 0;
  switch(card_name[0]){
    case 'K':
    case 'Q':
    case 'J':
      value = 10;
      break;
    case 'A':
      value = 11;
      break;
    case 'X':
      value = -1;
      break;
    default:
      value = atoi(card_name);
      if((value < 2)||(value >10)){
        /*Changed to val < 2 from val < 1 because i want to card count correctly.
        */
        puts("I don't understand that value!");
      }
  }
  return value;
}

/*
  Function that takes in the value of the card most recently played and updates the counter.
  Returns updated counter.

  curr_count: int of the current card count.
  val: int of the value of the input card.
*/
int count_difference(int curr_count, int val){
  if ((val > 2) && (val < 7)) {
    curr_count++;
  } else if (val == 10){
    curr_count--;
  }
  return curr_count;
}
/*
  Main function that prompts the reader for a card.

  Takes user input, dictated as function progresses.

  Returns 0.
*/
int main() {
  char card_name[3];
  int count;
  int val;
  count = 0;

  while(card_name[0] != 'X'){
    puts("Enter the card_name: ");
    scanf("%2s", card_name);

    val = 0;
    val = card_switch(card_name);
    if (val == -1){
      continue;
    }
    count = count_difference(count, val);

    printf("Current count: %i\n", count);
  }
  return 0;
}
