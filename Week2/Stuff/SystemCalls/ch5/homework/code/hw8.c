#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc1 = fork();

    int p[2];
    if (pipe(p) == -1) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    if (rc1 < 0) {
        fprintf(stderr, "fork 1 failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // child 1
        printf("child 1 init\n");
        sleep(1);

        close(p[0]);
        char text[] = "HIII\n";
        write(p[1], text, strlen(text) + 1);
        close(p[1]);
        printf("child 1 exit\n");


    } else {
        int rc2 = fork();
        if (rc2 < 0) {
            fprintf(stderr, "fork 2 failed\n");
            exit(1);
        } else if (rc2 == 0) {
            // child 2
            printf("child 2 init\n");


            char text[50];
            close(p[1]);
            read(p[0], text, 50);
            printf("got this: %s\n", text);
            close(p[0]);

            printf("child 2 exit\n");


        } else {
            // parent

            waitpid(rc1, NULL, 0);
            waitpid(rc2, NULL, 0);

        }
    }
}