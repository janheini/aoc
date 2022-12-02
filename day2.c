#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct score {
    int day1;
    int day2;
};

struct score cscore(char mine, char theirs) {
    // A = X = rock = 1
    // B = Y = paper = 2
    // C = Z = scissors = 3
    struct score s = { 0, 0 };
    switch (mine) {
        case 'X': // lose
            s.day1 += 1;
            switch (theirs) {
                case 'A':
                    s.day1 += 3;
                    s.day2 += 3;
                    break;
                case 'B': 
                    s.day2 += 1;
                    break;
                case 'C':
                    s.day1 += 6;
                    s.day2 += 2;
                    break;
                default: printf("OH NO!\n"); exit(EXIT_FAILURE);
            }
            break;
        case 'Y': // draw
            s.day1 += 2;
            s.day2 += 3;
            switch (theirs) {
                case 'A':
                    s.day1 += 6;
                    s.day2 += 1;
                    break;
                case 'B':
                    s.day1 += 3;
                    s.day2 += 2;
                    break;
                case 'C': 
                    s.day2 += 3;
                    break;
                default: printf("OH NO!\n"); exit(EXIT_FAILURE);
            }
            break;
        case 'Z': // win
            s.day1 += 3;
            s.day2 += 6;
            switch (theirs) {
                case 'A':
                    s.day2 += 2;
                    break;
                case 'B':
                    s.day1 += 6;
                    s.day2 += 3;
                    break;
                case 'C':
                    s.day1 += 3;
                    s.day2 += 1;
                    break;
                default: printf("OH NO!\n"); exit(EXIT_FAILURE);

            }
            break;
        default: printf("OH NO!\n"); exit(EXIT_FAILURE);
    }
    printf("s: [%i, %i]\n", s.day1, s.day2);
    return s;
}

int main(void) {
    FILE* input = fopen("./day2_input.txt", "r");

    char* lineptr = NULL;
    size_t linelength = 0;

    struct score s = { 0, 0 };
    int sc[2] = { 0 };

    if (input) {
        while (getline(&lineptr, &linelength, input) != -1) {
            printf("%s", lineptr);
            s = cscore(lineptr[2], lineptr[0]);
            sc[0] += s.day1;
            sc[1] += s.day2;
        }
    } else {
        perror("fopen");
    }

    printf("Score: [%i, %i]\n", sc[0], sc[1]);

    fclose(input);
    return 0;
}

