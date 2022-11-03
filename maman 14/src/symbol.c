#include "header.h"
#include "symbol.h"

/**
 * Function to check if the line containing a symbol
 */
int checkSymbol(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (isspace(line[i]))
        {
            return 0;
        }
        if (line[i] == ':')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

/**
 * Function to get the symbol value
 */
char *getSymbol(char *line)
{
    char *word = (char *)malloc(LABEL_MAX_LEN * sizeof(char));
    int i = 0;
    while (line[i] && line[i] != ':')
    {
        if (i == 0)
        {
            if (!isalpha(line[i]))
            {
                printf("Label name is not valid! - Label must start with alpha character.\n");
                exit(-1);
            }
        }
        if (i >= 30)
        {
            printf("Label name is too long - Label max legnth 30.\n");
            exit(-1);
        }
        word[i] = line[i];
        i++;
    }
    word[i] = '\0';
    return word;
}

/**
 * Function to create a new symbol node for symbol_list
 */
symbol_t *create_symbol_node(char *name, int address)
{
    symbol_t *node = (symbol_t *)malloc(sizeof(symbol_t));
    node->name = name;
    node->address = address;
    node->next = NULL;
    return node;
}

/**
 * Function to add a new symbol to the symbol_list
 */
void addSymbol(symbol_t **head, char *label, int address)
{
    symbol_t *current = *head;
    symbol_t *last;
    if (current)
    {
        while (current)
        {
            last = current;
            if (!strcmp(current->name, label))
            {
                printf("Label already exists!\n");
                exit(-1);
            }
            current = current->next;
        }
        last->next = create_symbol_node(label, address);
    }
    else
    {
        *head = create_symbol_node(label, address);
    }
}

/**
 * This function will free the symbol_list
 */
void freeSymbol_List(symbol_t **head)
{
    symbol_t *current = *head;
    symbol_t *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            if (prev)
            {
                if (prev->name)
                {
                    free(prev->name);
                }
                free(prev);
            }
        }
        if (current)
        {
            if (current->name)
            {
                free(current->name);
            }
            free(current);
        }
    }
}

/**
 * Function to return the memory address of a symbol.
 * Return -1 : If Label is not valid or not inside symbol_list
 */
int findSymbol_Address(symbol_t *label_list, char *label)
{
    symbol_t *current = label_list;
    int i = 0;
    if (label == NULL)
    {
        return -1;
    }
    while (current != NULL)
    {
        if (!strcmp(current->name, label))
        {
            return current->address;
        }
        i++;
        current = current->next;
    }

    return -1;
}