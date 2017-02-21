#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int* FileRead(char*);
int* Offset(char*, int); //offset factor
int* Scale(char*, int); //scale factor


int main(int argc, char *argv[])
{
	int i = 1, count = 0, filenum = 0, n = 0, size;
        double offset = 0, scale = 0;
        char* filename = malloc(sizeof(char)*15); //given length of filename
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
                    sprintf(filename, "Raw_data_%.2d.txt", filenum);
                    data = FileRead(filename);
                }
                else printf("%s", error);
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 'o')) {
                if(isdigit(argv[i+1][0])) {
                    offset = strtod(argv[i+1],NULL);
                    data = FileRead(filename);
                }
                    else printf("%s", error); //checks if first character is a digit
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 's')) {
                if(isdigit(argv[i+1][0])) {
                        scale = strtod(argv[i+1],NULL);
                        data = FileRead(filename);
                }
                        else printf("%s", error);
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 'r')) {
                //check for next char
                data = FileRead(filename);
                //else printf("%s", error);
            }
            else if((argv[i][0] == '-') && (argv[i][1] == 'h')) {
                printf("%s", error);
            }
            i++;
        }
        /*for(size = data[1]+2; n < size; n++) {
            printf("%d ", data[n]);
        }*/
	return 0;
}

int* FileRead(char* filename)
{
    FILE* fp = fopen(filename, "r");
    int i, size, temp, max;
    if(fp == NULL) {
        printf("The file was not opened!");
        return 0;
    }
    fscanf(fp, "%d", &size);
    size = size + 2;
    int* data = (int*)malloc(sizeof(int)*size); //allocates correct space
    rewind(fp);
    for(i = 0; i < size; i++) {
        fscanf(fp, "%d", &data[i]);
    }
    fclose(fp);
    return data;
}

int* Offset(char*, int num) {
    
}

int* Scale(char*, int factor) {
    
}