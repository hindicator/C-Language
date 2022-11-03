#ifndef _IS_SYMBOL_H
#define _IS_SYMBOL_H
#include "symbol.h"
#endif

#define _IS_DATA_H
/* Linked-List to store all entry labels */
struct entry_node
{
    char *label;
    struct entry_node *next;
};
typedef struct entry_node entry_t;

struct entry_data
{
    char *label;
    int address;
    struct entry_data *next;
};
typedef struct entry_data entry_file;
/*===============================================*/

/* Linked-List to store all extern labels */
struct extern_node
{
    char *label;
    struct extern_node *next;
};
typedef struct extern_node extern_t;

struct extern_data
{
    char *label;
    int address;
    struct extern_data *next;
};
typedef struct extern_data extern_file;

/* Linked-List to store all data with value of data_chain, i.e. all variable data */
struct data_order {
    int value;
    int address;
    struct data_order *next;
};
typedef struct data_order data_t;

struct data_image {
    data_t *data_chain;
    struct data_image *next;
};
typedef struct data_image data_list;


/**
 * @brief Get the Current label object
 *
 * @param line Pointer to current line
 * @return char* Pointer to label
 */
char *getCurrent_label(char *line);

/**
 * @brief Function that returns the type of instruction
 *
 * @param line pointer to current line string
 * @param isLabel int, is label exist or not
 * @return int - index of instruction [0-4],
 *          -1 if instruction is not valid.
 */
int checkInstruction(char *line, int isLabel);

/**
 * @brief Get the String data object
 *
 * @param line pointer to current line
 * @return data_t* pointer to new data node
 */
data_t *getString(char *line, int line_num);

/**
 * @brief Get the Data data object
 *
 * @param line pointer to current line
 * @return data_t* pointer to new data node
 */
data_t *getData(char *line, int line_num);

/**
 * @brief Get the Struct data object
 *
 * @param line pointer to current line
 * @return data_t* pointer to new data node
 */
data_t *getStruct(char *line, int line_num);

/**
 * @brief Function to add a new entry
 *
 * @param head Address of entry_list
 * @param label Label of new entry
 */
void addEntry(entry_t **head, char *label);

/**
 * @brief Function to add entry to the entryfile_list
 * 
 * @param head Pointer to the entry_file_list head
 * @param label Lable of the entry
 * @param address Address of the entry
 */
void addTo_EntryFile(entry_file **head, char *label, int address);

/**
 * @brief Function to add a new extern
 *
 * @param head Address of extern_list
 * @param label Label of new extern
 */
void addExtern(extern_t **head, char *label);

/**
 * @brief Function to add extern to the externfile_list
 * 
 * @param head Pointer to the extern_file_list head
 * @param label Lable of the extern
 * @param address Address of the extern
 */
void addTo_ExternFile(extern_file **head, char *label, int address);

/**
 * @brief Function to add a new value to the data_chain
 * 
 * @param head Pointer to datachain head
 * @param value int, New value to add
 */
void add2DataChain(data_t **head, int value);

/**
 * @brief Function to add a new node into the data list
 *
 * @param head data_list **head, address of data_list head pointer.
 * @param node data_t *node, pointer to new data node.
 */
void add2DataList(data_list **head, data_t *node);

/**
 * @brief Function to handle the instruction
 *
 * @param line Pointer to current line
 * @param line_num The number of current line
 * @param isLabel Number, 0 if no label, 1 if label exist
 * @param DATA_LIST Address of data_list
 * @param ENTRY_LIST Address of entry_list
 * @param EXTERN_LIST Address of extern_list
 * @return int
 */
int handleInstruction(char *line, int line_num, int isLabel, data_list **DATA_LIST, entry_t **ENTRY_LIST, extern_t **EXTERN_LIST);

/**
 * @brief Function to return the data-counter
 * 
 * @param data_list data_list head
 * @return int Number of data words
 */
int getDC(data_list *data_list);

/**
 * @brief Function to free data_list
 * 
 * @param head Pointer to data_list head
 */
void freeData_List(data_list **head);

/**
 * @brief Function to free extern_list
 * 
 * @param head Pointer to extern_list head
 */
void freeExtern_List(extern_t **head);

/**
 * @brief Function to free entry_list
 * 
 * @param head Pointer to entry_list head
 */
void freeEntry_List(entry_t **head);

/**
 * @brief Function to free entry_file list
 * 
 * @param head Pointer to entry_file head
 */
void free_EntryFile(entry_file **head);

/**
 * @brief Function to free extern_file list
 * 
 * @param head Pointer to extern_file head
 */
void free_ExternFile(extern_file **head);

