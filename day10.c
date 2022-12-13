#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(int x, int cycle) {
    static int signalstrenght[6] = { 0 };
    static int sum = -1;
    
    if (abs(((cycle-1) % 40) - x) < 2) {
        // printf("%i: (%i) %s\n", cycle, x, "\x1b[31m#\x1b[0m");
        printf("%s", "\x1b[97m#\x1b[0m");
    } else {
        // printf("%i: (%i) %s\n", cycle, x, "\x1b[30m#\x1b[0m");
        printf("%s", "\x1b[30m#\x1b[0m");
    }
    // printf("Cycle %i, x: %i, %i\n", cycle, x, (cycle % 40)-x);

    if (cycle % 40 == 0) {
        printf("\n");
    }

    switch (cycle) {
        case 20:
            signalstrenght[0] = cycle*x;
            // printf("Signalstrenght at %i: %i\n", cycle, cycle*x);
            break;
        case 60:
            signalstrenght[1] = cycle*x;
            // printf("Signalstrenght at %i: %i\n", cycle, cycle*x);
            break;
        case 100:
            signalstrenght[2] = cycle*x;
            // printf("Signalstrenght at %i: %i\n", cycle, cycle*x);
            break;
        case 140:
            signalstrenght[3] = cycle*x;
            // printf("Signalstrenght at %i: %i\n", cycle, cycle*x);
            break;
        case 180:
            signalstrenght[4] = cycle*x;
            // printf("Signalstrenght at %i: %i\n", cycle, cycle*x);
            break;
        case 220:
            signalstrenght[5] = cycle*x;
            // printf("Signalstrenght at %i: %i\n", cycle, cycle*x);
            sum = 0;
            for (int i = 0; i < 6; i++) {
                //printf("[%i]", signalstrenght[i]);
                sum += signalstrenght[i];
            }
            //printf(" Sum: %i\n", sum);
            break;
    }
    return sum;
}

int addx(int* x, int* cycle, int add) {
    // printf("adding %i\n", add);
    int signalstrenght_sum = 0;
    signalstrenght_sum = check(*x, *cycle);
    (*cycle)++;
    signalstrenght_sum = check(*x, *cycle);
    (*cycle)++;
    *x += add;
    return signalstrenght_sum;
}

int main(void) {
    FILE* input = fopen("./day10_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;

    int x = 1;
    int cycle = 1;
    int signalstrenght_sum = 0;

    if (input) {
        while (getline(&lineptr, &linelength, input) > 0) {
            // printf("%s", lineptr);
            char* tok = lineptr;
            if (strcmp(strtok(lineptr, " \n"), "noop") == 0) {
                signalstrenght_sum = check(x, cycle);
                cycle++;
            } else {
                int add = atoi(strtok(NULL, "\n"));
                signalstrenght_sum = addx(&x, &cycle, add);
            }
        }
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }
    printf("Signalstrenght sum: %i\n", signalstrenght_sum);
    free(lineptr);
}
