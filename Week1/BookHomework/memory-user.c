#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    int mb = atoi(argv[1]);
    if (mb > 100 || mb <= 0) {
        return 0;
    }

    // int ints = mb * 1024 / sizeof(int) * 1024;
    //
    // printf("%d ints\n", ints);
    //
    //
    // printf("hi\n");
    // int big[ints / 2];
    // printf("bye\n");
    // while (1) {
    //     for (int i = 0; i < ints; i++) {
    //         big[i] = big[(i - 1) % ints];
    //     }
    // }

    int b = mb * 1024 * 1024;

    int *a = (int *) malloc(b);

    printf("%d bytes alloacted\n", b);

    while (1) {
        for (int i = 0; i < b / sizeof(int); i++) {
            a[i] = i;
        }
    }

    return 0;
}
