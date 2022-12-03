#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

int main(void) {
    FILE* input = fopen("./day3_input.txt", "r");

    char* lineptr = calloc(BUFFER_SIZE, sizeof(char));
    size_t linelength = BUFFER_SIZE;
    int chars = 0;

    char* firstc = malloc(BUFFER_SIZE);
    char* secondc = malloc(BUFFER_SIZE);

    char* group[3] = { NULL };
    group[0] = calloc(BUFFER_SIZE, sizeof(char));
    group[1] = calloc(BUFFER_SIZE, sizeof(char));
    group[2] = calloc(BUFFER_SIZE, sizeof(char));

    int linecount = 0;

    int sum = 0;
    int labelsum = 0;

    if (input) {
        do {
            chars = getline(&lineptr, &linelength, input);
            if (chars < 2) {
                break;
            }
            printf("%d: %s", --chars, lineptr);
            strncpy(firstc, lineptr, chars/2);
            strncpy(secondc, lineptr + chars/2, chars/2);

            firstc[chars/2] = '\0';
            secondc[chars/2] = '\0';

            printf("%s | %s\n", firstc, secondc);

            for (int i = 0; i < 26; i++) {
                // uppercase
                // printf("Checking: %c\n", i + 65);
                if (strchr(firstc, i + 65) && strchr(secondc, i + 65)) {
                    printf("Both: %c, score of %i\n", i+65, i+27);
                    sum += i+27;
                }
                // lowercase
                // printf("Checking: %c\n", i + 97);
                if (strchr(firstc, i + 97) && strchr(secondc, i + 97)) {
                    printf("Both: %c, score of %i\n", i+97, i+1);
                    sum += i+1;
                }


            }

            char* curr = group[linecount % 3];
            strcpy(group[linecount % 3], lineptr);
            curr[chars] = '\0';

            if (linecount % 3 == 2) {
                printf("\nGroup %i:\n %s\n %s\n %s\n", linecount/3, group[0], group[1], group[2]);

                for (int i = 0; i < 26; i++) {
                    if (strchr(group[0], i+65) && strchr(group[1], i+65) && strchr(group[2], i+65)) {
                        printf("Label of group %i: %c, score of %i\n\n", linecount/3, i+65, i+27);
                        labelsum += i+27;
                    }
                    if (strchr(group[0], i+97) && strchr(group[1], i+97) && strchr(group[2], i+97)) {
                        printf("Label of group %i: %c, score of %i\n\n", linecount/3, i+97, i+1);
                        labelsum += i+1;
                    }
                }
            }
            linecount++;

        } while (chars > 0);
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    free(lineptr);

    free(firstc);
    free(secondc);

    free(group[1]);
    free(group[0]);
    free(group[2]);

    fclose(input);
    printf("Sum: %i\n", sum);
    printf("Labelsum: %i\n", labelsum);
    return 0;
}

