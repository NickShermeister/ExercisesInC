/* Example from Head First C.

Downloaded from https://github.com/twcamper/head-first-c

Modified by Allen Downey.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>


void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void child_code(int i)
{
    // sleep(i);
    printf("\n\nHello from child %d.\n\n", i);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    char *search_phrase = argv[1];
    char var[255];
    int status;
    pid_t pid;


    for (int i=0; i<num_feeds; i++) {
      pid = fork();
      if(pid == -1){
        printf("Error creating child %i\n", i);
        exit(1);
      }
      if(pid != 0){
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
        if (res == -1) {
            error("Can't run script.");
        }
        child_code(i);
        exit(1);
      }

    }

    exit(0);
    return 0;
}
