#include <stdio.h>
#include <stdlib.h>

int main() {
  char card_name[3];
  int count = 0;
  while(card_name[0] != 'X'){
    puts("Enter the card_name: ");
    scanf("%2s", card_name);
    int val = 0;
    switch(card_name[0]){
      case 'K':
      case 'Q':
      case 'J':
        val = 10;
        break;
      case 'A':
        val = 11;
      case 'X':
        continue;
      default:
        val = atoi(card_name);
        if((val < 2)||(val>10)){ //Changed to val < 2 from val < 1 because i want to card count correctly.
          puts("I don't understand that value!");
          continue;
        }
    }
    if ((val > 2) && (val < 7)) {
      count++;
    } else if (val == 10){
      count--;
    }
    printf("Current count: %i\n", count);
  }
  return 0;
}
