/**
 * @file header.h
 * @author Gal Hindi
 * @brief Main header file for project - all library includes in here.
 * @version 1.0
 * @date 2022-07-30
 * @copyright Copyright (c) 2022
 *
 */
#ifndef IS_HEADER_H_
#define IS_HEADER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LABEL_MAX_LEN 30
#define WORD_SIZE 20
#define INSTRUCTION_LEN 5
#define COMMAND_LEN 16
#define REGISTER_LEN 8

#define GREEN "\x1b[0;32m"
#define RED "\x1b[0;31m"
#define YELLOW "\x1b[0;33m"
#define BOLD "\x1b[1m"
#define BLANK "\x1b[0m"

/**
 * @brief Macro to increase pointer size
 * @param ptr Pointer to increase size
 * @param size int, increase size to the new size
 * @param type Pointer type - [char / int / double]
 */
#define input_addSize(ptr, size, type)                       \
    {                                                        \
        char *tmp_ptr;                                       \
        size += 10;                                          \
        tmp_ptr = (char *)realloc(ptr, size * sizeof(type)); \
        if (!tmp_ptr)                                        \
        {                                                    \
            printf("Failed allocation memory.\n");           \
            exit(-1);                                        \
        }                                                    \
        ptr = tmp_ptr;                                       \
    }

#define initAllLists()       \
    {                        \
        LABEL_LIST = NULL;   \
        COMMAND_LIST = NULL; \
        DATA_LIST = NULL;    \
        ENTRY_LIST = NULL;   \
        EXTERN_LIST = NULL;  \
        ENTRY_FILE = NULL;   \
        EXTERN_FILE = NULL;  \
    }
#define freeAllLists()                   \
    {                                    \
        freeSymbol_List(&LABEL_LIST);    \
        freeCommand_List(&COMMAND_LIST); \
        freeData_List(&DATA_LIST);       \
        freeEntry_List(&ENTRY_LIST);     \
        freeExtern_List(&EXTERN_LIST);   \
        free_EntryFile(&ENTRY_FILE);     \
        free_ExternFile(&EXTERN_FILE);   \
    }
#define writeAllFiles()                                                                                                       \
    {                                                                                                                         \
        write2file_obj(COMMAND_LIST, argv[current_file], getCommands_Len(COMMAND_LIST) - getDC(DATA_LIST), getDC(DATA_LIST)); \
        write2file_ext(EXTERN_FILE, argv[current_file]);                                                                      \
        write2file_ent(ENTRY_FILE, argv[current_file]);                                                                       \
    }
#define MARK_ERROR(line)                                                         \
    {                                                                            \
        int line_error_index = 0;                                                \
        int line_len = strlen(line);                                             \
        while (line_error_index < line_len)                                      \
        {                                                                        \
            if (((i - line_error_index) <= 5) && ((i - line_error_index) >= -5)) \
            {                                                                    \
                fprintf(stderr, "%s%s_", RED, BOLD);                             \
            }                                                                    \
            else                                                                 \
            {                                                                    \
                fprintf(stderr, " ");                                            \
            }                                                                    \
            line_error_index++;                                                  \
        }                                                                        \
        fprintf(stderr, "%s\n", BLANK);                                          \
    }

#endif