/*
    Maman 11
    Program to count the number of parallel bits of two given numbers
    Name    :   Gal Hindi
    ID      :   318248002
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

void tablePrint(int x1, int x2);
void pprint(int n);
int getNumOfDigits(int n);
int compareBits(unsigned long x, unsigned long y);

int main()
{
    int x1 = 0, x2 = 0;
    int isDone = 1;
    printf("Welcome to find bits Program,\n");
    printf("This program calculate the number of parallel bits of two given numbers.\n");
    while (isDone)
    {
        printf("Please enter first number : \n");
        scanf("%d", &x1);
        printf("Please enter second number : \n");
        scanf("%d", &x2);
        
        tablePrint(x1, x2);
        printf("Enter 1 to try again or 0 to quit : \n");
        scanf("%d", &isDone);
    }
    printf("Thanks for playing!\n");
    return 0;
}

void tablePrint(int x1, int x2)
{
    int digitCount;
    printf("================================================================================\n");
    pprint(x1);
    pprint(x2);
    printf("\t\t");
    digitCount = MAX(getNumOfDigits(x1), getNumOfDigits(x2));
    while(digitCount > 0)
    {
        printf("=====");
        digitCount--;
    }
    printf("\n");
    pprint(x1&x2);
    printf("Total number of parallel bits : %d\n", compareBits(x1,x2));
    printf("================================================================================\n");
}

int getNumOfDigits(int n)
{
    int tmp = n;
    int k = 0;
    while(tmp > 0)
    {
        tmp >>= 1;
        k++;
    }
    return k-1;
}

void pprint(int n)
{
    int tmp = n;
    int c, k;
    printf("%d\t->\t| ", n);
    for (c = getNumOfDigits(n); c >= 0; c--)
    {
        k = tmp >> c;

        if (k & 1)
            printf("1 | ");
        else
            printf("0 | ");
    }
    printf("\n");
}

int compareBits(unsigned long x, unsigned long y)
{
    int count0 = 0, count1 = 0;
    while(x > 0 && y > 0)
    {
        /* If current bit is 1 on both */
		if (x & 1 && y & 1)
        {
			count1++;
		}

		/* If current bit is 0 on both*/
		else
        {
			count0++;
		}
		x = x >> 1;
        y = y >> 1;
    }
    return count1;
}