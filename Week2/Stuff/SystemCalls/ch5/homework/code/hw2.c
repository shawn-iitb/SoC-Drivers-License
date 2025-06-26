#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    FILE *f;

    f = fopen("text.txt", "r");

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        // child
        char p[] = "Child";

        char data[100];

        printf("%s File content\n\n", p);
        while (fgets(data, 50, f)
               != NULL) {
            // Print the data
            printf("%s", data);
               }
        printf("\n");
    } else {
        // parent
        char p[] = "Parent";

        // sleep(1);

        char data[100];

        printf("%s File content\n\n", p);
        while (fgets(data, 50, f)
               != NULL) {
            // Print the data
            printf("%s", data);
        }
        printf("\n");


        wait(NULL);
    }
}
