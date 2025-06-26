#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int sig) {
    printf("I will run... FOREVER!!\n");
    // signal(SIGINT, SIG_DFL);
}

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        signal(SIGINT, handler);
        int i = 1;
        printf("Counting with process %d!\n", getpid());
        while (1) {
            sleep(1);
            printf("%d + 1 = %d\n", i, i + 1);
            i++;
        }
    } else {
        sleep(2);

        printf("Parent: Attempting Interrupt\n");
        kill(rc, SIGINT);

        sleep(2);

        printf("Parent: Attempting Interrupt\n");
        kill(rc, SIGINT);

        sleep(2);

        printf("Parent: It appears there is no way to stop it... except murder!\n");
        sleep(2); // pause for dramatic effect
        kill(rc, SIGKILL);

        wait(NULL);

        printf("u snooze u lose!\n");
    }
}
