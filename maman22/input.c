#include "mat.h"
#include <stdarg.h>
void initilize_mat(mat **mat_arr)
{
    int i, j, k;
    for (k = 0; k < NUM_OF_MATS; k++)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                mat_arr[k]->theArr[i][j] = 0;
            }
        }
    }
} /* Initilize all mats */

/* Return array of words from the splited line */
char **split_line(char *line)
{
    char **word_array = (char **)calloc(MAX_WORD_IN_LINE, sizeof(char *));
    char word[MAX_WORD_SIZE];
    int i = 0, current_word = 0;
    int k = 0;
    int word_index = 0;

    for (i = 0; i < MAX_WORD_IN_LINE; i++)
    {
        word_array[i] = '\0';
    }
    for (i = 0; i < MAX_WORD_SIZE; i++)
    {
        word[i] = '\0';
    }
    i = 0;
    while (line[i])
    {
        if (current_word >= MAX_WORD_IN_LINE)
        {
            printf("Invalid parameters.\n");
        }
        if (line[i] == ' ' || line[i] == ',' || line[i] == '\n' || (i > 0 && line[i - 1] == ',') || (i > 0 && line[i - 1] == ' '))
        {
            word_array[current_word] = (char *)calloc(MAX_WORD_SIZE, sizeof(char));
            for (k = 0; k < MAX_WORD_SIZE; k++)
            {
                (word_array[current_word])[k] = word[k];
                word[k] = '\0';
            }
            current_word++;
            word_index = 0;
        }
        word[word_index++] = line[i];
        i++;
    } /* While */
    if (i == 0)
    {
        return NULL;
    }
    word[word_index++] = line[i];
    word_array[current_word] = (char *)calloc(20, sizeof(char));
    for (k = 0; k < MAX_WORD_SIZE; k++)
    {
        (word_array[current_word])[k] = word[k];
        word[k] = '\0';
    }
    return word_array;
} /* Split line function */

void free_word_arr(char **word_array)
{
    int i;
    for (i = 0; i < MAX_WORD_IN_LINE; i++)
    {
        if (word_array[i])
        {
            free(word_array[i]);
        }
    }
    if (word_array)
    {
        free(word_array);
    }
} /* Free words array */

/* Return all line from input */
char *get_input()
{
    char *input = (char *)calloc(20, sizeof(char)); /* Main character pointer */
    char *new_input;                                /* Temporary character pointer for realloc */
    char c;
    int index = 0;
    int current_size = 20;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            input[index] = '\0';
            return input;
        }
        if (!(index % 10))
        {
            current_size += 10;
            new_input = (char *)realloc(input, current_size); /* Try to realloc */
            if (!new_input)                                   /* If realloc return null, EXIT */
            {
                perror("Failed reallocate memory!\nCode Line - 46\n");
                exit(-1);
            }    /* if */
            else /* Return new pointer value to main pointer */
            {
                input = new_input;
            } /* else */
        }
        input[index++] = c; /* Save current character in input pointer */
        /* Increase index and numOfCharacters counter */
    }
    input[index] = '\0';
    printf("Program has stopped without stop command\n");
    return input;
} /* end of get_input - return input of line */

/* Remove all white chars from string after command */
void format_line(char **str)
{
    int i, x;
    i = 0;
    /* Pass all white chars on beginning */
    while ((*str[i]) && isspace((*str)[i]))
    {
        i++;
    }
    for (x = 0; (*str)[i]; i++)
        (*str)[x++] = (*str)[i];
    (*str)[x] = '\0';

    /* Remove all white chars after command location */
    i = x = 0;
    while (((*str)[i]) && !isspace((*str)[i]))
    {
        if (i > 10)
        {
            printf("Unvalid command!");
        }
        (*str)[x] = (*str)[i];
        i++;
        x++;
    }
    (*str)[x] = (*str)[i];
    x++;
    i++;
    while ((*str)[i])
    {
        if (!isspace((*str)[i]))
        {
            (*str)[x++] = (*str)[i];
        }
        i++;
    } /* While */
    (*str)[x] = '\0';
} /* End of format_line */

/* Return int value 0 - 5 based on string matrix index */
int mat_2_num(char *mat_num)
{
    int i = 0;
    /* All possible mat names for loop instead of hard coded */
    char *mat_names[NUM_OF_MATS] = {"MAT_A", "MAT_B", "MAT_C", "MAT_D", "MAT_E", "MAT_F"};
    for (i = 0; i < NUM_OF_MATS; i++)
    {
        if (strcmp(mat_num, mat_names[i]) == 0)
        {
            return i;
        }
    }
    if (mat_num[5])
    {
        printf("You have missed a comma between Matrix name and numbers\n");
    }
    else
    {
        printf("Undefined matrix name\n");
    }
    /* Mat name not valid */
    return -1;
} /* end of mat_2_num */

/* Return int - presenting the number of command*/
int command_num(char *first_word)
{
    /* All possible command types for loop instead of hard coded */
    const char *commandNames[COMMAND_NUM] = {"read_mat", "print_mat", "add_mat", "sub_mat", "mul_mat", "mul_scalar", "trans_mat", "stop"};
    int i;
    if (!first_word)
    {
        return -1;
    }
    for (i = 0; i < COMMAND_NUM; i++)
    {
        /* we compare the first word with each of the command names */
        if (!strcmp(commandNames[i], first_word))
        {
            return i;
        }
    }
    return -1;
} /* End of command_num */

/* Handle command of the input line */
void handle_command(char *line, mat **matrix_arr)
{
    char **word_array;
    int command_type = 0;
    double *input_vectors;
    if (!line)
    {
        /* Pass empty line */
        return;
    }
    format_line(&line);
    word_array = split_line(line);
    command_type = command_num(word_array[0]);
    if (!isValid_Commas(word_array))
    {
        printf("Multiple consecutive commas\n");
    }
    else if (word_array[1] && IS_COMMA((word_array[1])[0]))
    {
        printf("Illegal comma\n");
    }
    /* if-statements for all possible commands */
    /* Check which command */
    else if (command_type == -1)
    {
        printf("\nUndefined command name\n");
    }
    else if (command_type == 0) /* read_mat */
    {
        if (isValid_command(1, word_array[2]))
        {
            input_vectors = read_vectors(line);
            if (input_vectors && mat_2_num(word_array[2]) >= 0)
            {
                read_mat(matrix_arr[mat_2_num(word_array[2])], input_vectors);
            }
            if (input_vectors)
            {
                free(input_vectors);
            }
        }
    }
    else if (command_type == 1) /* print_mat */
    {
        if (isValid_command(1, word_array[2]))
        {
            if (mat_2_num(word_array[2]) >= 0)
            {
                print_mat(matrix_arr[mat_2_num(word_array[2])]);
            }
        }
    }
    else if (command_type == 2) /* Add command */
    {
        if (isValid_command(3, word_array[2], word_array[4], word_array[6]))
        {
            if (!(IS_COMMA((word_array[3])[0]) && IS_COMMA((word_array[5])[0]) && IS_COMMA((word_array[7])[0])))
            {
                printf("Missing comma\n");
            }
            else if (mat_2_num(word_array[2]) >= 0 && mat_2_num(word_array[4]) >= 0 && mat_2_num(word_array[6]) >= 0)
            {
                add_mat(matrix_arr[mat_2_num(word_array[2])], matrix_arr[mat_2_num(word_array[4])], matrix_arr[mat_2_num(word_array[6])]);
            }
        }
    }
    else if (command_type == 3) /* Sub command */
    {
        if (isValid_command(3, word_array[2], word_array[4], word_array[6]))
        {
            if (mat_2_num(word_array[2]) >= 0 && mat_2_num(word_array[4]) >= 0 && mat_2_num(word_array[6]) >= 0)
            {
                sub_mat(matrix_arr[mat_2_num(word_array[2])], matrix_arr[mat_2_num(word_array[4])], matrix_arr[mat_2_num(word_array[6])]);
            }
        }
    }
    else if (command_type == 4) /* mul command */
    {
        if (isValid_command(3, word_array[2], word_array[4], word_array[6]))
        {
            if (mat_2_num(word_array[2]) >= 0 && mat_2_num(word_array[4]) >= 0 && mat_2_num(word_array[6]) >= 0)
            {
                mul_mat(matrix_arr[mat_2_num(word_array[2])], matrix_arr[mat_2_num(word_array[4])], matrix_arr[mat_2_num(word_array[6])]);
            }
        }
    }
    else if (command_type == 5) /* mul_scalar */
    {
        if (isValid_command(3, word_array[2], word_array[4], word_array[6]))
        {
            if (mat_2_num(word_array[2]) >= 0 && mat_2_num(word_array[6]) >= 0)
            {
                mul_scalar(matrix_arr[mat_2_num(word_array[2])], atof(word_array[4]), matrix_arr[mat_2_num(word_array[6])]);
            }
        }
    }
    else if (command_type == 6) /* trans_mat */
    {
        if (!word_array[2])
        {
            printf("Mat 1 has undefined name\n");
        }
        else if (!word_array[4])
        {
            printf("Mat 2 has undefined name\n");
        }
        else if (mat_2_num(word_array[2]) >= 0 && mat_2_num(word_array[4]) >= 0)
        {
            trans_mat(matrix_arr[mat_2_num(word_array[2])], matrix_arr[mat_2_num(word_array[4])]);
        }
    }
    else if (command_type == 7) /* stop */
    {
        if (word_array[1] == NULL)
        {
            printf("\nThanks for playing!\n");
            free_word_arr(word_array);
            exit(0);
        }
        printf("Extraneous text after end of command\n");
    }
    free_word_arr(word_array);
}
/* Return pointer of vectors */
double *read_vectors(char *p)
{
    char current_num[MY_MAX_NUM_LEN];
    double *mat_vectors = (double *)calloc(20, sizeof(double));
    double *mat_vectors_tmp;
    int i = 0, vector_index = 0;
    double vector_element;
    int current_size = 20;
    /* Initilize vector array to zeros */
    /* While char not equal to , - increase counter */
    i = 0;
    while (p[i] && p[i] != ',')
    {
        i++;
    }
    i++;
    memset(current_num, 0, strlen(current_num)); /* Set all cells to 0 */
    while (p[i])
    {
        if (p[i] == '-' && vector_index == 0) /* Important for number */
        {
            strncat(current_num, &p[i], 1);
        }
        else if (p[i] == '+' && vector_index == 0) /* Not helping in positive double */
        {
        }
        else if (p[i] == ',')
        {
            vector_element = atof(current_num);
            if (!(vector_index + 2 % 10))
            {
                current_size += 10;
                mat_vectors_tmp = (double *)realloc(mat_vectors, current_size * sizeof(double)); /* Try to realloc */
                if (!mat_vectors_tmp)                                                            /* If realloc return null, EXIT */
                {
                    perror("Failed reallocate memory!\n");
                    exit(-1);
                }    /* if */
                else /* Return new pointer value to main pointer */
                {
                    mat_vectors = mat_vectors_tmp;
                } /* else */
            }
            mat_vectors[vector_index++] = vector_element;
            memset(current_num, 0, strlen(current_num));
        }
        else if (isdigit(p[i]) || p[i] == '.')
        {
            strncat(current_num, &p[i], 1);
        }
        else /* If char is not valid - free pointer and return null */
        {
            printf("Argument is not a real number\n");
            if (mat_vectors)
            {
                free(mat_vectors);
            }
            return NULL;
        }
        i++;
    } /* End of while */
    if(p[i-1] && p[i-1] == ',')
    {
        printf("Extraneous text after end of command\n");
        if(mat_vectors)
        {
            free(mat_vectors);
        }
        return NULL;
    }
    vector_element = atof(current_num);
    mat_vectors[vector_index++] = vector_element;
    memset(current_num, 0, strlen(current_num));
    return mat_vectors;
}

/* Prompting the user to enter input - ready to receive new command */
void user_promt()
{
    printf("\nEnter command :\n");
}

/* Validate that the command parameters are valid */
int isValid_command(int numOfArgs, ...)
{
    va_list myArgs;
    char *current_word;
    int i;
    va_start(myArgs, numOfArgs);
    for (i = 0; i < numOfArgs; i++)
    {
        current_word = va_arg(myArgs, char *);
        if (!current_word)
        {
            printf("Missing argument\n");
            return 0;
        }
    }
    va_end(myArgs);
    return 1;
}
/* Validate that the command parameters are valid */
int isValid_Commas(char **p)
{
    int i;
    for (i = 1; p[i]; i++)
    {
        if (*p[i] == ',' && *p[i - 1] == ',')
        {
            return 0;
        }
    }
    return 1;
}