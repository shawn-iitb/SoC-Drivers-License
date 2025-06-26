#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    // close(STDOUT_FILENO);
    // printf("testing123\n");

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        // child

        close(STDOUT_FILENO);
        printf("child\n");
    } else {
        // parent

        printf("parent\n");
        wait(NULL);
    }
}