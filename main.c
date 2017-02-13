#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define PI 3.14159265358979323846
//With math.h, Pi is already pre-defined as M_PI, so it is not necessary
int main(int argc, char** argv) {
    float num, cprice, sprice, op1, op2, output; //cost price and sell price
    char op; //selected operation
    //Part 1
    printf("Part 1: Area of circle\n\nEnter the radius of your circle: ");
    scanf("%f", &num);
    printf("\nThe area of your circle is : %f\n\n", M_PI*pow(num,2));
    //Part 2
    printf("Part 2: Sales Profit\n\nEnter the cost of your item: ");
    scanf("%f", &cprice);
    printf("\nEnter the selling price of your item: ");
    scanf("%f", &sprice);
    if(cprice > sprice) printf("\nYou've lost $%.2f on this transaction.\n\n", cprice - sprice);
    else printf("\nYou've earned $%.2f on this transaction\n\n", sprice - cprice);
    //Part 3
    printf("Part 3: Calculator:\n\nEnter your first operand: ");
    scanf("%f", &op1);
    printf("\nEnter your second operand: ");
    scanf("%f", &op2);
    printf("\nSelect on of the following operations: '+', '-', '*', '/'\n");
    op = getchar();
    op = getchar(); //This is done twice because to account for '\n'
    switch(op) //checks which operator was selected
    {
        case '+':
            printf("%.2f + %.2f = %.2f\n",op1, op2, op1 + op2);
            break;
        case '-':
            printf("%.2f - %.2f = %.2f\n",op1, op2, op1 - op2);
            break;
        case '*':
            printf("%.2f * %.2f = %.2f\n",op1, op2, op1 * op2);
            break;
        case '/':
            if(op2 == 0) 
            {
                printf("Error! Divided by zero\n");
                return 0;
            }
            printf("%.2f / %.2f = %.2f\n",op1, op2, (op1 / op2));
            break;
        default:
            printf("Error! Wrong format.\n");
    }
    
    return (EXIT_SUCCESS);
}

