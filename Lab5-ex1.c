#include <stdio.h>
#include <stdlib.h> 
int main()
{
    char* fileName = malloc(sizeof(char)*12);
    printf("Specify file name you would like to print to: \n");
    scanf("%s",fileName);
 

    FILE* file1 = fopen(fileName, "a+");
 
    char c;
    while ((c=getchar()) != EOF)
    {
        fprintf(file1, &c);
    }
 
    fclose(file1);
 
    printf("CTRL+d is a correct ending");
 
    return 0;
}
