#include <stdio.h> /* printf, perror, sprintf */
#include <ctype.h> /* isalpha, isdigit */
#include <stdlib.h> /* calloc, atoi */
#include "header.h" /* pre declartion of all functions below */

int main()
{
    char *input; /* First 10 index are allocated for storing input size */
    /* Size limit is 10digit number 1 000 000 000 */
    int input_size;
    /* Friendly output guiding the user on input rules */
    printf("Hello, this program convert unbounded text length\ninto styled form.\n");
    /* Read user input until EOF */
    input = readText();
    input_size = my_itof(input);
    tablePrint(input, input_size);
    free(input);
    return 0;
} /* main */

char* readText()
{
    char *tmp = (char *)calloc(10, sizeof(char));
	char *input= NULL; /* Main character pointer */
    char *new_input; /* Temporary character pointer for realloc */
    int current_size = 20, i; /* Increase pointer size by 10 every 10characters */
    char c; /* The current character in read text process */
    int _index = 10; /* Pointer last index, i.e. (Pointer size)*(sizeof(char)) */
    int _numOfChars = 11; /* Counter for size increasement alert */
    printf("Please enter input : (Enter 'CTRL+d' to end)\n");
    input = (char*)calloc(20, sizeof(char)); /* Realloc minimum size */
    for(i = 0; i < 10; i++) /* Reset size storage adrress Incase calloc is older version which not reset by default */
    {
        input[i] = '\0';
    } /* for */
    while( (c = getchar()) != EOF ) /* Read characters until input EOF */
    {
        if(_numOfChars-1 == current_size) /* If need to increase pointer size */
        {
            current_size+=10; /* Pointer current size value increased by 10*/
            new_input = (char *) realloc(input, current_size); /* Try to realloc */
            if(!input) /* If realloc return null, EXIT */
            {
                perror("Failed reallocate memory!\nCode Line - 42\n");
                exit(-1);
            } /* if */
            else /* Return new pointer value to main pointer */
            {
                input = new_input;
            } /* else */
        } /* if */
        input[_index] = c; /* Save current character in input pointer */
        /* Increase index and numOfCharacters counter */
        _index++;
        _numOfChars++;
    } /* while */
    tmp = my_itoa(_index, tmp); /* Creates a number string from 10first elements in input pointer */
    for(i = 0; i < 10; i++) /* For loop 10 times to store pointer size in 10first characters */
    {
        input[i] = tmp[i];
    } /* for */
    return input;
} /* readText */
 
void tablePrint(char *input, int _index)
{
    int i = 0;
    int num_of_special_chars = 0; /* Counter for alpha-numeric character */
    int current_column = 1; /* Counter current column - max=60 then : new line */
    heightBorder(); /* Height border for styled output */
    for(i = 10; i < _index; i++)
    {
        if(isalnum(input[i])) /* if character is alpha-numeric - increase special character counter */
        {
            num_of_special_chars++;
        } /* if */
        if(input[i] == '\n')
        {
            sideBorder(current_column); /* Side border for styled output */
            current_column=1;
        } /* if */
        else if(current_column >= 60)
        {
            if(input[i] == ' ' || input[i] == '\n')
            {
                sideBorder(current_column); /* Side border for styled output */
                current_column=1;
            } /* if */
            else if(current_column==90)
            {
                printf("|\n");
                current_column=1;
                printf("%c", input[i]);
                current_column++;
            } /* else if */
            else
            {
                printf("%c", input[i]);
                current_column++;
            } /* else */
        }
        else
        {
            printf("%c", input[i]);
            current_column++;
        } /* else */
    } /* for */
    sideBorder(current_column); /* Side border for styled output */
    heightBorder(); /* Height border for styled output */
    printf("Total alpha-numeric characters : %d\n", num_of_special_chars);
    printf("Total input length : %d\n", _index);
} /* tablePrint */
void sideBorder(int current_column)
{
    int i = 0;
    for(i = current_column; i < 90; i++)
    {
        printf(" ");
    } /* for */
    printf("|\n");
} /* sideBorder */
void heightBorder()
{
    int i = 0;
    for(i = 0; i < 90; i++)
    {
        printf("=");
    } /* for */
    printf("\n");
} /* heightBorder */

char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
            return NULL;
        } /* if */
        sprintf(str, "%d", num);
        return str;
} /* my_itoa */
int my_itof(char *str)
{
    char *tmp_str = calloc(10, sizeof(char));
    int i;
    int x;
    if(str == NULL)
    {
        return 0;
    } /* if */
    for(i = 0; i<10; i++)
    {
        tmp_str[i] = str[i];
    } /* for */
    x = atoi(tmp_str);
    free(tmp_str);
    return x;
} /* my_itof */