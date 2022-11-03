#include "input.h"

symbol_t *LABEL_LIST = NULL;
data_list *DATA_LIST = NULL;
mem_wt *COMMAND_LIST = NULL;
extern_t *EXTERN_LIST = NULL;
entry_t *ENTRY_LIST = NULL;

entry_file *ENTRY_FILE = NULL;
extern_file *EXTERN_FILE = NULL;

int main(int argc, char **argv)
{
    FILE *fptr;
    char *line = NULL;
    char *label;
    int current_file = 1, isLabel = 0, line_num = 1;
    char *am_format = NULL;
    /* Validate that the user entered atleast one file - otherwise print UsageExample */
    if (argc <= 1)
    {
        fprintf(stderr, "%s%s[ERROR] %sPlease enter a filename\nExample - ./program test/ps1\n", RED, BOLD, BLANK);
    }
    /* while not finished to compile all files */
    while (current_file < argc)
    {
        initAllLists();
        am_format = concat(argv[current_file], ".am");
        line_num = 1;

        spread_macro(argv[current_file]);
        fptr = getFile(am_format);
        while (!feof(fptr))
        {
            /* Get a line from the file */
            line = getLinefromFile(fptr);
            /* Format the line - remove space, etc.. */
            format_line(line);
            /* If symbol exist, add it to the symbol_list */
            if (checkSymbol(line))
            {
                label = getSymbol(line);
                addSymbol(&LABEL_LIST, label, getCurrentAddress(COMMAND_LIST));
                isLabel = 1;
            }
            else
            {
                isLabel = 0;
            }
            handleSentence(line, line_num, isLabel, &DATA_LIST, &LABEL_LIST, &COMMAND_LIST, &ENTRY_LIST, &EXTERN_LIST);
            line_num++;
            if (line)
            {
                free(line);
            }
        }
        rewind(fptr);
        secondPass(fptr, &COMMAND_LIST, &LABEL_LIST, &ENTRY_LIST, &EXTERN_LIST, &ENTRY_FILE, &EXTERN_FILE);
        writeAllFiles();
        freeAllLists();
        fprintf(stderr, "%s%s[SUCCESS] %sCompiled File %d - %s successfully!\n", GREEN, BOLD, BLANK, current_file, am_format);
        printf("=========================================\n");
        fclose(fptr);
        if (am_format)
        {
            free(am_format);
        }
        current_file++;
    }
    return 0;
}