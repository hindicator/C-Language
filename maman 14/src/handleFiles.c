#include "handleFiles.h"

/**
 * Function that write the content of cmd_list into
 * New file with .ob format.
 */
void write2file_obj(mem_wt *cmd_list, char *filename, int IC, int DC)
{
    FILE *fptr;
    mem_wt *current = cmd_list;
    char *current_address, *current_char;
    char *file_path = concat(filename, ".ob");
    if (current)
    {
        fptr = fopen(file_path, "w+");
        fprintf(fptr, "\t");
        if (IC <= 31)
        {
            current_char = dec2base(IC);
            fprintf(fptr, "%c ", current_char[1]);
            if (current_char)
            {
                free(current_char);
            }
        }
        else
        {
            current_char = dec2base(IC);
            fprintf(fptr, "%s ", current_char);
            if (current_char)
            {
                free(current_char);
            }
        }
        if (IC <= 31)
        {
            current_char = dec2base(DC);
            fprintf(fptr, "%c", current_char[1]);
            if (current_char)
            {
                free(current_char);
            }
        }
        else
        {
            current_char = dec2base(DC);
            fprintf(fptr, "%s", current_char);
            if (current_char)
            {
                free(current_char);
            }
        }
        fprintf(fptr, "\n");
        while (current)
        {
            current_address = dec2base(current->address);
            current_char = dec2base(current->value);
            fprintf(fptr, OBJECT_FORMAT_OUT, current_address, current_char);
            if (current_address)
            {
                free(current_address);
            }
            if (current_char)
            {
                free(current_char);
            }

            current = current->next;
        }
        if (fptr)
        {
            fclose(fptr);
        }
    }
    if (file_path)
    {
        free(file_path);
    }
}

/**
 * Function that write the content of extern_file list into
 * New file with .ext format.
 */
void write2file_ext(extern_file *extern_file_data, char *filename)
{
    FILE *fptr;
    extern_file *current = extern_file_data;
    char *current_address;
    char *file_path = concat(filename, ".ext");
    if (current)
    {
        fptr = fopen(file_path, "w+");
        while (current)
        {
            current_address = dec2base(current->address);
            fprintf(fptr, EXTERNAL_FORMAT_OUT, current->label, current_address);
            if (current_address)
            {
                free(current_address);
            }

            current = current->next;
        }
        if (fptr)
        {
            fclose(fptr);
        }
    }
    if (file_path)
    {
        free(file_path);
    }
}

/**
 * Function that write the content of entry_file list into
 * New file with .ent format.
 */
void write2file_ent(entry_file *entry_file_data, char *filename)
{
    FILE *fptr;
    entry_file *current = entry_file_data;
    char *current_address;
    char *file_path = concat(filename, ".ent");
    if (current)
    {
        fptr = fopen(file_path, "w+");
        while (current)
        {
            current_address = dec2base(current->address);
            fprintf(fptr, EXTERNAL_FORMAT_OUT, current->label, current_address);
            if (current_address)
            {
                free(current_address);
            }

            current = current->next;
        }
        if (fptr)
        {
            fclose(fptr);
        }
    }
    if (file_path)
    {
        free(file_path);
    }
}

/**
 * This function will update the entry_file list
 */
void handleEntryFile(entry_file **entry_datafile, symbol_t **label_list, entry_t **entry_list)
{
    entry_t *current = *entry_list;
    symbol_t *current_symbol;
    while (current)
    {
        current_symbol = *label_list;
        while (current_symbol)
        {
            if (!strcmp(current_symbol->name, current->label))
            {
                addTo_EntryFile(entry_datafile, current_symbol->name, current_symbol->address);
            }
            current_symbol = current_symbol->next;
        }
        current = current->next;
    }
}

/**
 * SecondPass function to update all unknown labels in FirstPass
 */
void secondPass(FILE *fptr, mem_wt **CMD_LIST, symbol_t **LABEL_LIST, entry_t **ENTRY_LIST, extern_t **EXTERN_LIST, entry_file **ENTRY_FILE, extern_file **EXTERN_FILE)
{
    mem_wt *current = *CMD_LIST;
    char *line;
    char *operand1 = NULL, *operand2 = NULL;
    int isLabel = 0;
    /*
    int result1, result2;
    char *current_entry;
    int label_address = 0;
    */
    while (!feof(fptr))
    {
        /* Get a line from the file */
        line = getLinefromFile(fptr);
        /* Format the line - remove space, etc.. */
        format_line(line);
        if (checkSymbol(line))
        {
            isLabel = 1;
        }
        else
        {
            isLabel = 0;
        }
        operand1 = getOperand1_Label(line, isLabel);
        operand2 = getOperand2_Label(line, isLabel);
        formatOperand(&operand1);
        formatOperand(&operand2);
        /* If sentence is command */
        if (get_sentence_type(line, isLabel) == 4)
        {
            if (isOperand_external(operand1, *EXTERN_LIST))
            {
                while (current && (current->value != 0))
                {
                    current = current->next;
                }
                if (current)
                {
                    current->value = 1;
                    addTo_ExternFile(EXTERN_FILE, operand1, current->address);
                }
            }
            else
            {
                if (findSymbol_Address(*LABEL_LIST, operand1) >= 0)
                {
                    while (current && (current->value != 0))
                    {
                        current = current->next;
                    }
                    if (current)
                    {
                        current->value = (findSymbol_Address(*LABEL_LIST, operand1) << 2) + 2;
                    }
                }
            }
            if (isOperand_external(operand2, *EXTERN_LIST))
            {
                while (current && (current->value != 0))
                {
                    current = current->next;
                }
                if (current)
                {
                    current->value = 1;
                    addTo_ExternFile(EXTERN_FILE, operand2, current->address);
                }
            }
            else
            {

                if (findSymbol_Address(*LABEL_LIST, operand2) >= 0)
                {
                    while (current && (current->value != 0))
                    {
                        current = current->next;
                    }
                    if (current)
                    {
                        current->value = (findSymbol_Address(*LABEL_LIST, operand2) << 2) + 2;
                    }
                }
            }
        }
        if (line)
        {
            free(line);
        }
        if (operand1)
        {
            free(operand1);
        }
        if (operand2)
        {
            free(operand2);
        }
    }
    handleEntryFile(ENTRY_FILE, LABEL_LIST, ENTRY_LIST);
}