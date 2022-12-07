#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int different(char* arr) {
    if (arr[0] != arr[1]
            && arr[0] != arr[2]
            && arr[0] != arr[3]
            && arr[1] != arr[2]
            && arr[1] != arr[3]
            && arr[2] != arr[3])
        return 1;

    return 0;
}

int diff(char* arr, size_t size) {
    int alphabet[26] = { 0 };
    for (int i = 0; i < size; i++) {
        // printf("%c\n", *arr);
        alphabet[*arr++ - 97]++;
    }
    for (int i = 0; i < 26; i++) {
        printf("[%i]", alphabet[i]);
        if (alphabet[i] > 1) {
            printf("\n");
            return 0;
        }
    }
    printf("\n");
    return 1;
}


int main(void) {
    FILE* input = fopen("./day6_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;
    int chars = 0;

    const size_t MARKER_SIZE = 14;
    char* marker = calloc(MARKER_SIZE, sizeof(char));
    int count = 0;

    if (input) {
        chars = getline(&lineptr, &linelength, input);
        printf("%s", lineptr);

        for (; count < MARKER_SIZE; count++) {
            marker[count] = *lineptr++;
            printf("%c\n", marker[count]);
        }

        if (diff(marker, MARKER_SIZE)) {
           printf("Marker at pos %lu ...\n", MARKER_SIZE+1); 
        }

        for (; count < chars; count++) {
            marker[count % MARKER_SIZE] = *lineptr++;
            if (diff(marker, MARKER_SIZE)) {
                printf("Marker at pos %i: ", count + 1);
                for (int i = 0; i < MARKER_SIZE; i++) {
                    printf("%c ", marker[i]); 
                }
                printf("- %c\n", *lineptr);
                break;
            }
        }


        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    free(marker);
}
