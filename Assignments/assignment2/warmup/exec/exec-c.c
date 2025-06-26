#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*

The "after" print statement is only executed when the exec fails in some way

*/

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("before\n");
        execlp("ls", "ls"); // doesn't execute ls and prints "after"
        // execlp("ls", "ls", NULL); // executes ls and doesn't print "after"
        printf("after\n");
    }
    wait(NULL);
}
