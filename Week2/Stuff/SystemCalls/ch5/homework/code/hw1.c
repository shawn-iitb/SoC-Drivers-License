#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        // child
        char p[] = "Child";

        printf("%s x: %d (at %p)\n", p, x, &x);

        printf("%s sleeping\n", p);
        sleep(1);

        printf("%s x: %d (at %p)\n", p, x, &x);
        printf("%s changing x to 1\n", p);
        x = 1;
        printf("%s x: %d (at %p)\n", p, x, &x);

        sleep(2);
        printf("%s x: %d (at %p)\n", p, x, &x);
    } else {
        // parent
        char p[] = "Parent";

        printf("%s x: %d (at %p)\n", p, x, &x);

        printf("%s sleeping\n", p);
        sleep(2);
        x = *(&x);
        printf("%s x: %d (at %p)\n", p, x, &x);
        printf("%s changing x to 2\n", p);
        x = 2;
        printf("%s x: %d (at %p)\n", p, x, &x);

        wait(NULL);
    }
}