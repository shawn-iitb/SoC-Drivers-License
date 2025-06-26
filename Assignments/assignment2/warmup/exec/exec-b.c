#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Incorrect number of arguments\n");
        printf("Usage: ./exec-b command argument\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        execlp(argv[1], argv[1], argv[2], NULL);
    } else {
        wait(NULL);
        printf("Command successfully completed\n");
    }
}
