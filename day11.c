#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MONKEYS 8
#define ROUNDS 10000

typedef struct s_monkey {
    int inspectcount;
    int itemcount;
    int64_t items[64];
    int con;
    void (*operation)(int64_t* old, int con);
    int test;
    int true_dest;
    int false_dest;
} monkey;

void add(int64_t* old, int con) {
    *old += con;
}
void mult(int64_t* old, int con) {
    *old *= con;
}

void powr(int64_t* old, int con) {
    for (int i = 1; i < con; i++) {
        *old = *old * *old;
    }
}

void print_monkey(monkey* m) {
    printf("has items: ");
    for (int i = 0; i < m->itemcount; i++) {
        printf("[%ld]", m->items[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("no input file\n");
        exit(EXIT_FAILURE);
    }
    FILE* input = fopen(argv[1], "r");

    char* lineptr = 0;
    size_t linelength = 0;
    char* tok;

    monkey* m = calloc(MONKEYS, sizeof(monkey));

    if (input) {
        // Step 1: Parse the monkeys
        for (int i = 0; i < MONKEYS; i++) {

            // Monkey
            getline(&lineptr, &linelength, input);
            if (strcmp(lineptr, "\n") == 0) {
                getline(&lineptr, &linelength, input);
                printf("\n");
            }
            printf("Monkey %i\n", i);

            // Starting items
            getline(&lineptr, &linelength, input);
            tok = lineptr+18;
            strtok(tok, " \n");
            while (tok) {
                m[i].items[m[i].itemcount++] = strtol(tok, NULL, 10);
                tok = strtok(NULL, " \n");
            }
            print_monkey(&m[i]);

            // Operation
            getline(&lineptr, &linelength, input);
            if (strchr(lineptr, '+')) {
                printf("Operation add");
                m[i].operation = add;
            } else if (strchr(lineptr, '*')) {
                printf("Operation mult");
                m[i].operation = mult;
            } else {
                printf("Invalid Operation\n");
                exit(EXIT_FAILURE);
            }
            if (strstr(lineptr, "old * old")) {
                printf("Operation powr\n");
                m[i].operation = powr;
                m[i].con = 2;
            } else {
                printf(" %s", lineptr+25);
                m[i].con = strtol(lineptr+25, NULL, 10);
            }
            if (m[i].con <= 0) {
                printf("Failed to parse con\n");
                exit(EXIT_FAILURE);
            }

            // Test
            getline(&lineptr, &linelength, input);
            printf("test %li\n", strtol(lineptr+21, NULL, 10));
            m[i].test = strtol(lineptr+21, NULL, 10);
            if (m[i].test <= 0) {
                printf("Failed to parse test\n");
                exit(EXIT_FAILURE);
            }

            // true_dest
            getline(&lineptr, &linelength, input);
            printf("true_dest: %li\n", strtol(lineptr + strlen(lineptr) - 3, NULL, 10));
            m[i].true_dest = strtol(lineptr + strlen(lineptr) - 3, NULL, 10);

            // false_dest
            getline(&lineptr, &linelength, input);
            printf("false_dest: %li\n", strtol(lineptr + strlen(lineptr) - 3, NULL, 10));
            m[i].false_dest = atoi(&lineptr[strlen(lineptr)-3]);

        }
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    int cm = 1;
    for (int i = 0; i < MONKEYS; i++) {
        cm *= m[i].test;
    }
    printf("cm = %i\n", cm);


    printf("================\n");
    for (int round = 0; round < ROUNDS; round++) {
        printf("\n\nRound %i ===\n\n", round);
        for (int i = 0; i < MONKEYS; i++) {
            printf("Monkey %i ", i);
            print_monkey(&m[i]);
            for (int j = 0; j < m[i].itemcount; j++) {
                printf("Monkey %i inspecting item %i: %ld\n", i, j, m[i].items[j]);
                m[i].inspectcount++;
                m[i].items[j] %= cm;
                m[i].operation(&(m[i].items[j]), m[i].con);
                // m[i].items[j] /= 3;
                printf("Monkey %i new value of item %i: %ld\n", i, j, m[i].items[j]);

                if (m[i].items[j] % m[i].test == 0) {
                    // throw to true_dest
                    printf("Monkey %i throws item %i (%ld) to t Monkey %i\n", i, j, m[i].items[j], m[i].true_dest);
                    printf("Monkey %i ", m[i].true_dest);
                    print_monkey(&(m[m[i].true_dest]));
                    monkey* dest = &(m[m[i].true_dest]);
                    int dest_itemcount = dest->itemcount;
                    dest->items[dest_itemcount] = m[i].items[j];
                    dest->itemcount = dest_itemcount + 1;
                    printf("Monkey %i now ", m[i].true_dest);
                    print_monkey(&(m[m[i].true_dest]));
                } else {
                    // throw to false_dest
                    printf("Monkey %i throws item %i (%ld) to f Monkey %i\n", i, j, m[i].items[j], m[i].false_dest);
                    printf("Monkey %i ", m[i].false_dest);
                    print_monkey(&(m[m[i].false_dest]));
                    monkey* dest = &(m[m[i].false_dest]);
                    int dest_itemcount = dest->itemcount;
                    dest->items[dest_itemcount] = m[i].items[j];
                    dest->itemcount = dest_itemcount + 1;
                    printf("Monkey %i now ", m[i].false_dest);
                    print_monkey(&(m[m[i].false_dest]));
                }

            }
            m[i].itemcount = 0;
        }
    }

    int64_t max[2] = { 0 };
    for (int i = 0; i < MONKEYS; i++) {
        printf("Monkey %i has inspectet %i items.\n", i, m[i].inspectcount);
        if (m[i].inspectcount > max[0]) {
            max[1] = max[0];
            max[0] = m[i].inspectcount;
        } else if (m[i].inspectcount > max[1]) {
            max[1] = m[i].inspectcount;
        }
    }

    fprintf(stderr, "Solution is %li * %li = %li\n", max[0], max[1], max[0]*max[1]);

    free(m);
    free(lineptr);
}
