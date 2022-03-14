#include <stdio.h>
#include <stdlib.h>

// needs to be freed
char* get_input() {
    char* buffer = calloc(10000, sizeof(char));
    char c;
    char* p = buffer;
    while ((c = getchar()) != EOF) {
        *p = c;
        p++;
    }
    return buffer;
}

int task_1(char* c) {
    int result, prev, curr = 0;
    //printf("prev, curr, result\n");
    prev = atoi(c);
    while (*c != '\0') {
        while (*c != '\n') {
            c++;
        }
        curr = atoi(++c);
        if (curr > prev) result++;
        //printf("%4i, %4i, %6i\n", prev, curr, result);
        prev = curr;
    }
    //printf("\n");
    return result;
}

int task_2(char* c) {
    int a[3] = {0,0,0};
    int b[3] = {0,0,0};
    int result = 0;
    char* p = c;

    while (*c != '\0') {
        a[0] = atoi(c);
        while (*c != '\n') {
            c++;
        }
        a[1] = b[0] = atoi(++c);
        p = c; // p is starting point for next round
        while (*c != '\n') {
            c++;
        }
        a[2] = b[1] = atoi(++c);
        while (*c != '\n') {
            c++;
        }
        b[2] = atoi(++c);
        if ( (b[0]+b[1]+b[2]) > (a[0]+a[1]+a[2]) ) result++;
        c = p; // set c to next "starting point"
    }
    return result;
}

int main(void) {
    char* INPUT = get_input();
    printf("Task1 result is %i.\n", task_1(INPUT));
    printf("Task2 result is %i.\n", task_2(INPUT));
    free(INPUT);
}
