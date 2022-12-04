#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

int parse(char* line, int** bounds) {
    int* tmp = *bounds;
    *tmp++ = atoi(strtok(line, "-,"));
    *tmp++ = atoi(strtok(NULL, "-,"));
    *tmp++ = atoi(strtok(NULL, "-,"));
    *tmp = atoi(strtok(NULL, "-,"));
    return 0;
}

int overlaps(int** arr) {
    int* tmp = *arr;

    // regular overlap
    if (tmp[1] < tmp[2])
        return 0;

    // reverse overlap
    if (tmp[3] < tmp[0])
        return 0;

    return 1;
}

int main(void) {
    FILE* input = fopen("./day4_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;
    int chars = 0;

    int* bounds = malloc(4 * sizeof(int));
    int count = 0;
    int countoverlaps = 0;

    if (input) {
        for (;;) {
            chars = getline(&lineptr, &linelength, input);

            if (chars < 0) {
                break;
            }

            printf("%s", lineptr);
            parse(lineptr, &bounds);
            printf("[%d, %d, %d, %d]\n", bounds[0], bounds[1], bounds[2], bounds[3]);

            // the first one contains the second
            if (bounds[2] - bounds[0] >= 0 && bounds[1] - bounds[3] >= 0) {
                printf("the first one contains the second\n");
                count++;
            } else if (bounds[0] - bounds[2] >= 0 && bounds[3] - bounds[1] >= 0) {
                printf("the second one contains the first\n");
                count++;
            }

            if (overlaps(&bounds)) {
                countoverlaps++;
            }

        }
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    printf("Count: %i\n", count);
    printf("Counted overlaps: %i\n", countoverlaps);
}
