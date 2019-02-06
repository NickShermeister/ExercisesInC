/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

/*
Compile and run aspace.c in this directory.

Read the code. You might want to read about malloc here.
-done

Based on the output, draw a sketch of the virtual address space (see page 80 of HFC). Show the relative locations of the stack, heap, globals, constants, and code.
-see address_space.png

Add a second call to malloc and check whether the heap on your system grows up (toward larger addresses).
-see address_space.png

Add a function that prints the address of a local variable, and check whether the stack grows down.
-see below
Choose a random number between 1 and 32, and allocate two chunks with that size.
How much space is there between them? Hint: Google knows how to subtract hexadecimal numbers.
see below.
*/


/*
5:
  Function which establishes whether the stack is growing up or down.
  Inputs:
  int*varIn: The first variable defined in the stack.

  Returns a boolean. 0 if down, 1 if up.
*/
int stackGrowth (int varIn) {
  printf("The input variable varIn points to %p\n", &varIn);
  int varDef = 10;
  printf("The variable defined in-function points to %p\n", &varDef);
  if(&varIn < &varDef){ //If the 1st location is lower in memory than the second
    printf("The stack is growing up.\n");
    return 1;
  }
  else {
    printf("The stack is growing down.\n");
    return 0;
  }
}

/*
#6:
Random numbers chosen: 20, 1, 31
20 - 32
1 - 32
31 - 48???? (shouldn't this be 32???)
30 - 48
24 - 32
27 - 48
25 -48

Why is this happening iin this pattern? That doesn't make sense... 12 in malloc = 16 bytes?
*/
void sizeDiff(){
  void *temp1 = malloc(25);
  void *temp2 = malloc(25);

  printf ("temp1 points to %p\n", temp1);
  printf ("temp2  points to %p\n", temp2);
  int diff = temp2 - temp1; //We know the stack grows up on the test computer.

  printf("The difference between temp1 and temp2 is: %d", diff);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *p2 = malloc(128);
    char *s = "Hello, World";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    /*
    Output from run including var2:
    Address of main is 0x4005d6
    Address of var1 is 0x60104c
    Address of var2 is 0x7ffd7bdf149c
    p points to 0x1a70010
    p2 points to 0x1a700a0
    s points to 0x400744

    */
    int temp = stackGrowth(var2);
    printf ("p points to %p\n", p);
    printf ("p2 points to %p\n", p2);
    printf ("s points to %p\n", s);

    sizeDiff();

    return 0;
}
