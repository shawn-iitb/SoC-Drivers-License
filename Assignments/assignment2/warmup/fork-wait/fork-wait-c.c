#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*

First part:
simple

Second part:
here, the first child terminates one second after the second child, hence it is returned in the second wait();

Third part:
here, the first waitpid() has to wait for the first child, even though the second has already returned
even then, the second waitpid() / wait() still reaps the second child (even though it terminated a second back)

*/


int main(int argc, char *argv[]) {
    if (1) {
        // so that it can be collapsed while coding the other parts
        printf("\nFirst part:\n\n");

        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            printf("googoo gaga, my pid is %d\n", getpid());
            exit(0); // exiting so that the child is dead by the second part
        } else {
            int pid = wait(NULL);

            // These 2 printf statements should give the same pid
            printf("my child has come back!: %d\n", pid);
            printf("is it my child for sure?: %d\n", rc);
        }
    }

    if (1) {
        // so that it can be collapsed while coding the other parts
        printf("\nSecond part:\n\n");


        int rc1 = fork();
        if (rc1 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc1 == 0) {
            // child 1

            printf("googoo gaga, my pid is %d\n", getpid());
            sleep(1);
            exit(0);
        }

        int rc2 = fork();
        if (rc2 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc2 == 0) {
            // child 2

            printf("gaga googoo, my pid is %d\n", getpid());
            exit(0);
        }

        // parent

        int pid1 = wait(NULL);
        printf("my child has come back!: %d\n", pid1);
        int pid2 = wait(NULL);
        printf("my child has come back!: %d\n", pid2);
    }

    if (1) {
        printf("\nThird part:\n\n");


        int rc1 = fork();
        if (rc1 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc1 == 0) {
            // child 1

            printf("googoo gaga, my pid is %d\n", getpid());
            sleep(1);
            exit(0);
        }

        int rc2 = fork();
        if (rc2 < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc2 == 0) {
            // child 2

            printf("gaga googoo, my pid is %d\n", getpid());
            exit(0);
        }

        // parent

        int pid1 = waitpid(rc1, NULL, 0);
        printf("my child has come back!: %d\n", pid1);
        // int pid2 = waitpid(rc2, NULL, 0);
        int pid2 = wait(NULL);
        printf("my child has come back!: %d\n", pid2);
    }
}
