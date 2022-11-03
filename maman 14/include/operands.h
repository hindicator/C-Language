#ifndef _IS_CMD_OP_H
#define _IS_CMD_OP_H
#include "input.h"
#endif

/**
 * @brief Get the Register num object
 * 
 * @param word Current Operand label
 * @return int number of register
 */
int getRegister_num(char *word);

/**
 * @brief Get the Operand num object
 * 
 * @param word Current Operand label
 * @return int Number in the operand
 */
int getOperand_num(char *word);

/**
 * @brief Get the Struct address object
 * 
 * @param word Current Operand label
 * @return int The address in the struct, i.e. S1.2, 2 is the address
 */
int getStruct_address(char *word);

/**
 * @brief Function to concatinate two strings
 * 
 * @param s1 String 1
 * @param s2 String 2
 * @return char* String1 with string2 appended to it
 */
char *concat(const char *s1, const char *s2);

/**
 * @brief Function to convert decimal base to 32base
 * 
 * @param n Decimal number
 * @return char* word in 32base
 */
char *dec2base(int n);


void formatOperand(char **operand);

/**
 * @brief Get the Operand1  Label object
 * 
 * @param line Pointer to current line
 * @param isLabel 1 if label exists, 0 otherwise
 * @return char* Pointer to the operand1 label
 */
char *getOperand1_Label(char *line, int isLabel);

/**
 * @brief Get the Operand2 Label object
 * 
 * @param line Pointer to current line
 * @param isLabel 1 if label exists, 0 otherwise
 * @return char* Pointer to the operand2 label
 */
char *getOperand2_Label(char *line, int isLabel);

/**
 * @brief Function to return the addressing type of operand1
 * 
 * @param word Pointer to Operand label
 * @param isLabel int, 1 if label exists, 0 otherwise.
 * @param LABEL_LIST Pointer to label_list head.
 * 
 * @return 0 if addressing is immediate
 * @return 1 if addressing is straight
 * @return 2 if addressing is access a label
 * @return 3 if addressing is access to register
 * @return -1 if addressing type is invalid.
 */
int getOperand_Type(char *word, symbol_t *LABEL_LIST);

/**
 * @brief Function to return the addressing type of operand1
 * 
 * @param line Pointer to Operand label
 * @param LABEL_LIST Pointer to label_list head.
 * 
 * @return 0 if addressing is immediate
 * @return 1 if addressing is straight
 * @return 2 if addressing is access a label
 * @return 3 if addressing is access to register
 * @return -1 if addressing type is invalid.
 */

/**
 * @brief Function that check if operand is external label
 * 
 * @param label The label to check if it's external
 * @param extern_list Pointer to external_list head
 * @return int 1 if true, 0 otherwise.
 */
int isOperand_external(char *label, extern_t *extern_list);

/**
 * @brief Function that check if operand is entry label
 * 
 * @param label The label to check if it's entry
 * @param entry_list Pointer to entry_list head
 * @return int 1 if true, 0 otherwise.
 */
int isOperand_entry(char *label, entry_t *entry_list);