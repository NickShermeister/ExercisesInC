/* Fixed errors. Commented lines that weren't fixed (such as never_allocated, because it was unused).

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}

int read_element(int *array, int index) {
    int x = array[index];
    return x;
}

int main()
{
    // int never_allocated; //Unused, so commented.
    int *free_twice = malloc(sizeof (int));
    int *use_after_free = malloc(sizeof (int));
    int *never_free = malloc(sizeof (int));
    int array1[100];
    int *array2 = malloc(100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    read_element(array1, 1);
    read_element(array1, 99);

    // but it does bounds-check dynamic arrays
    read_element(array2, 1);
    read_element(array2, 99);

    // and it catches use after free

    *use_after_free = 17;
    free(use_after_free);

    // never_free is definitely lost
    *never_free = 17;

    // the following line would generate a warning
    // free(&never_allocated); //Unnecessary

    // but this one doesn't
    // free_anything(&never_allocated); //Unnecessary

    free(free_twice);
    free(array2);
    free(never_free);
    // free(free_twice); //Unnecessary.

    return 0;
}
