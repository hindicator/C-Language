#include "operands.h"
#define EXTERNAL_FORMAT_OUT "%s\t\t%s\n"
#define OBJECT_FORMAT_OUT "\t%s\t%s\n"

/**
 * All the available register_names
 */
char *register_names2[REGISTER_LEN] = {"r0", "r1", "r2", "r3",
                                       "r4", "r5", "r6", "r7"};

/**
 * All the character in our base32 language
 */
char base_dic[32] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>',
                     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};

/**
 * This function convert a decimal number to base32 number
 */
char *dec2base(int n)
{
    char *word = (char *)malloc(3 * sizeof(char));
    word[0] = base_dic[((n >> 5) & 31)];
    word[1] = base_dic[n & 31];
    word[2] = '\0';

    return word;
}

/**
 * This function return a string with
 * s2 appended to s1.
 */
char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
        return result; /* return the name of the file */
    }
    else
    {
        return NULL;
    }
}

/**
 * Function to check if operand is external
 */
int isOperand_external(char *label, extern_t *extern_list)
{
    extern_t *current = extern_list;
    if (label == NULL)
    {
        return 0;
    }
    while (current)
    {
        if (!strcmp(label, current->label))
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/**
 * Function to check if operand is entry
 */
int isOperand_entry(char *label, entry_t *entry_list)
{
    entry_t *current = entry_list;
    if (label == NULL)
    {
        return 0;
    }
    while (current)
    {
        if (!strcmp(label, current->label))
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/**
 * Function to get a struct address in operand label.
 */
int getStruct_address(char *line)
{
    int i = 0, k = 0;
    char struct_field[WORD_SIZE];
    while (line[i] && (line[i] != '.'))
    {
        i++;
    }
    if (line[i])
    {
        i++;
    }
    while (line[i] && isdigit(line[i]))
    {
        struct_field[k++] = line[i++];
    }
    struct_field[k] = '\0';
    return atoi(struct_field);
}

/**
 * Function to return the number value of operand
 * with addressing type of 0 - immediate addressing
 */
int getOperand_num(char *word)
{
    int i = 0, x = 0;
    char num[WORD_SIZE];
    if (word == NULL)
    {
        return -1;
    }
    if (word[0] == '#')
    {
        i++;
        while (word[i] && (isdigit(word[i]) || (word[i] == '-') || (word[i] == '+')))
        {
            if ((x != 0) && (word[i] == '+' || word[i] == '-'))
            {
                printf("Invalid number!\n");
            }
            num[x++] = word[i++];
        }
        num[x] = '\0';
        return atoi(num);
    }
    else
    {
        return -1;
    }
}

/**
 * Function to return the register number value of operand
 * with addressing type of 3 - Register straight addressing
 */
int getRegister_num(char *word)
{
    int i;
    /* Address type number 3 */
    for (i = 0; i < 8; i++)
    {
        if (!strcmp(word, register_names2[i]))
        {
            return i;
        }
    }
    return -1;
}

/**
 * Function to get the operand type
 */
int getOperand_Type(char *word, symbol_t *LABEL_LIST)
{
    int i = 0;

    /* Validation for errors */
    if (word == NULL)
    {
        return -1;
    }
    /* Address type number 0 */
    if (word[0] == '#')
    {
        return 0;
    }
    /* Address type number 1 */
    if (findSymbol_Address(LABEL_LIST, word) >= 0)
    {
        return 1;
    }
    /* Address type number 2 */
    for (i = 0; word[i]; i++)
    {
        if (word[i] == '.' && i != 0)
        {
            return 2;
        }
    }
    /* Address type number 3 */
    for (i = 0; i < 8; i++)
    {
        if (!strcmp(word, register_names2[i]))
        {
            return 3;
        }
    }
    /* If none - return 1, as label may exist in second process */
    return 1;
}

/** 
 * Get operand by Label - includes Struct field
 */
void formatOperand(char **operand)
{
    int i = 0;
    if (*operand == NULL)
    {
        return;
    }
    while ((*operand)[i] && (isalnum((*operand)[i])))
    {
        i++;
    }
    (*operand)[i] = '\0';
}

/**
 * Function that return the label of operand 1
 */
char *getOperand1_Label(char *line, int isLabel)
{
    char *word;
    int i = 0, x = 0;
    int isComma = 0;
    /* Check if comma exist */
    while (line[i])
    {
        if (line[i] == ',')
        {
            isComma = 1;
        }
        i++;
    }
    if (isComma)
    {
        word = (char *)malloc(WORD_SIZE * sizeof(char));
        i = 0;
        if (isLabel)
        {
            while (line[i] && line[i] != ' ')
            {
                i++;
            }
            i++;
        }
        while (line[i] && !isspace(line[i]))
        {
            i++;
        }
        if (line[i])
        {
            i++;
            while (line[i] && !isspace(line[i]) && (line[i] != ','))
            {
                if (x >= 10)
                {
                    fprintf(stderr, "%s%s[ERROR] %sNumber too long!\n\t%s\n", RED, BOLD, BLANK, line);
                    fprintf(stderr, "\t\t");
                    MARK_ERROR(line);
                }
                word[x] = line[i];
                i++;
                x++;
            }
            word[x] = '\0';
        }
    }
    else
    {
        return NULL;
    }

    return word;
}

/**
 * Function that return the label of operand 2
 */
char *getOperand2_Label(char *line, int isLabel)
{
    char *word = (char *)malloc(WORD_SIZE * sizeof(char));
    int i = 0, x = 0;
    int isComma = 0;
    while (line[i])
    {
        if (line[i] == ',')
        {
            isComma = 1;
        }
        i++;
    }
    if (isComma)
    {
        i = 0;
        while (line[i] && (line[i] != ','))
        {
            i++;
        }
        i++;
        while (line[i] && !isspace(line[i]) && line[i] != ',')
        {
            if (x >= 10)
            {
                fprintf(stderr, "%s%s[ERROR] %sNumber too long!\n\t%s\n", RED, BOLD, BLANK, line);
                MARK_ERROR(line);
            }
            word[x++] = line[i++];
        }
    }
    else
    {
        i = 0;
        if (isLabel)
        {
            while (line[i] && (line[i] != ' '))
            {
                i++;
            }
            i++;
        }
        while (line[i] && !isspace(line[i]))
        {
            i++;
        }
        if (line[i])
        {
            i++;
            while (line[i] && !isspace(line[i]) && (line[i] != ','))
            {
                if (x >= 10)
                {
                    fprintf(stderr, "%s%s[ERROR] %sNumber too long!\n%s\n", RED, BOLD, BLANK, line);
                    MARK_ERROR(line);
                }
                word[x] = line[i];
                i++;
                x++;
            }
        }
    }
    word[x] = '\0';

    return word;
}
