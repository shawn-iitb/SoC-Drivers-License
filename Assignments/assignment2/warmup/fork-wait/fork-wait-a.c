#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*

at every iteration, each process splits into 2: a child and parent
=> the total number of processes = 2^N
one process would be the parent every time (the base process)
=> total number of child processes = 2^N - 1

*/

int main(int argc, char *argv[]) {
    int N = 1;
    if (argc == 2) {
        N = atoi(argv[1]);
    }

    for (int i = 0; i < N; i++) {
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            printf("googoo gaga, my pid is %d\n", getpid());
        } else {
            wait(NULL);
        }
    }
}
