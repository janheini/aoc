#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBDIRS 16
#define MAX_NAME 64

struct node {
    char name[MAX_NAME];
    struct node* parent;
    int childcount;
    struct node* children[MAX_SUBDIRS];
    size_t size;
};

void free_filetree(struct node* root) {
    for (int i = 0; i < root->childcount; i++) {
        free_filetree(root->children[i]);
    }
    free(root);
}

size_t get_size(struct node* root) {
    int size = 0;
    for (int i = 0; i < root->childcount; i++) {
        size += get_size(root->children[i]);
    }
    return size += root->size;
}

size_t get_sum_of_dirs_with_max_size(struct node* root, size_t max_size) {
    static size_t sum_size = 0;
    for (int i = 0; i < root->childcount; i++) {
        get_sum_of_dirs_with_max_size(root->children[i], max_size);
    }
    if (strcmp(root->name, "/") == 0) {
        return sum_size;
    }
    size_t size = get_size(root);
    if (size < max_size && root->childcount > 0) {
        printf("%s is small enough: %zu\n", root->name, size);
        sum_size += size;
        return size;
    }
    return 0;
}

size_t find_smallest_dir_with_min_size(struct node* root, size_t min_size, size_t max_size) {
    size_t size = get_size(root);
    if (size > min_size) {
        if (size < max_size) {
            max_size = size;
        }
        for (int i = 0; i < root->childcount; i++) {
            max_size = find_smallest_dir_with_min_size(root->children[i], min_size, max_size);
        }
    }
    return max_size;
}

int main(void) {
    FILE* input = fopen("./day7_input.txt", "r");

    char* lineptr = 0;
    size_t linelength = 0;
    int chars = 0;

    struct node* root = calloc(1, sizeof(struct node));
    strcpy(root->name, "/");

    struct node* curr = root;

    // skip the first two lines
    getline(&lineptr, &linelength, input);

    if (input) {
        while (getline(&lineptr, &linelength, input) > 0) {
            strtok(lineptr, "\n"); // removes trailing \n
            
            if (strncmp(lineptr, "$ cd ..", 7) == 0) {
                printf("CD .. !\n");
                curr = curr->parent;
                continue;
            }

            if (strncmp(lineptr, "$ cd", 4) == 0) {
                printf("CD: %s\n", lineptr + 5);
                for (int i = 0; i < curr->childcount; i++) {
                    printf("Looking for %s, child nr %i: %s.\n", lineptr + 5, i, curr->children[i]->name);
                    if (strcmp(curr->children[i]->name, lineptr + 5) == 0) {
                        printf("FOUND %s\n", lineptr +5);
                        curr = curr->children[i];
                        break;
                    }
                }
                if (strcmp(curr->name, lineptr + 5) != 0) {
                    printf("DIR %s NOT FOUND!\n", lineptr + 5);
                    exit(EXIT_FAILURE);
                }
                continue;
            }

            if (strncmp(lineptr, "$ ls", 4) == 0) {
                printf("LS: %s\n", lineptr);
                continue;
            }

            // else create a child
            struct node* child = calloc(1, sizeof(struct node));
            curr->children[curr->childcount++] = child;    
            if (strncmp(lineptr, "dir", 3) == 0) {
                // it's a directory
                strcpy(child->name, lineptr + 4);
                child->parent = curr;
                printf("added dir %s to %s\n", child->name, curr->name);
            } else {
                // it's a file
                char* tok = lineptr;
                child->size = atoi(strtok(tok, " \n"));
                strcpy(child->name, strtok(NULL, " \n"));
                printf("added file %s to %s\n", child->name, curr->name);
            }

        }

        if (errno != 0) {
            perror("getline");
        }
    } else {
        perror("fopen");
    }

    printf("Full size is %zu\n", get_size(root));
    printf("Sum of dirs with max size 100000: %zu\n", get_sum_of_dirs_with_max_size(root, 100000));

    printf("We have %i, we need %i, currently free is %lu, so we need another, %lu\n", 70000000, 30000000, 70000000 - get_size(root), 30000000 - (70000000 - get_size(root)));
    printf("Smallest dir that's big enough has size %zu\n", find_smallest_dir_with_min_size(root, 30000000 - (70000000 - get_size(root)), 70000000));

    free(lineptr);
    free_filetree(root);
}
