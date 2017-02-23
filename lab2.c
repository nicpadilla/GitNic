#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
unsigned long factorial(unsigned short);
void leap(unsigned int);
void max(float, float);
void arithConvert(unsigned short);
void bitConvert(unsigned short);
int main()
{
    char selection = 'a', choice = 'd';
    unsigned short num, dec;
    unsigned int year;
    float input1, input2;
    int num1, num2, i=0;
    while(1)
    {
        printf("\nSelect one of the following:\n"
            "1. (f)actorial of a number\n"
            "2. (l)eap year or not\n"
            "3. (m)aximum\n"
            "4. (d)ivision of two numbers\n"
            "5. (c)onvert decimal to binary\n"
            "6. (e)xit\n");
        if(i!=0) while(getchar() != '\n');
        selection = getchar();
        i++;
        switch(selection) //checks which operator was selected
        {
            case 'f':
                printf("Enter the number you want a factorial of: ");
                scanf("%u", &num);
                for(int i=0; num > 12; i++)
                {
                    if(i > 1)
                    {
                        printf("\nToo many incorrect entries.\n");
                        return 0;
                    }
                    printf("\nError, output out of range, enter a number <= 12: ");
                    scanf("%u", &num);

                }

                printf("%d! = %lu\n", num, factorial(num));
                break;
            case 'l':
                printf("Enter the year: ");
                scanf("%u", &year);
                leap(year);
                break;
            case 'm':
                printf("Enter your first number: ");
                scanf("%f", &input1);
                printf("\nEnter your second number: ");
                scanf("%f", &input2);
                (input1 > input2) ? printf("%.4f is larger than %.4f\n", input1, input2) : (input1 == input2) ? printf("Numbers are equal.\n") : printf("%.4f is larger than %.4f\n", input2, input1);
                break;
            case 'd':
                printf("Enter your first integer: ");
                scanf("%d", &num1);
                printf("\nEnter your second integer: ");
                scanf("%d", &num2);
                (num2 == 0) ? printf("Divided by zero.\n") : printf("%d / %d = %f\n", num1, num2, (float) num1/num2);
                break;
            case 'e':
                return 0;
                break;
            case 'c':
                printf("Enter your decimal number: ");
                scanf("%u", &dec);
                /*while(dec > 65535)
                {
                    printf("Enter a number < 65535.\n");
                    scanf("%u", &dec);
                }*/
                printf("Which method?\n"
                    "1. (a)rithmetic\n"
                    "2. (b)itwise operators\n");
                scanf(" %c", &choice);
                if(choice == 'a') arithConvert(dec);
                else if(choice == 'b') bitConvert(dec);
                else 
                {
                    printf("Error.\n");
                    return 0;
                }
                break;
            default:
                printf("Error, incorrect input.\n");
        }
    }
    return 0;
}

unsigned long factorial(unsigned short num)
{
    if(num == 0) return 1;
    return (num * factorial(num - 1));
}

void leap(unsigned int year)
{
    if(year % 4 == 0)
        if(year % 100 == 0)
            if(year % 400 == 0) printf("%u is a leap year!\n", year);
            else printf("%u is not a leap year!\n", year);
        else printf("%u is a leap year!\n", year);
    else printf("%u is not a leap year!\n", year);
}

void arithConvert(unsigned short dec)
{
    int remainder, length;
    long bin = 0, n = 1;
    while(dec != 0)
    {
        remainder = dec % 2; //gives either 1 or 0
        dec /= 2;
        bin += (remainder*n);
        n *= 10;
    }
    /*if(bin != 0) length = floor(log10(abs(bin))) + 1; //checks length of final binary number
    for(1;length < 16; length++ ) //adds preceding zeros if necessary
    {
        printf("0");
    }*/
    printf("%ld", bin);
}

void bitConvert(unsigned short dec)
{
    unsigned short mask=32768; //1000000000000000
    while(mask > 0)
    {
        if((dec & mask) == 0) printf("0"); //checks each bit in 'dec', sets bits in output
        else printf("1");
        mask = mask >> 1; //shifts bits by one in mask to check next bit of 'dec'
    }
}