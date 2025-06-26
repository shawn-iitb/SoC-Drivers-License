#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        sleep(10);
    } else {
        sleep(1);
        kill(rc, SIGINT);
        wait(NULL);

        printf("u snooze u lose!\n");
    }
}
