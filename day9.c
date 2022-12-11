#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define LENGTH 2
#define LENGTH 10

typedef struct head {
    int length;
    struct node* next;
} list;

struct node {
    int x;
    int y;
    struct node* next;
};

struct rope_segment {
    int x;
    int y;
};

void print_list(list* l) {
    if (l) {
        struct node* node = l->next;
        while (node) {
            printf("[%i][%i]->", node->x, node->y);
            node = node->next;
        }
        printf("\n");
    } else {
        printf("[]\n");
    }
}

void insert(list* l, int x, int y) {
    struct node* node = l->next;
    while (node) {
        if (node->x == x && node->y == y)
            return;
        if (!node->next)
            break;
        node = node->next;
    }

    if (node) {
        // insert at the end
        node->next = malloc(sizeof(struct node));
        node->next->x = x;
        node->next->y = y;
        node->next->next = NULL;
        l->length++;
        printf("Length: %i\n", l->length);
    } else {
        l->next = malloc(sizeof(struct node));
        l->next->x = x;
        l->next->y = y;
        l->next->next = NULL;
        printf("Length: %i\n", l->length);
        l->length++;
    }
}

void free_list(struct node* node) {
    if (node->next)
        free_list(node->next);
    free(node);
}

void move(char d, struct node* h) {
    switch(d) {
        case 'U':
            h->x++;
            break;
        case 'D':
            h->x--;
            break;
        case 'L':
            h->y--;
            break;
        case 'R':
            h->y++;
            break;
    }
}

void follow(struct node* h, struct node* t) {
    if (h->x - t->x >= 2) {
        t->x++; // move tail to right
        if (h->y - t->y >= 1) {
            t->y++;
        }
        if (h->y - t->y <= -1) {
            t->y--;
        }
    }
    if (h->x - t->x <= -2) {
        t->x--; // move tail to left
        if (h->y - t->y >= 1) {
            t->y++;
        }
        if (h->y - t->y <= -1) {
            t->y--;
        }
    }

    if (h->y - t->y >= 2) {
        t->y++; // move tail up
        if (h->x - t->x >= 1) {
            t->x++;
        }
        if (h->x - t->x <= -1) {
            t->x--;
        }
    }
    if (h->y - t->y <= -2) {
        t->y--; // move tail down
        if (h->x - t->x >= 1) {
            t->x++;
        }
        if (h->x - t->x <= -1) {
            t->x--;
        }
    }
}

void move_amount_and_insert(char d, list* rope, int amount, list* l) {
    struct node* r;
    for (int i = 0; i < amount; i++) {
        r = rope->next; 
        move(d, r);
        while (r && r->next) {
            follow(r, r->next);
            r = r->next;
        }
        printf("Moved %c, inserting [%i][%i]\n", d, r->x, r->y);
        insert(l, r->x, r->y);
    }
}


int main(void) {
    FILE* input = fopen("./day9_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;

    list* l = malloc(sizeof(list));
    l->length = 0;
    l->next = NULL;

    list* rope = calloc(1, sizeof(list));
    rope->next = calloc(1, sizeof(struct node));
    rope->length = 1;
    struct node* r = rope->next;
    for (int i = 0; i < LENGTH-1; i++) {
        r->next = calloc(1, sizeof(struct node));
        rope->length++;
        r = r->next;
    }
    printf("Rope (%i): ", rope->length);
    print_list(rope);

    if (input) {
        while (getline(&lineptr, &linelength, input) > 0) {
            printf("\x1b[31m%s\x1b[0m", lineptr);
            move_amount_and_insert(lineptr[0], rope, atoi(lineptr+2), l);
            printf("Rope (%i): ", rope->length);
            print_list(rope);
            printf("List (%i)\n", l->length);
            //print_list(l);
        }
        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    free(lineptr);
    free_list(l->next);
    free(l);
    free_list(rope->next);
    free(rope);
}
