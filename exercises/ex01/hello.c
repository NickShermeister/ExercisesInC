/*
A basic funciton, created for Software Systems spring 2019 at Olin College.
Author: Nicholas Sherman
Date: 1/27/2019
*/
/*
Q1: Compile and look at the assembly language output (see this section of Think OS. Can you find the code that corresponds to this line?
A1:subq	$16, %rsp
movl	$5, -4(%rbp)
(lines 16 & 17)
Q2: What happens if you turn on optimization using the flag -O2?
A2: The code seems to be split up into multiple (functions? simultaneous calls?) dictated by the .###. It also just puts the values directly into the assembly code.
Q3: Modify the printf statement to print x, then compile it with and without optimization. What effect does it have when you print x?
A3:Once more, the code is split up into smaller functions, presumably so they can run simultaneously.
Q4: Compile with and without optimization. What happens to x and y?
The parallelization is still here. The what y equals is put directly into the print statement (instead of calculating y separately then using the value.)
What conclusions can you draw about how optimization works?
Optimization is useful for parallelization and for combining assignments and reusage of variables into smaller spaces.
There is also compilation prediction that allows for shortened code by precomputing x because it isn't used.


*/
#include <stdio.h>

int main() {
  int x = 5;
   int y = x + 1;
    // printf("Hello, World!\n");
    // printf("x is: %i", x);
    printf("y is: %i", y);

    return 0;
}
