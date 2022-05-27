#include "mat.h"

int main()
{
    /* All mats */
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    /* Store all mats in matrix_arr */
    mat *matrix_arr[6];
    /* Temp pointer for current line */
    char *line;
    matrix_arr[0] = &MAT_A;
    matrix_arr[1] = &MAT_B;
    matrix_arr[2] = &MAT_C;
    matrix_arr[3] = &MAT_D;
    matrix_arr[4] = &MAT_E;
    matrix_arr[5] = &MAT_F;

    initilize_mat(matrix_arr);

    printf("Welcome to the matrix calculator!\n");
    /* print_mat(&MAT_A);*/
    while (1)
    {
        user_promt();
        line = get_input(); /* get the input line the user entered */
        handle_command(line, matrix_arr);
        if(line)
        {
            free(line);
        }
    }
    return 0;
}
