#include "lists_c.h"

int main(int argc, char **argv)
{
    node_t *head = NULL;
    FILE *fptr;
    char *word;
    /* Check if user entered a valid filepath */
    if (argc > 1)
    {
        if (isFileExists(argv[1]))
        {
            fptr = fopen(argv[1], "r");
        }
        else
        {
            printf("Couldn't find file, please enter a valid filepath.\nExample - ./lists_c test.txt\n");
            exit(-1);
        }
    }
    else
    {
        printf("Please enter filepath.\nExample - ./lists_c test.txt\n");
        exit(-1);
    }
    while (!(feof(fptr)))
    {
        word = readWord(fptr);
        if (word != NULL)
        {
            add2list(&head, word);
        }
    }
    printList(&head);
    fclose(fptr);

    return 0;
}

/*====================================================================*/
/* Description for the functions is available in the header file. */

int isFileExists(const char *path)
{
    /* Try to open file */
    FILE *fptr = fopen(path, "r");

    /* If file does not exists  */
    if (fptr == NULL)
        return 0;

    /* File exists hence close file and return true. */
    fclose(fptr);

    return 1;
}
char *readWord(FILE *fptr)
{
    char ch;
    char *word;
    char *word_tmp;
    int cnt = 1, index = 0;
    word = (char *)malloc(15 * sizeof(char));
    if (feof(fptr))
    {
        return NULL;
    }
    ch = fgetc(fptr);
    if (isspace(ch) && ch != '\n')
    {
        return NULL;
    }
    while (!feof(fptr))
    {
        /* Increase string size every 10 chars */
        if (!(cnt % 10))
        {
            word_tmp = (char *)realloc(word, ((10 + cnt) * sizeof(char)));
            if (!word_tmp)
            {
                printf("Error reallocating!\n");
                exit(-1);
            }
            word = word_tmp;
        }
        if (ch == ' ' || ch == EOF)
        {
            break;
        }
        else if (ch == '\n')
        {
            word[index++] = ch;
            break;
        }
        else
        {
            word[index] = ch;
        }
        index++;
        cnt++;
        ch = fgetc(fptr);
    }
    word[index] = '\0';
    return word;
}
node_t *create_new_node(char *word)
{
    node_t *result = (node_t *)malloc(sizeof(node_t));
    int i = 0;
    result->word = word;
    result->next = NULL;
    while (word[i])
    {
        i++;
    }
    result->length = i;
    return result;
}
void sideBorder(int current_column)
{
    int i = 0;
    for (i = current_column; i < 70; i++)
    {
        printf(" ");
    } /* for */
    printf("|\n");
} /* sideBorder */
void heightBorder()
{
    int i = 0;
    for (i = 0; i < 71; i++)
    {
        printf("=");
    } /* for */
    printf("\n");
} /* heightBorder */
void printList(node_t **head)
{
    node_t *currNode = *head;
    int i = 0;
    int current_column = 0; /* Making sure to use a new line every 60 columns */
    heightBorder();
    while (currNode != NULL)
    {
        if (current_column + currNode->length < 60)
        {
            if ((currNode->word)[currNode->length - 1] == '\n')
            {
                i = 0;
                while (i < currNode->length - 1)
                {
                    printf("%c", (currNode->word)[i]);
                    i++;
                }
                sideBorder(current_column + i);

                current_column = 0;
            }
            else
            {
                printf("%s ", currNode->word);
                current_column += currNode->length + 1;
            }
        }
        else
        {
            sideBorder(current_column);
            printf("%s ", currNode->word);
            current_column = currNode->length + 1;
        }
        currNode = currNode->next;
    }
    sideBorder(current_column);
    heightBorder();
}
void add2list(node_t **head, char *word)
{
    node_t *currNode = *head;
    if (currNode == NULL)
    {
        *head = create_new_node(word);
        return;
    }
    while (currNode->next != NULL)
    {
        currNode = currNode->next;
    }
    currNode->next = create_new_node(word);
}
/*====================================================================*/