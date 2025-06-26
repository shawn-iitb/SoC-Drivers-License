#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc;

    // execvp
    if (1) {
        rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            printf("execvp:\n");

            char *args[] = {"ls", "-l", NULL};
            execvp(args[0], args);
        }
        wait(NULL);
        printf("\n");
    }

    // execv
    if (1) {
        rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            printf("execv:\n");

            // doesnt have PATH variables

            char *args[] = {"/usr/bin/ls", "-l", NULL};
            execv(args[0], args);
        }
        wait(NULL);
        printf("\n");
    }

    // execve
    if (1) {
        rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            printf("execve:\n");

            // can give environment variables

            char *args[] = {"/usr/bin/bash", "-c", "$custom", NULL};

            char *envs[] = {"custom=ls -l", NULL};
            execve(args[0], args, envs); // PATH is not used, which is why /usr/bin/bash is needed
        }
        wait(NULL);
        printf("\n");
    }

    // execvpe
    if (1) {
        rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            printf("execvpe:\n");

            // can give environment variables and uses PATH

            char *args[] = {"bash", "-c", "$custom", NULL};

            char *envs[] = {"custom=ls -l", NULL};
            execvpe(args[0], args, envs);
        }
        wait(NULL);
        printf("\n");
    }

    // execlp
    if (1) {
        rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            printf("execlp:\n");

            execlp("ls", "ls", "-l", NULL);
        }
        wait(NULL);
        printf("\n");
    }
}
