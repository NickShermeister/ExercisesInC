/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

/*
Read stack.c, which should be in this directory. What is it intended to do? What would the output be if the program worked as expected?
stack.c is intended to create an array of size SIZE (which is a constant currently set to 5) of ints. These values are then set to 42. As it stands, array bar does nothing except create an array of size SIZE valued 0 to size-1. It then is supposed to print out the first generated array, which was passed back to the main function.
If it worked as expected, it should print 42 five times.


Compile it. Do you get a warning? What does it mean?
-I got a warning that stated:
warning: function returns address of local variable [-Wreturn-local-addr]
This means that the variable which we are trying to pass back and forth is being deleted from the stack as it is a local variable and therefore we will lose all references to it, which is why it shouldn't be returned.

Run it. What happens? You might get a segmentation fault, or you might get some strange output. Can you explain it? You might find it helpful to draw a stack diagram.
After running it, I get two printed addresses of the same value (which was due to foo and bar taking up the same amount of space, causing array to be located at the same disk space in both foo and bar, resulting in the same location being printed in each function)
and then a segmentation fault. This occurs because the pointer that was array was still passed to the main function, but the area it pointed to we were no longer able to look at.
We ended up with a segmentation fault due to this fact.


Comment out the print statements in foo() and bar() and run it again. What happens now?
With -Wall on we get some more errors! Specifically, we're we're still warned about returning array in foo but in bar we're warned that array is set but not used for some reason!
We also still get a segmentation fault when the main function tries to read at the old location of array.

Add comments to the code to explain these experiments and the results, then check the code in to the repo.
-done

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
Function that is supposed to create an array of size SIZE (constant, 5) and then set all of its values to 42.
Currently, the function creates array as a local variable and therefore it is lost.
returns int*: the location of where array should be.
*/
int *foo() {
  //Declaration of local variables
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    //Looped assignment of array variable values
    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    //Return the pointer to the array that is to be deleted.
    return array;
}
/*
Function that locally creates an array of size SIZE (constant, 5) and then instantiates the diferent locations' values to the locaiton (e.g. the 0th slot is 0).
Currently works, but doesn't do anything.
*/
void bar() {
  //Declaration of variables
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    //Instanitation loop
    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

/*
Main function which is supposed to take an array made in foo and print out the values.

In actuality, foo makes a local variable not a global variable and therefore the variable is inacessible to the main function.
*/
int main()
{
    //Declar variables
    int i;
    //Make the critical mistake of not having a global array.
    int *array = foo();
    //Be confused as to why this function exists. The devs are uncertain as well.
    bar();

    //Recursively print the array if we have access to it. Otherwise, have a segmentation fault.
    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
