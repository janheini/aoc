#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE* input = fopen("./day1_input.txt", "r");

    char* lineptr = NULL;
    size_t linelength = 0;

    int curr_elf = 1;
    int curr = 0;
    int max[3] = {0, 0, 0};

    if (input) {
        while (getline(&lineptr, &linelength, input) != -1) {
            printf("%s", lineptr);
            curr += atoi(lineptr);
            if (strcmp(lineptr, "\n") == 0) {

                printf("curr = %i\n", curr);
                if (curr > max[0]) {
                    max[2] = max[1];
                    max[1] = max[0];
                    max[0] = curr;
                } else if (curr > max[1]) {
                    max[2] = max[1];
                    max[1] = curr;
                } else if (curr > max[2]) {
                    max[2] = curr;
                }

                printf("next elf\n");
                curr_elf++;
                curr = 0;
            }
        }
    } else {
        perror("fopen");
    }
    fclose(input);

    printf("max: [%i][%i][%i]\n", max[0], max[1], max[2]);
    printf("sum: %i\n", max[0] + max[1] + max[2]);

    return 0;
}
