#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
struct node
{
    char *word;
    int length;
    struct node *next;
};
typedef struct node node_t;

/**
 * Function to check whether a file exists or not.
 * It returns 1 if file exists at given path otherwise
 * returns 0.
 */
int isFileExists(const char *path);
/**
 * Function to read 1 word from given file.
 * Return pointer to string if didn't reach EOF
 * Return NULL if reached EOF.
 */
char *readWord(FILE *fptr);
/**
 * Function to create a new node.
 * Return pointer node.
 */
node_t *create_new_node(char *word);
/**
 * Function for prettier print of linked list.
 */
void printList(node_t **head);
/**
 * Function to add a new node into the end of the list.
 */
void add2list(node_t **head, char *word);