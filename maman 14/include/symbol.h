/**
 * @brief Symbol node linked-list
 */
struct symbol_chart
{
    char *name;  /* Name of symbol */
    int address; /* Address of symbol */
    struct symbol_chart *next;
};
typedef struct symbol_chart symbol_t;

/**
 * @brief Function to check if the line first word is a symbol (i.e. MAIN:, LOOP:, ...)
 * 
 * @param line pointer of line
 * @return 1 if symbol exist.
 * @return 0 if symbol not exist.
 */
int checkSymbol(char *line);

/**
 * @brief Function to get the symbol name from line
 * 
 * @param line pointer of line
 * If symbol name is valid :
 * @return pointer to symbol name
 */
char *getSymbol(char *line);

/**
 * @brief Create a symbol node object
 * 
 * @param name name of symbol
 * @param address address of symbol
 * @return symbol_t* - pointer to symbol node
 */
symbol_t *create_symbol_node(char *name, int address);

/**
 * @brief Function to add a new symbol to the symbol_list
 * 
 * @param head Pointer to symbol_list head
 * @param label New label to add
 * @param address Address of the new symbol
 */
void addSymbol(symbol_t **head, char *label, int address);

/**
 * @brief Function to free all nodes in symbol list
 * 
 * @param head Pointer to symbol list head.
 */
void freeSymbol_List(symbol_t **head);

/**
 * @brief Function to return the address of specific symbol
 * 
 * @param label_list The symbol list
 * @param label Label to find
 * @return int Address of the label
 * @return -1 if label ot exist
 */
int findSymbol_Address(symbol_t *label_list, char *label);