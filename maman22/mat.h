#include <stdio.h>  /* printf */
#include <ctype.h>  /* isalpha, isdigit */
#include <stdlib.h> /* calloc, atoi */
#include <string.h> /* strcmp */

#define MAX_LINE_LEN 100 /* Max length of line per command */
#define COMMAND_NUM 8    /* Number of available commands */
#define MAX_COMMAND_SIZE 20
#define MY_MAX_NUM_LEN 50
#define NUM_OF_MATS 6
#define MAX_WORD_SIZE 20
#define MAX_WORD_IN_LINE 50
#define MAX_LINE_SIZE 100
#define IS_COMMA(ch) ch == ',' ? 1 : 0
/*The mat struct*/
typedef struct
{
    double theArr[4][4];
} mat;

/* ==================== Function for main ==================== */
void initilize_mat(mat **mat_arr);

/* ==================== Functions for mat.c ==================== */
/* Read mat */
void read_mat(mat *a, double *vectors);
/* Print mat */
void print_mat(mat *a);
/* Add mat */
void add_mat(mat *a, mat *b, mat *c);
/* Sub mat */
void sub_mat(mat *a, mat *b, mat *c);
/* Mul mat */
void mul_mat(mat *a, mat *b, mat *c);
/* Mul scalar */
void mul_scalar(mat *a, double scalar, mat *c);
/* Trans mat */
void trans_mat(mat *a, mat *b);
/* Stop program */
void stop();

/* ==================== Functions for input.c ==================== */
/* Return array of words from the splited line */
char **split_line(char *line);
/* Free words pointers and pointer of words */
void free_word_arr(char **word_array);
/* Return all line from input */
char *get_input();
/* Format Line - Remove all white chars from string after command */
void format_line(char **str);
/* Return int value 0 - 5 based on string matrix index */
int mat_2_num(char *mat_num);
/* Handle command of the input line */
void handle_command(char *line, mat **matrix_arr);
/* Return int - presenting the number of command*/
int command_num(char *first_word);
/* Return pointer of vectors */
double *read_vectors(char *p);
/* Prompt the user for - ready to receive data */
void user_promt();

int isValid_command(int numOfArgs, ...);
int isValid_Commas(char **p);