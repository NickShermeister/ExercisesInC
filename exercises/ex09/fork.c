/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

int testGlobal = 1;

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;



    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    int testBeforeForkLocal = 1;

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        int * testHeap = malloc(sizeof(int));
        *testHeap = 1;
        int testAfterForkLocal = 1;


        //This prints out where each thing a process references is.
        printf("Location of a global variable before editing for process %d: %d\t\t value: %d\n", i, &testGlobal, testGlobal);
        printf("Location of a local variable before editing created before fork for process %d: %d\t\t value: %d\n", i, &testBeforeForkLocal, testBeforeForkLocal);
        printf("Location of a local variable before editing created after fork for process %d: %d\t\t value: %d\n", i, &testAfterForkLocal, testAfterForkLocal);
        printf("Location of a heap variable before editing for process %d: %d\t\t value: %d\n", i, testHeap, *testHeap);

        //Change the values to see what happens, using the child number to try to significantly differentiate the results.
        testAfterForkLocal = i+10;
        testBeforeForkLocal = i+10;
        *testHeap = i+10;
        testGlobal = i+10;

        //Print the new results
        printf("Location of a global variable after editing for process %d: %d\t\t value: %d\n", i, &testGlobal, testGlobal);
        printf("Location of a local variable after editing created before fork for process %d: %d\t\t value: %d\n", i, &testBeforeForkLocal, testBeforeForkLocal);
        printf("Location of a local variable after editing created after fork for process %d: %d\t\t value: %d\n", i, &testAfterForkLocal, testAfterForkLocal);
        printf("Location of a heap variable after editing for process %d: %d\t\t value: %d\n", i, testHeap, *testHeap);

        //My results are saying that the locations are the same for all processes despite the values being able to be manipulated separately.
        //I believe that this is due to the computer mapping the actual locations of the memory to different locations due to some sort of (hashing?) function as to where to physically store the memory.


        free(testHeap);

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
