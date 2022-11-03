#ifndef _IS_HF_OP_H
#define _IS_HF_OP_H
#include "input.h"
#endif

#define EXTERNAL_FORMAT_OUT "%s\t\t%s\n"
#define OBJECT_FORMAT_OUT "\t%s\t%s\n"

/**
 * @brief Function to write all object file
 * 
 * @param cmd_list Pointer to command_list head
 * @param filename Filename string
 */
void write2file_obj(mem_wt *cmd_list, char *filename, int IC, int DC);

/**
 * @brief Function to write all external content to file
 * 
 * @param extern_file_data Pointer to external_file head
 * @param filename Filename string
 */
void write2file_ext(extern_file *extern_file_data, char *filename);

/**
 * @brief Function to write all entry content to file
 * 
 * @param entry_file_data Poitner to entry_file head
 * @param filename Filename string
 */
void write2file_ent(entry_file *entry_file_data, char *filename);

/**
 * @brief Function to handle entry_file content and update his values
 * 
 * @param entry_datafile Pointer to entry_file head
 * @param label_list Pointer to label_list head
 * @param entry_list Pointer to entry_list head
 */
void handleEntryFile(entry_file **entry_datafile, symbol_t **label_list, entry_t **entry_list);

/**
 * @brief Function to start a second pass which fill the addresses gap.
 * 
 * @param fptr Pointer to macro spreaded file
 * @param CMD_LIST Pointer to command_list head
 * @param LABEL_LIST Pointer to label_list head
 * @param ENTRY_LIST Pointer to entry_list head
 * @param EXTERN_LIST Pointer to extern_list head
 * @param ENTRY_FILE Pointer to entry_file head
 * @param EXTERN_FILE Pointer to extern_file head
 */
void secondPass(FILE *fptr, mem_wt **CMD_LIST, symbol_t **LABEL_LIST, entry_t **ENTRY_LIST, extern_t **EXTERN_LIST, entry_file **ENTRY_FILE, extern_file **EXTERN_FILE);