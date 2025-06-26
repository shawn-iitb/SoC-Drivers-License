#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        // child
        int pid = getpid();

        wait(NULL);
        printf("%d: spawned\n", pid);
        sleep(1);
        printf("%d: died\n", pid);
    } else {
        rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork 2 failed\n");
        } else if (rc == 0) {
            // child 2
            int pid = getpid();

            printf("%d: spawned\n", pid);
            sleep(2);
            printf("%d: died\n", pid);
        } else {
            // parent

            wait(NULL);
            printf("BYEEEEEEEEEEEE 1\n");

            waitpid(rc, NULL, 0);
            printf("BYEEEEEEEEEEE 2\n");
        }
    }
}