#include "input.h"

/**
 * Return formated line with unneeded spaces,
 * Unline format_line which change the original line
 */
char *remove_spaces(char *line)
{
    char *formated_line = (char *)malloc(strlen(line) + 1);
    int i = 0;
    int index = 0;
    int flag = 1;
    int is_data = 1;

    if (!formated_line)
    {
        fprintf(stderr, "%s%s[ERROR] %sFailed to allocate memory!\n", RED, BOLD, BLANK);
        exit(-1);
    }
    /* Skip all whitechars in the beggining */
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
                formated_line[index++] = line[i];
                flag = 0;
            }
            i++;
        }
        if (line[i])
        {
            formated_line[index++] = line[i++];
            flag = 1;
        }
    }
    formated_line[index] = '\0';
    return formated_line;
}

/**
 * Function that return the macro name
 */
char *get_macro_name(char *current_line)
{
    char *line = remove_spaces(current_line);        /* Remove Unneeded whitespaces */
    char *macro_name = (char *)malloc(strlen(line)); /* Allocate enough space for macro name */
    int i = 0, index = 0;
    char *pos;
    if (!macro_name)
    {
        fprintf(stderr, "%s%s[ERROR] %sFailed to allocate memory!\n", RED, BOLD, BLANK);
        exit(-1);
    }
    pos = strstr(line, "macro");
    if (!pos)
    {
        fprintf(stderr, "%s%s[ERROR] %sInvalid macro name!\n", RED, BOLD, BLANK);
        return NULL;
    }
    index = pos - line;
    index += 6;

    while (line[index] && !isspace(line[index]))
    {
        macro_name[i++] = line[index++];
    }
    macro_name[i] = '\0';

    if(line)
    {
        free(line);
    }
    return macro_name;
}

/**
 * Function that check if the given "find_word" is present
 * in current line
 */
int handle_macro(char *line, char *find_word)
{
    if (strstr(line, find_word))
    {
        return 1;
    }
    return 0;
}

/**
 * This function append content to the macro content
 * Until reached the "endmacro" keyword
 */
char *append_macro_content(char *macro_content, char *new_content)
{
    char *content;
    if (!macro_content)
    {
        format_line(new_content);
        content = (char *)malloc(strlen(new_content) + 4);
        strcpy(content, new_content);
        free(new_content);
        return content;
    }
    else
    {
        format_line(new_content);
        content = (char *)malloc(strlen(macro_content) + strlen(new_content) + 4);
        strcpy(content, macro_content);
        strcat(content, "\n\t");
        strcat(content, new_content);
        free(macro_content);
        free(new_content);
        return content;
    }
}

/**
 * This function add a new macro to the macro_list
 */
void add_new_macro(char *macro_name, char *macro_content, macro_list **macro_table)
{
    macro_list *current = *macro_table;
    macro_list *new_macro = (macro_list *)malloc(sizeof(macro_list));
    new_macro->macro_name = (char *)malloc(strlen(macro_name)+1);
    strcpy(new_macro->macro_name, macro_name);
    new_macro->macro_content = macro_content;
    new_macro->next = NULL;
    if (current)
    {
        while (current->next)
        {
            current = current->next;
        }
        current->next = new_macro;
    }
    else
    {
        (*macro_table) = new_macro;
    }
}

/**
 * This function will free the macro list
 * After we finished to spread all macros
 */
void free_macro_list(macro_list **macro_table)
{
    macro_list *current = *macro_table;
    macro_list *prev = NULL;
    if (current)
    {
        while (current->next)
        {
            prev = current;
            current = current->next;
            free(prev->macro_name);
            free(prev->macro_content);
            free(prev);
        }
        free(current->macro_name);
        free(current->macro_content);
        free(current);
    }
}

/**
 * Replace all occurrences of a given a word in string.
 */
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    /* Fix: If oldWord and newWord are same it goes to infinite loop */
    if (!strcmp(oldWord, newWord))
    {
        return;
    }

    /*
     * Repeat till all occurrences are replaced.
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        /* Backup current line */
        strcpy(temp, str);

        /* Index of current found word */
        index = pos - str;

        /* Terminate str after word found index */
        str[index] = '\0';

        /* Concatenate str with new word */
        strcat(str, newWord);

        /* Concatenate str with remaining words after
           oldword found index. */
        strcat(str, temp + index + owlen);
    }
}

/**
 * The main macro function -
 * Spread all macro declaration into a new file
 */
int spread_macro(char *file_path)
{
    char *line;
    char *start_macro = "macro", *end_macro = "endmacro";
    char *source_file_name = (char *)malloc(strlen(file_path) + 4);
    char *dest_file_name = (char *)malloc(strlen(file_path) + 4);
    char *macro_name = NULL, *macro_content = NULL;
    FILE *fptr;
    FILE *new_fptr, *fTemp;
    macro_list *macro_table = NULL;
    macro_list *current_macro = NULL;
    char buffer[BUFFER_SIZE];
    if (!source_file_name || !dest_file_name)
    {
        fprintf(stderr, "%s%s[ERROR] %scouldn't allocate enough memory for file_name\n", RED, BOLD, BLANK);
    }

    strcpy(source_file_name, file_path);
    strcat(source_file_name, ".as");
    strcpy(dest_file_name, file_path);
    strcat(dest_file_name, ".am");
    fptr = getFile(source_file_name);
    if (fptr == NULL)
    {
        fprintf(stderr, "%s%s[ERROR] %sCouldn't find file - %s\n", RED, BOLD, BLANK, source_file_name);
        if (source_file_name)
        {
            free(source_file_name);
        }
        if (dest_file_name)
        {
            free(dest_file_name);
        }
        return 0;
    }
    new_fptr = fopen(dest_file_name, "w+");
    fTemp = fopen("replace.tmp", "w+");
    while (!feof(fptr))
    {
        line = getLinefromFile(fptr);
        if (handle_macro(line, start_macro))
        {
            macro_name = get_macro_name(line);
            if(line)
            {
                free(line);
            }
            macro_content = NULL;
            while (!feof(fptr))
            {
                line = getLinefromFile(fptr);

                if (handle_macro(line, end_macro))
                {
                    /* Macro ended */
                    break;
                }
                macro_content = append_macro_content(macro_content, line);
            }
            add_new_macro(macro_name, macro_content, &macro_table);
            if(macro_name)
            {
                free(macro_name);
            }
        }
        else
        {
            fputs(line, new_fptr);
            fputs("\n", new_fptr);
        }

        if (line)
        {
            free(line);
        }
    }
    if (!macro_table)
    {
        fclose(new_fptr);
        fclose(fTemp);
        fclose(fptr);
        
        if (source_file_name)
        {
            free(source_file_name);
        }
        if (dest_file_name)
        {
            free(dest_file_name);
        }

        remove("replace.tmp");
        fprintf(stderr, "%s%s[SUCCESS] %sNo macros in this file. - %s%s -> %s%s\n", GREEN, BOLD, BLANK, file_path, ".as", file_path, ".am");
        
        return 1;
    }
    current_macro = macro_table;
    while (current_macro)
    {
        rewind(new_fptr);
        rewind(fTemp);
        memset(buffer, 0, BUFFER_SIZE);
        while ((fgets(buffer, BUFFER_SIZE, new_fptr)) != NULL)
        {
            /* Replace all occurrence of word from current line */
            replaceAll(buffer, current_macro->macro_name, current_macro->macro_content);
            /* After replacing write it to temp file. */
            fputs(buffer, fTemp);
        }
        rewind(new_fptr);
        rewind(fTemp);
        memset(buffer, 0, BUFFER_SIZE);
        while ((fgets(buffer, BUFFER_SIZE, fTemp)) != NULL)
        {
            fputs(buffer, new_fptr);
        }
        current_macro = current_macro->next;
    }
    /* Close all files to release resource */
    fclose(new_fptr);
    fclose(fTemp);
    if (source_file_name)
    {
        free(source_file_name);
    }
    if (dest_file_name)
    {
        free(dest_file_name);
    }
    if (macro_table)
    {
        free_macro_list(&macro_table);
    }
    /* Remove temporary file */
    remove("replace.tmp");
    fprintf(stderr, "%s%s[SUCCESS] %sSpread all macros from file file - %s%s -> %s%s\n", GREEN, BOLD, BLANK, file_path, ".as", file_path, ".am");
    fclose(fptr);
    return 1;
}
