/*
    Maman 23
    Program that return AND operator between all given numbers from input.
    Name    :   Gal Hindi
    ID      :   318248002
*/
#include <stdio.h>      /* printf */
#include <stdarg.h>     /* va_list, va_arg, va_end */
#include <time.h>       /* srand (for random) */
#include <stdlib.h>     /* malloc, recalloc */

/**
 * Function for prettier print of calculations and result.
 * Print Decimal value, Hex value and all bits value.
 */
void pprint(int n)
{
    int tmp = n;
    int c, k;
    printf("Dec: %10u , HEX: %10x \t->\t| ", n, n);
    k = tmp >> 1;
    for (c = 0; c < 32; c++)
    {
        if (k & 1)
            printf("1 | ");
        else
            printf("0 | ");
        k >>= 1;
    }
    printf("\n");
}
/**
 * Function to compare undefined numbers of (unsigned int) parameters.
 * Return and between the bits of all numbers.
 */
int compareBits(int num_args, ...)
{
    va_list args;
    unsigned int result;
    int i, tmp;
    va_start(args, num_args);
    result = ~(0&result); /* Initilize result - all bits with value 1 */
    for (i = 0; i < num_args; i++)
    {
        tmp = va_arg(args, unsigned int);
        pprint(tmp);
        result = result & tmp;
    }
    va_end(args);
    return result;
}

/**
 * Function that generate a random unsigned integer.
 * Return unsigned int
 */
unsigned int getRandom()
{
    return (unsigned int)rand();
}

int main()
{
    int result1, result2, result3, result4;
    srand(time(NULL));
    printf("Welcome to find bits Program,\n");
    result1 = compareBits(4, getRandom(), getRandom(), getRandom(), getRandom());
    printf("Result :\n");
    pprint(result1);
    printf("=================================================================================================================================================================================\n");
    result2 = compareBits(4, getRandom(), getRandom(), getRandom(), getRandom());
    printf("Result :\n");
    pprint(result2);
    printf("=================================================================================================================================================================================\n");
    result3 = compareBits(4, getRandom(), getRandom(), getRandom(), getRandom());
    printf("Result :\n");
    pprint(result3);
    printf("=================================================================================================================================================================================\n");
    result4 = compareBits(4, getRandom(), getRandom(), getRandom(), getRandom());
    printf("Result :\n");
    pprint(result4);
    printf("=================================================================================================================================================================================\n");

    return 0;
}