#ifndef _IS_SYMBOL_H
#define _IS_SYMBOL_H
#include "symbol.h"
#endif
#ifndef _IS_DATA_H
#define _IS_DATA_H
#include "data.h"
#endif

/**
 * @brief IsBitSet - Macro to return if the n bit of val is on or off
 * 
 */
#define IsBitSet(val, bit) ((val) & (1 << (bit))) ? 1 : 0
struct mem_word
{
    unsigned int opcode4 : 1;
    unsigned int opcode3 : 1;
    unsigned int opcode2 : 1;
    unsigned int opcode1 : 1;
    unsigned int op_source2 : 1;
    unsigned int op_source1 : 1;
    unsigned int op_dest2 : 1;
    unsigned int op_dest1 : 1;
    unsigned int ARE2 : 1;
    unsigned int ARE1 : 1;

    int value;
    int address;

    struct mem_word *next;
};
typedef struct mem_word mem_wt;

/**
 * @brief Function to add memory word into mem_list
 * 
 * @param head Address of mem_list
 * @param num Number to add
 */
void addMemword(mem_wt **head, int num);

/**
 * @brief Get the Mem Word object
 * 
 * @param opcode Number of command [0-15]
 * @param op_source Operade source type
 * @param op_dest Operand destination type
 * @param ARE ARE type
 * @return int New memory word value
 */
int getMemWord(int opcode, int op_source, int op_dest, int ARE);

/**
 * @brief Function to free all nodes in command_list
 * 
 * @param head Pointer to command_list head.
 */
void freeCommand_List(mem_wt **head);

/**
 * @brief Function to get the total length of memory words.
 * 
 * @param head command_list head
 * @return int Total memory words length.
 */
int getCommands_Len(mem_wt *head);

/**
 * @brief Function to handle a new command
 * 
 * @param line Pointer to the line
 * @param isLabel 1 If label exist on line, 0 otherwise
 * @param label_list Pointer to label_list head
 * @param cmd_list Pointer to cmd_list head
 * @param entry_list Pointer to entry_list head
 * @param extern_list Pointer to extern_list head
 * @return int 
 */
int handleCommand(char *line, int isLabel, symbol_t **label_list, mem_wt **cmd_list, entry_t **entry_list, extern_t **extern_list);