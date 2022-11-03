#include "header.h"
#include "data.h"

/**
 * @brief Array to store all available types of instructions
 */
static char *instruction_type[INSTRUCTION_LEN] = {"data", "string", "struct", "entry", "extern"};

int checkInstruction(char *line, int isLabel)
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
        while (!isspace(line[i]))
        {
            word[x] = line[i];
            i++;
            x++;
        }
        for (i = 0; i < INSTRUCTION_LEN; i++)
        {
            if (!strcmp(word, instruction_type[i]))
            {
                return i;
            }
        }
    }
    return -1;
}

void add2DataChain(data_t **head, int value)
{
    data_t *new_node = (data_t *)malloc(sizeof(data_t));
    data_t *current = NULL;
    if (*head != NULL)
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        new_node->value = value;
        new_node->address = (current->address) + 1;
        new_node->next = NULL;
        current->next = new_node;
    }
    else
    {
        new_node->value = value;
        new_node->address = 0;
        new_node->next = NULL;
        *head = new_node;
    }
}

data_t *getString(char *line, int line_num)
{
    data_t *strList = NULL;
    int i = 0;
    while (line[i] && (line[i] != '\"'))
    {
        i++;
    }
    if (line[i])
    {
        i++;
        while (line[i])
        {
            if (line[i] == 34)
            {
                break;
            }
            add2DataChain(&strList, (int)(line[i]));
            i++;
        }
    }
    add2DataChain(&strList, 0);
    return strList;
}

data_t *getData(char *line, int line_num)
{
    data_t *dataList = NULL;
    char num[WORD_SIZE];
    int i = 0, x = 0, vector_element = 0;
    while (line[i] && line[i] != '.')
    {
        i++;
    }
    if (line[i])
    {
        while (line[i] && !isspace(line[i]))
        {
            i++;
        }
        i++;
        while (line[i])
        {
            while (line[i] && line[i] != ',')
            {
                if (!isdigit(line[i]))
                {
                    if (x != 0)
                    {
                        fprintf(stderr, "%s%s[ERROR] %sInvalid number has entered!\n[LINE] : %d\t%s\n", RED, BOLD, BLANK, line_num, line);
                        fprintf(stderr, "\t\t");
                        MARK_ERROR(line);
                    }
                }
                if (x >= 10)
                {
                    fprintf(stderr, "%s%s[ERROR] %sNumber too long!\n[LINE] : %d\t%s\n", RED, BOLD, BLANK, line_num, line);
                    fprintf(stderr, "\t\t");
                    MARK_ERROR(line);
                }
                num[x] = line[i];
                x++;
                i++;
            }
            num[x] = '\0';
            vector_element = atoi(num);
            add2DataChain(&dataList, vector_element);
            x = 0;
            if (line[i])
            {
                i++;
            }
        }
    }
    return dataList;
}

data_t *getStruct(char *line, int line_num)
{
    data_t *structList = NULL;
    char element[WORD_SIZE];
    int i = 0, x = 0, vector_element = 0;
    while (line[i] && line[i] != '.')
    {
        i++;
    }
    if (line[i])
    {
        while (line[i] && !isspace(line[i]))
        {
            i++;
        }
        if (line[i])
        {
            i++;
        }
        while (line[i])
        {
            if (line[i] == '"')
            {
                i++;
                while (line[i] && line[i] != '"')
                {
                    add2DataChain(&structList, (int)(line[i]));
                    i++;
                }
                add2DataChain(&structList, 0);
                i++;
            }
            else
            {
                while (line[i] && line[i] != ',')
                {
                    if (x >= 10)
                    {
                        fprintf(stderr, "%s%s[ERROR] %sNumber too long!\n[LINE] : %d\t%s\n", RED, BOLD, BLANK, line_num, line);
                        fprintf(stderr, "\t\t");
                        MARK_ERROR(line);
                    }
                    if (!isdigit(line[i]))
                    {
                        if (x != 0)
                        {
                            fprintf(stderr, "%s%s[ERROR] %sInvalid number has entered!\n[LINE] : %d\t%s\n", RED, BOLD, BLANK, line_num, line);
                            fprintf(stderr, "\t\t");
                            MARK_ERROR(line);
                        }
                    }
                    element[x] = line[i];
                    x++;
                    i++;
                }
                element[x] = '\0';
                vector_element = atoi(element);
                add2DataChain(&structList, vector_element);
                x = 0;
                if (line[i])
                {
                    i++;
                }
            }
        }
    }
    return structList;
}

void add2DataList(data_list **head, data_t *node)
{
    data_list *current = NULL;
    data_list *new_data_node = (data_list *)malloc(sizeof(data_list));
    new_data_node->data_chain = node;
    new_data_node->next = NULL;
    if (*head != NULL)
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_data_node;
    }
    else
    {
        *head = new_data_node;
    }
}

int handleInstruction(char *line, int line_num, int isLabel, data_list **DATA_LIST, entry_t **ENTRY_LIST, extern_t **EXTERN_LIST)
{
    int result = 0;
    switch (checkInstruction(line, isLabel))
    {
    case 0:
        /* data */
        add2DataList(DATA_LIST, getData(line, line_num));
        result = 0;
        break;
    case 1:
        /* string */
        result = 1;
        add2DataList(DATA_LIST, getString(line, line_num));
        break;

    case 2:
        /* struct */
        result = 2;
        add2DataList(DATA_LIST, getStruct(line, line_num));
        break;
    case 3:
        /* entry */
        result = 3;
        addEntry(ENTRY_LIST, getCurrent_label(line));
        break;
    case 4:
        /* extern */
        result = 4;
        addExtern(EXTERN_LIST, getCurrent_label(line));
        break;
    default:
        result = -1;
        break;
    }
    return result;
}

char *getCurrent_label(char *line)
{
    char *label = (char *)malloc(LABEL_MAX_LEN);
    int i = 0, x = 0;
    while (line[i] && (line[i] != '.'))
    {
        i++;
    }
    if (line[i])
    {
        while ((line[i]) && !isspace(line[i]))
        {
            i++;
        }
        if (line[i])
        {
            i++;
        }
        while (line[i] && isalnum(line[i]))
        {
            label[x++] = line[i++];
        }
        label[x] = '\0';
        return label;
    }
    else
    {
        free(label);
        return NULL;
    }
}

void addEntry(entry_t **head, char *label)
{
    entry_t *current = *head;
    entry_t *new_node = (entry_t *)malloc(sizeof(entry_t));
    new_node->label = label;
    new_node->next = NULL;
    if (current != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    else
    {
        *head = new_node;
    }
}

void addTo_EntryFile(entry_file **head, char *label, int address)
{
    entry_file *current = *head;
    entry_file *new_node = (entry_file *)malloc(sizeof(entry_file));
    new_node->label = (char *)malloc(WORD_SIZE * sizeof(char));
    strcpy(new_node->label, label);
    new_node->address = address;
    new_node->next = NULL;
    if (current != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    else
    {
        *head = new_node;
    }
}

void addExtern(extern_t **head, char *label)
{
    extern_t *current = *head;
    extern_t *new_node = (extern_t *)malloc(sizeof(extern_t));
    new_node->label = label;
    new_node->next = NULL;
    if (current != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    else
    {
        *head = new_node;
    }
}

void addTo_ExternFile(extern_file **head, char *label, int address)
{
    extern_file *current = *head;
    extern_file *new_node = (extern_file *)malloc(sizeof(extern_file));
    new_node->label = (char *)malloc(WORD_SIZE * sizeof(char));
    strcpy(new_node->label, label);
    new_node->address = address;
    new_node->next = NULL;
    if (current != NULL)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    else
    {
        *head = new_node;
    }
}

int getDC(data_list *head)
{
    data_list *current = head;
    data_t *current_chain = NULL;
    int dc = 0;
    if (current)
    {
        while (current)
        {
            current_chain = current->data_chain;
            while (current_chain)
            {
                dc++;
                current_chain = current_chain->next;
            }
            current = current->next;
        }
    }
    return dc;
}

void freeData_List(data_list **head)
{
    data_list *current = *head;
    data_list *prev = NULL;
    data_t *bitCurrent = NULL;
    data_t *bitPrev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            bitCurrent = prev->data_chain;
            while (bitCurrent->next)
            {
                bitPrev = bitCurrent;
                bitCurrent = bitCurrent->next;
                if (bitPrev)
                {
                    free(bitPrev);
                }
            }
            if (bitCurrent)
            {
                free(bitCurrent);
            }
            if (prev)
            {
                free(prev);
            }
        }
        bitCurrent = current->data_chain;
        while (bitCurrent->next)
        {
            bitPrev = bitCurrent;
            bitCurrent = bitCurrent->next;
            if (bitPrev)
            {
                free(bitPrev);
            }
        }
        if (bitCurrent)
        {
            free(bitCurrent);
        }
        if (current)
        {
            free(current);
        }
    }
}

void freeEntry_List(entry_t **head)
{
    entry_t *current = *head;
    entry_t *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            if (prev)
            {
                if (prev->label)
                {
                    free(prev->label);
                }
                free(prev);
            }
        }
        if (current)
        {
            if (current->label)
            {
                free(current->label);
            }
            free(current);
        }
    }
}
void freeExtern_List(extern_t **head)
{
    extern_t *current = *head;
    extern_t *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            if (prev)
            {
                if (prev->label)
                {
                    free(prev->label);
                }
                free(prev);
            }
        }
        if (current)
        {
            if (current->label)
            {
                free(current->label);
            }
            free(current);
        }
    }
}

/**
 * Function to free all entry_file nodes,
 * labels already free by freeSymbol_List.
 */
void free_EntryFile(entry_file **head)
{
    entry_file *current = *head;
    entry_file *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            if (prev)
            {
                if (prev->label)
                {
                    free(prev->label);
                }
                free(prev);
            }
        }
        if (current)
        {
            if (current->label)
            {
                free(current->label);
            }
            free(current);
        }
    }
}
/**
 * Function to free all entry_file nodes,
 * labels already free by freeSymbol_List.
 */
void free_ExternFile(extern_file **head)
{
    extern_file *current = *head;
    extern_file *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            if (prev)
            {
                if (prev->label)
                {
                    free(prev->label);
                }
                free(prev);
            }
        }
        if (current)
        {
            if (current->label)
            {
                free(current->label);
            }
            free(current);
        }
    }
}