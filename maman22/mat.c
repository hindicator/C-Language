#include "mat.h"
#define MY_MAX_NUM_LEN 50
/* Contain all available commands */
const char *commandNames[COMMAND_NUM] = {"read_mat", "print_mat", "add_mat", "sub_mat", "mul_mat", "mul_scalar", "trans_mat", "stop"};

/* read_mat - store vectors in mat a */
void read_mat(mat *a, double *vectors)
{
    int i, j;
    int current_vector = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            a->theArr[i][j] = vectors[current_vector++];
        }
    }
}

/* Print mat a */
void print_mat(mat *a)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%8.02f ", a->theArr[i][j]);
        }
        printf("\n");
    }
}
/* Add mat a and mat b and store in mat c*/
void add_mat(mat *a, mat *b, mat *c)
{
    mat tmp;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp.theArr[i][j] = a->theArr[i][j] + b->theArr[i][j];
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c->theArr[i][j] = tmp.theArr[i][j];
        }
    }
}
/* Substitute mat b from mat a and store in mat c*/
void sub_mat(mat *a, mat *b, mat *c)
{
    mat tmp;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp.theArr[i][j] = a->theArr[i][j] - b->theArr[i][j];
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c->theArr[i][j] = tmp.theArr[i][j];
        }
    }
}

/* Return scalar_product of mat - v1[row] and v2[column] */
double scalar_result(mat *v1, mat *v2, int row, int column)
{
    int i;
    double result = 0;
    for(i = 0; i < 4; i++)
    {
        result += v1->theArr[row][i] * v2->theArr[i][column];
    }
    return result;
}
/* Store the multiple of mat a and mat b in mat c */
void mul_mat(mat *a, mat *b, mat *c)
{
    mat tmp;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp.theArr[i][j] = scalar_result(a, b, i, j);
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c->theArr[i][j] = tmp.theArr[i][j];
        }
    }
}
/* Store the multiple of mat a and scalar in mat c */
void mul_scalar(mat *a, double scalar, mat *c)
{
    mat tmp;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp.theArr[i][j] = a->theArr[i][j] * scalar;
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c->theArr[i][j] = tmp.theArr[i][j];
        }
    }
}
/* Transpose mat a and store it in mat b */
void trans_mat(mat *a, mat *b)
{
    mat tmp;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            tmp.theArr[j][i] = a->theArr[i][j];
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            b->theArr[i][j] = tmp.theArr[i][j];
        }
    }
}

















/*
void add_mat(mat *a, mat *b, mat *c)
{
}


void print_mat(mat *a);
void add_mat(mat *a, mat *b, mat *c);
void sub_mat(mat *a, mat *b, mat *c);
void mul_mat(mat *a, mat *b, mat *c);
void mul_scalar(mat *a, double scalar, mat *c);
void trans_mat(mat *a, double scalar, mat *c);
void stop();
*/