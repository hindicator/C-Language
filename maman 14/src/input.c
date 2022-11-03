#include "input.h"

char *instruction_list[INSTRUCTION_LEN] = {"data", "string", "struct", "entry", "extern"};

/**
 * 16 different types of commands,
 * Array to store all different types of commands
 */
char *command_names[COMMAND_LEN] = {"mov", "cmp", "add", "sub",
                                    "not", "clr", "lea", "inc",
                                    "dec", "jmp", "bne", "get",
                                    "prn", "jsr", "rts", "hlt"};

/**
 * 8 Different register names,
 * Array to store register names
 */
char *register_names[REGISTER_LEN] = {"r0", "r1", "r2", "r3",
                                      "r4", "r5", "r6", "r7"};

FILE *getFile(char *file_name)
{
    FILE *fptr;
    fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "%s%s[ERROR] %scouldn't find file - %s\nPlease enter valid filepath.\nExample - ./program test1 test2\n", RED, BOLD, BLANK, file_name);
        return NULL;
    }
    return fptr;
}

char *getLinefromFile(FILE *fptr)
{
    char *line = (char *)calloc(10, sizeof(char)); /* Main character pointer */
    char c;
    /* char *arr;*/
    int index = 0;
    int current_size = 10;
    /* int is_icreased = 0;*/
    if (fptr == NULL)
    {
        printf("Invalid input.");
        if (!line)
            free(line);
        return NULL;
    }
    /* Extract characters from file and store in character c */
    while ((c = getc(fptr)) != EOF)
    {
        if (c == '\n') /* Increment count if this character is newline */
        {
            break;
        }
        if (!((index + 1) % 10))
        {
            input_addSize(line, current_size, char);
        }
        line[index++] = c;
    }
    line[index] = '\0';
    return line;
}

void format_line(char *line)
{
    int i = 0;
    int index = 0;
    int flag = 1;
    int is_data = 1;
    while (line[i] && isspace(line[i]))
    {
        i++;
    }
    while (line[i])
    {
        if (line[i] == ',' || line[i] == '.')
        {
            if ((line[i] == '.') && i == 0)
            {
                is_data = 1;
            }
            else
            {
                is_data = 0;
            }
        }
        while (line[i] && isspace(line[i]))
        {
            if (flag == 1 && is_data == 1)
            {
                line[index++] = line[i];
                flag = 0;
            }
            i++;
        }
        if (line[i])
        {
            line[index++] = line[i++];
            flag = 1;
        }
    }
    line[index] = '\0';
}

int get_sentence_type(char *line, int isLabel)
{
    if (!line)
    {
        return 0;
    }
    if (line[0] == '\0')
    {
        return 1;
    }
    if (line[0] == ';')
    {
        return 2;
    }
    if (isInstruction(line, isLabel))
    {
        return 3;
    }
    if (get_command_type(line, isLabel) >= 0)
    {
        return 4;
    }

    return 0;
}

int get_command_type(char *line, int isLabel)
{
    char op_code[WORD_SIZE];
    int i, x = 0;
    for (i = 0; i < WORD_SIZE; i++)
    {
        op_code[i] = '\0';
    }
    i = 0;
    if (isLabel)
    {
        while (!isspace(line[i]))
        {
            i++;
        }
        i++;
    }
    while (line[i] && line[i] != ' ')
    {
        if (x >= WORD_SIZE)
        {
            printf("Command type is not valid!\n");
            exit(-1);
        }
        op_code[x] = line[i];
        i++;
        x++;
    }
    for (i = 0; i < 16; i++)
    {
        if (strcmp(op_code, command_names[i]) == 0)
        {
            return i;
        }
    }

    printf("Invalid command type!\n");
    exit(-1);
}

void add_new_data(mem_wt **cmd_list, data_list **DATA_LIST)
{
    mem_wt *curr_memory_word = *cmd_list;
    data_list *curr_data = *DATA_LIST;
    data_t *new_data = NULL;
    if (curr_memory_word)
    {
        while (curr_memory_word->next)
        {
            curr_memory_word = curr_memory_word->next;
        }
    }
    if (curr_data)
    {
        while (curr_data->next)
        {
            curr_data = curr_data->next;
        }
        new_data = curr_data->data_chain;
        while (new_data)
        {
            addMemword(cmd_list, new_data->value);
            new_data = new_data->next;
        }
    }
}

int isInstruction(char *line, int isLabel)
{
    char word[WORD_SIZE];
    int i = 0;
    int x = 0;
    for (i = 0; i < WORD_SIZE; i++)
    {
        word[i] = '\0';
    }
    i = 0;
    if (isLabel)
    {
        while (line[i] && !isspace(line[i]))
        {
            i++;
        }
    }
    while (line[i] && line[i] != '.')
    {
        i++;
    }
    if (line[i] == '.')
    {
        i++;
        while (line[i] && !isspace(line[i]))
        {
            word[x] = line[i];
            i++;
            x++;
        }
        for (i = 0; i < INSTRUCTION_LEN; i++)
        {
            if (!strcmp(word, instruction_list[i]))
            {
                return 1;
            }
        }
    }
    return 0;
}

int handleSentence(char *line, int line_num, int isLabel, data_list **DATA_LIST, symbol_t **LABEL_LIST, mem_wt **cmd_list, entry_t **entry_list, extern_t **extern_list)
{
    int sentenceType = get_sentence_type(line, isLabel);
    int result = 0;
    int tmp = -1;
    switch (sentenceType)
    {
    case 1:
        result = 1;
        break;
    case 2:
        result = 1;
        break;
    case 3:
        result = 1;
        tmp = handleInstruction(line, line_num, isLabel, DATA_LIST, entry_list, extern_list);
        if ((tmp >= 0) && (tmp <= 2))
            add_new_data(cmd_list, DATA_LIST);
        break;
    case 4:
        result = 1;
        handleCommand(line, isLabel, LABEL_LIST, cmd_list, entry_list, extern_list);
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

int getCurrentAddress(mem_wt *cmd_list)
{
    mem_wt *curr = cmd_list;
    if (curr)
    {
        while (curr->next)
        {
            curr = curr->next;
        }
        return (curr->address) + 1;
    }
    else
    {
        return 100;
    }
}