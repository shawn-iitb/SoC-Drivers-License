#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        // child
        printf("Helloo\n");
    } else {
        // parent
        sleep(1);


        printf("Byeee\n");
    }
}