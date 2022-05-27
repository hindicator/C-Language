/*
    Maman 11
    Program to calculate the scalar product of two given vectors
    Name    :   Gal Hindi
    ID      :   318248002
*/
#include <stdio.h>      /* imported for printf/scanf */
#include <stdlib.h>     /* imported for calloc */
#include <string.h>
#include <ctype.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))
#define MAX_NUMBER_SIZE 10

void tablePrint(int v1[], int v2[], int j, int k);
void pprint(int v[], int n, int max_length);
int * scalar_result(int v1[], int v2[], int j, int k);
int scalar_product(int v1[], int v2[], int n);

int main()
{
    int *v1, *v2;
    char num[MAX_NUMBER_SIZE];
    int k, j, n;
    int x;
    char c;
    int isInsideNum = 0;
    int endProgram = 0;
    printf("Welcome to my scalar program,\n");
    printf("This program calculate the scalar product of two given vectors.\n");
    printf("Enter vector with spaces between every element, at the end of the vector write ';'\nExample :\n1 12 -33 14; -11 -1 11 1;\n");

    while(!endProgram)
    {
        printf("Please enter vector length : ");
        scanf("%d", &n);
        printf("%d\n", n);

        v1 = (int*)calloc(n, sizeof(int));
        v2 = (int*)calloc(n, sizeof(int));

        k = 0;
        j = 0;
        memset(num,0,strlen(num));
        printf("Please enter first vector : \n");
        while( (c = getchar()) != EOF )
        {
            if( c == ';' )
            {
                if(isInsideNum)
                {
                    if(k == n)
                    {
                        printf("Error, Vector length too long, exiting...\n");
                        exit(0);
                    }
                    x = atoi(num);
                    v1[k] = x;
                    k++;
                    memset(num,0,strlen(num));
                    c = getchar();
                    isInsideNum = 0;
                    if(k > 0) /* For safety against bad input */
                    {
                        break;
                    }
                }
            }
            else if( c == ' ' )
            {
                if(isInsideNum)
                {
                    if(k == n)
                    {
                        printf("Error, Vector length too long, exiting...\n");
                        exit(0);
                    }
                    x = atoi(num);
                    v1[k] = x;
                    k++;
                    memset(num,0,strlen(num));
                }
                isInsideNum = 0;
            }
            else
            {
                if(c == '-' || isdigit(c) )
                {
                    strncat(num, &c, 1);
                    isInsideNum = 1;
                }  
            }
        }
        printf("Please enter second vector : \n");
        while( (c = getchar()) != EOF )
        {
            if( c == ';' )
            {
                if(isInsideNum)
                {
                    if(j == n)
                    {
                        printf("Error, Vector length too long, exiting...\n");
                        exit(0);
                    }
                    x = atoi(num);
                    v2[j] = x;
                    j++;
                    memset(num,0,strlen(num));
                    c = getchar();
                    isInsideNum = 0;
                    if(j > 0) /* For safety against bad input */
                    {
                        break;
                    }
                }
            }
            else if( c == ' ' )
            {
                if(isInsideNum)
                {
                    if(j == n)
                    {
                        printf("Error, Vector length too long, exiting...\n");
                        exit(0);
                    }
                    x = atoi(num);
                    v2[j] = x;
                    j++;
                    memset(num,0,strlen(num));
                }
                isInsideNum = 0;
            }
            else
            {
                if(c == '-' || isdigit(c) )
                {
                    strncat(num, &c, 1);
                    isInsideNum = 1;
                }  
            }
        }
        memset(num,0,strlen(num));
        tablePrint(v1, v2, j, k);
        free(v1);
        free(v2);
        printf("Enter 1 to Retry or 0 Quit :\n");
        scanf("%s", num);
        if( 1 != atoi(num) )
        {
            endProgram = 1; /* Exit program */
        }

    }
    printf("Thanks for playing!\n");
    return 0;
}

void tablePrint(int v1[], int v2[], int j, int k)
{
    int *result = scalar_result(v1, v2, j, k);
    int digitCount;
    int i;
    printf("================================================================================\n");
    printf("v1\t->\t| ");
    pprint(v1, k, j);
    printf("\t\t");
    for(i = 0; i < MAX(j, k); i++)
    {
        printf("%*c", 3, ' ');
        printf("*");
        printf("%*c", 3, ' ');
    }
    printf("\nv2\t->\t| ");
    pprint(v2, j, k);
    printf("\t\t");
    for(i = 0; i < MAX(j, k); i++)
    {
        printf("%*c", 3, ' ');
        printf("=");
        printf("%*c", 3, ' ');
    }
    printf("\n");
    /* scalar_product(v1, v2, MIN(j,k)); */
    printf("result\t->\t| ");
    pprint(scalar_result(v1, v2, j, k), j, k);
    printf("\t\t");
    digitCount = MAX(j, k);
    while(digitCount > 0)
    {
        printf("=======");
        digitCount--;
    }
    printf("\n");
    printf("The scalar product is : ");
    for(i = 0; i < MAX(j, k) - 1; i++)
    {
        printf("%d + ", result[i]);
    }
    printf("%d = %d\n", result[MAX(j, k) - 1], scalar_product(v1, v2, MIN(j,k)));
    printf("================================================================================\n");
}

void pprint(int v[], int j, int k)
{
    int noMore = 0;
    int i = 0;
    for(i = 0; i < MAX(j, k); i++)
    {
        if(i >= j)
        {
            printf("%4d | ", noMore);
        }
        else
        {
            printf("%4d | ", v[i]);
        }
    }
    printf("\n");
}

int scalar_product(int v1[], int v2[], int n)
{
    int sum = 0;
    int i;
    for(i = 0; i < n; i++){
        sum += v1[i] * v2[i];
    }
    return sum;
}

int *scalar_result(int v1[], int v2[], int j, int k)
{
    int i;
    int *result =  malloc(MAX(j, k) * sizeof(int));
    for(i = 0; i < MAX(j, k); i++)
    {
        if(i >= k)
        {
            v1[i] = 0;
        }
        if(i >= j)
        {
            v2[i] = 0;
        }
        result[i] = v1[i] * v2[i];
    }
    return result;
}