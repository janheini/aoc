#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 99

int is_visible(int forest[SIZE][SIZE], int y, int x) {
    if (x == 0 || y == 0 || x == SIZE-1 || y == SIZE-1 ) {
        return 1;
    }
    int vis = 0;

    // left
    for (int i = x-1; i >= 0; i--) {
        if (forest[y][i] >= forest[y][x]) {
            break;
        }
        if (i == 0) {
            vis = 1;
        }
    }

    // right
    for (int i = x+1; i < SIZE; i++) {
        if (forest[y][i] >= forest[y][x]) {
            break;
        }
        if (i == SIZE-1) {
            vis = 1;
        }
    }

    // top
    for (int i = y-1; i >= 0; i--) {
        if (forest[i][x] >= forest[y][x]) {
            break;
        }
        if (i == 0) {
            vis = 1;
        }
    }

    // bottom
    for (int i = y+1; i < SIZE; i++) {
        if (forest[i][x] >= forest[y][x]) {
            break;
        }
        if (i == SIZE-1) {
            vis = 1;
        }
    }

    return vis;
}

int scenic_score(int forest[SIZE][SIZE], int y, int x) {
    int north = 0;
    for (int i = y-1; i >= 0; i--) {
        north++;
        if (forest[i][x] >= forest[y][x])
            break;
    }

    int south = 0;
    for (int i = y+1; i < SIZE; i++) {
        south++;
        if (forest[i][x] >= forest[y][x])
            break;
    }
    
    int east = 0;
    for (int i = x-1; i >= 0; i--) {
        east++;
        if (forest[y][i] >= forest[y][x])
            break;
    }

    int west = 0;
    for (int i = x+1; i < SIZE; i++) {
        west++;
        if (forest[y][i] >= forest[y][x])
            break;
    }

    return north * south * east * west;
}

int main(void) {
    FILE* input = fopen("./day8_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;
    int chars = 0;

    int forest[SIZE][SIZE] = { 0 };

    if (input) {
        for (int i = 0; i < SIZE; i++) {
            getline(&lineptr, &linelength, input);
            for (int j = 0; j < SIZE; j++) {
                forest[i][j] = lineptr[j] - 48; // char to int with ascii
                                                // offset
            }
        }
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    int visible_trees = 0;
    int highest_scenic = 0;
    int score = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            score = scenic_score(forest, i, j);
            if (score > highest_scenic) {
                printf("\x1b[31m%i\x1b[0m", forest[i][j]);
                highest_scenic = score;
            } else if (is_visible(forest, i, j)) {
                printf("\x1b[92m%i\x1b[0m", forest[i][j]);
            } else {
                printf("\x1b[30m%i\x1b[0m", forest[i][j]);
            }

            if (is_visible(forest, i, j)) {
                visible_trees++;
            }

        }
        printf("\n");
    }

    printf("Visible trees: %i\n", visible_trees);
    printf("Highest scenic score: %i\n", highest_scenic);

    free(lineptr);
}
