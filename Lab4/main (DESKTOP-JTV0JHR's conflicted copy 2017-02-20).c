#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int* FileRead(char*);

int main(int argc, char *argv[])
{
	int i = 1, count = 0, filenum = 0;
        double offset = 0, scale = 0;
        char filename[11];
        int* data = NULL;
        char* error = "Error, you must enter '-n' in the command line argument followed by the file number.\n"
                        "You may then use any of the following arguments after that:\n"
                        "-o: offset value (value needed)\n"
                        "-s: scale factor (value needed)\n"
                        "-r: rename files (name needed)\n"
                        "-h: help\n";
	while(i < argc){
            if((argv[i][0] == '-') && (argv[i][1] == 'n')) {
                if(isdigit(argv[i+1][0])) {
                    filenum = atoi(argv[i+1]);
                    sprintf(filename, "Raw_data_%d", filenum);
                    data = FileRead(filename);
                }
                else {
                    printf("%s", error);
                }
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 'o')) {
                (isdigit(argv[i+1][0])) ? offset = strtod(argv[i+1],NULL) : printf("%s", error); //checks if first character is a digit
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 's')) {
                (isdigit(argv[i+1][0])) ? scale = strtod(argv[i+1],NULL) : printf("%s", error);
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 'r')) {
                
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 'h')) {
                printf("%s", error);
            }
            i++;
        }
	return 0;
}

int* FileRead(char* filename)
{
    FILE* fp = fopen(filename, "r");
    int i, length;
    if(fp == NULL) {
        printf("The file was not opened!");
        return 0;
    }
    fseek(fp,0,SEEK_END);
    length = (int)ftell(fp)/sizeof(int);
    int* data = (int*)malloc(sizeof(int)*length); //allocates correct space
    rewind(fp);
    for(int i = 0; i < length; i++) {
        fscanf(fp, "%d", data[i]);
    }
    fclose(fp);
    return data;
}