/* Read input from user until EOF */
char* readText();
/* Print the input in styled form */
void tablePrint(char *input, int _index);
/* 
    Print sideBorder of styled form 
    tablePrint private function 
*/
void sideBorder(int current_column);
/* 
    Print heightBorder of styled form 
    tablePrint private function 
*/
void heightBorder();
/* Read char pointer length from first 10 characters and return int */
int my_itof(char *str);
/* Convert int to pointer of characters */
char *my_itoa(int num, char *str);