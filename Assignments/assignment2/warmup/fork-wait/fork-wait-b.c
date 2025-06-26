#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*

in the first part of the question (when wait(NULL) is put after the prinf()),

the book says the order is non deterministic

but atleast for my system specifically, it always printed:
I'm a parent
I am a child.

when modified to print without the \n (either only the parent or both), it always printed the child first
very interesting
(i ran into this by accident coz i forgot to put \n in the printf)

*/


int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("I am a child.\n");
    } else {
        wait(NULL);
        printf("I'm a parent\n");
    }
}