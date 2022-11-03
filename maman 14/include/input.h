#ifndef IS_INPUT_H_
#define IS_INPUT_H_
#include "header.h"
#include "macro.h"
#include "commands.h"

#ifndef _IS_OPERANDS_H
#define _IS_OPERANDS_H
#include "operands.h"
#endif

#ifndef _IS_HF_OP_H
#define _IS_HF_OP_H
#include "handleFiles.h"
#endif


/**
 * @brief Get the File object
 * @param file_name path to file
 * @return FILE* if file has been found, return null if file not exist.
 * @return null if file not exist.
 */
FILE *getFile(char *file_name);

/**
 * @brief Function the get line from current file.
 * @param fptr file pointer
 * @return string pointer of line.
 * @return NULL if reached EOF.
 */
char *getLinefromFile(FILE *fptr);

/**
 * @brief Function to format current line in pretty way and easy to process.
 * @param line Current line
 * Change current line pointer to the formated line
 */
void format_line(char *line);

/**
 * @brief Function to return type of sentence.
 * @param line Pointer to line
 * @param isLabel If label exist on this line - 1, otherwise 0.
 * @return Sentence type number
 * @note returns 1 if empty sentence
 * @note returns 2 if comment sentence
 * @note returns 3 if instruction sentence
 * @note returns 4 if command sentence
 * @note returns 0 if not valid
 */
int get_sentence_type(char *line, int isLabel);

/**
 * @brief Function to return command type (0-15)
 * @return number between 0-15 relative to command num
 * @return -1 if line is not a command
 */
int get_command_type(char *line, int isLabel);

/**
 * @brief Function to check if line is instruction.
 * @return 1 if line is instruction.
 * @return 0 if not.
 */
int isInstruction(char *line, int isLabel);

/**
 * @brief Get the Current Address of memory_word
 * 
 * @param cmd_list word_list
 * @return int The address of the memory word.
 */
int getCurrentAddress(mem_wt *cmd_list);

/**
 * @brief Add new memory word to word_list
 * 
 * @param cmd_list list of memory words
 * @param DATA_LIST list of data
 */
void add_new_data(mem_wt **cmd_list, data_list **DATA_LIST);

/**
 * @brief Function to handle sentence
 * @return 1 if handled successfuly
 * @return 0 if failed
 */
int handleSentence(char *line, int line_num, int isLabel, data_list **DATA_LIST, symbol_t **LABEL_LIST, mem_wt **cmd_list, entry_t **entry_list, extern_t **extern_list);

#endif