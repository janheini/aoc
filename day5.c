#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char val;
    struct node* next;
};

int push(char val, struct node** node) {
    struct node* new = malloc(sizeof(struct node));
    new->val = val;
    new->next = *node;
    *node = new;
    return 0;
}

int append(char val, struct node** node) {
    if (!node || !*node) {
        struct node* new = malloc(sizeof(struct node));
        new->val = val;
        new->next = NULL;
        *node = new;
        return 0;
    }

    if (!(*node)->next) {
        struct node* new = malloc(sizeof(struct node));
        new->val = val;
        new->next = NULL;
        (*node)->next = new;
        return 0;
    }

    append(val, &(*node)->next);
    return 0;

}

char pop(struct node** node) {
    struct node* n = *node;
    char val = n->val;
    *node = (*node)->next;
    free(n);
    return val;
}

void print_stack(struct node* node) {
    while (node) {
        printf("[%c]", node->val);
        node = node->next;
    }
    printf("\n");
}

void free_stack(struct node* node) {
    if (!node) {
        return;
    }

    if (node->next) {
        free_stack(node->next);
    }

    free(node);
    return;
}

void cratemover9000(int amount, struct node** fromstack, struct node** tostack) {
    for (int i = 0; i < amount; i++) {
        push(pop(fromstack), tostack);
    }
}
void cratemover9001(int amount, struct node** fromstack, struct node** tostack) {
    struct node* tmp = NULL;
    for (int i = 0; i < amount; i++) {
        push(pop(fromstack), &tmp);
    }
    for (int i = 0; i < amount; i++) {
        push(pop(&tmp), tostack);
    }
    // tmp is always empty so no need to free
}

int main(void) {
    FILE* input = fopen("./day5_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;
    int chars = 0;

    int* bounds = malloc(4 * sizeof(int));
    int count = 0;
    int countoverlaps = 0;

    struct node* stacks[9] = { NULL };
    struct node* tmpstack = NULL;

    if (input) {
        for (;;) {
            chars = getline(&lineptr, &linelength, input);
            if (chars < 0) {
                break;
            }

            // printf("%s", lineptr);
            if (strcmp(" 1   2   3   4   5   6   7   8   9 \n", lineptr) == 0) {
                printf("\nend init\n");
                getline(&lineptr, &linelength, input); // skip empty line
                break;
            }

            int column = 1;
            for (int i = 0; i < 9; i++) {
                if (lineptr[column] != ' ') {
                    printf("%c", lineptr[column]);
                    append(lineptr[column], &(stacks[i]));
                }
                column += 4;
            }
            printf("\n");

            for (int i = 0; i < 9; i++) {
                printf("%i :", i+1);
                print_stack(stacks[i]);
            }

        }

        for (;;) {
            chars = getline(&lineptr, &linelength, input);
            if (chars < 0) {
                break;
            }

            char* tokens[6];
            tokens[0] = strtok(lineptr, " \n");
            for (int i = 1; i < 6; i++) {
                tokens[i] = strtok(NULL, " \n");
            }

            printf("|");
            for (int i = 0; i < 6; i++) {
                printf("%s|", tokens[i]);
            }
            printf("\n");

            //cratemover9000(atoi(tokens[1]), &stacks[atoi(tokens[3])-1], &stacks[atoi(tokens[5])-1]);
            cratemover9001(atoi(tokens[1]), &stacks[atoi(tokens[3])-1], &stacks[atoi(tokens[5])-1]);

            // for (int i = 0; i < atoi(tokens[1]); i++) {
            //     printf("%i From stack %i to stack %i\n", atoi(tokens[1]), atoi(tokens[3]), atoi(tokens[5]));
            //     push(pop(&stacks[atoi(tokens[3])-1]), &stacks[atoi(tokens[5])-1]);
            // }

            for (int i = 0; i < 9; i++) {
                printf("%i :", i+1);
                print_stack(stacks[i]);
            }

        }
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }
    free(lineptr);

    for (int i = 0; i < 9; i++) {
        printf("%i :", i+1);
        print_stack(stacks[i]);
    }

    for (int i = 0; i < 9; i++) {
        printf("%c", pop(&stacks[i]));
    }
    printf("\n");

    struct node* blaa = NULL;
    push('a', &blaa);
    push('b', &blaa);
    push('c', &blaa);
    append('d', &blaa);
    append('e', &blaa);
    append('f', &blaa);
    print_stack(blaa);
    free_stack(blaa);

}
