#ifndef IS_MACRO_H_
#define IS_MACRO_H_
#include "header.h"
#define BUFFER_SIZE 1000
struct m_list
{
    char *macro_name;
    char *macro_content;
    struct m_list *next;
};
typedef struct m_list macro_list;

/**
 * @brief Function to remove all unneeded spaces
 * 
 * @param line Current line pointer
 * @return char* New formated line
 */
char *remove_spaces(char *line);

/**
 * @brief Get the macro name object
 * 
 * @param current_line Pointer to current line
 * @return char* Pointer to macro new
 */
char *get_macro_name(char *current_line);

/**
 * @brief Function to handle macro
 * 
 * @param line Pointer to ine
 * @param find_word Word to find
 * @return int 1 if word exists, 0 otherwise.
 */
int handle_macro(char *line, char *find_word);

/**
 * @brief Function to add lines to macro content until reach endmacro
 * 
 * @param macro_content Current macro content
 * @param new_content New content to append
 * @return char* Pointer of new content
 */
char *append_macro_content(char *macro_content, char *new_content);

/**
 * @brief Function to add a new macro to the macro_list
 * 
 * @param macro_name Macro name
 * @param macro_content Macro content
 * @param macro_table Pointer to macro_list head
 */
void add_new_macro(char *macro_name, char *macro_content, macro_list **macro_table);

/**
 * @brief Function to free all memory allocated to the macro_table list
 * 
 * @param macro_table Pointer to macro_table list head.
 */
void free_macro_list(macro_list **macro_table);

/**
 * @brief Function to replace all 'oldWord' occurrence to the new 'newWord' 
 * 
 * @param str Replace all occurences of oldWord with newWord
 * @param oldWord oldWord to replace
 * @param newWord newWord to replace to
 */
void replaceAll(char *str, const char *oldWord, const char *newWord);

/**
 * @brief Function to spread all macros from .as format to .am format
 * 
 * @param file_path Path to the file
 * @return int 
 */
int spread_macro(char *file_path);

#endif
