#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double* FileRead(char*);
void Offset(double*, double, int); //offset factor
void Scale(double*, double, int); //scale factor
void Stats(double*, int);
int Max(double*);
double Average(double*);
void Center(double*, int);
void Normalize(double*, int);


int main(int argc, char *argv[])
{
	int i = 1, p=1, count = 0, filenum = 0, n = 0, size, FNrun = 0;
        double OffsetNum = 0, Sfactor = 0;
        char* filename = malloc(sizeof(char)*15); //given length of filename
        double* data = NULL;
        char* error = "Error, you must enter '-n' in the command line argument followed by the file number.\n"
                        "You may then use any of the following arguments after that:\n"
                        "-o: offset value (value needed)\n"
                        "-s: scale factor (value needed)\n"
                        "-r: rename files (name needed)\n"
                        "-h: help\n";
	while(i < argc){
            free(data);
            while(p < argc && FNrun == 0) { //check for filename first, else quit program
                if(!strcmp(argv[p], "-n")) {
                    if(isdigit(argv[p+1][0])) {
                        filenum = atoi(argv[p+1]);
                        sprintf(filename, "Raw_data_%.2d.txt", filenum);
                        if((data = FileRead(filename)) == NULL) return 0;
                        FNrun = 1; //to stop from running unnecessarily
                    }
                    else {
                        printf("%s", error);
                        return 0;
                    }
                }
                else if(i == argc-1) {
                    printf("%s", error);
                    return 0;
                }
                p++;
            }
            if(!strcmp(argv[i], "-o")) { //offset
                if(isdigit(argv[i+1][0]) || (argv[i+1][0] == '-' && isdigit(argv[i+1][1]))) {
                    OffsetNum = strtod(argv[i+1],NULL);
                    data = FileRead(filename);
                    Offset(data, OffsetNum, filenum);
                }
                    else {
                    printf("%s", error); //checks if first character is a digit
                    return 0;
                    }
            }
            else if(!strcmp(argv[i], "-s")) { //scale
                if(isdigit(argv[i+1][0]) || (argv[i+1][0] == '-' && isdigit(argv[i+1][1]))) {
                        Sfactor = strtod(argv[i+1],NULL);
                        data = FileRead(filename);
                        Scale(data, Sfactor, filenum);
                }
                        else {
                            printf("%s", error);
                            return 0;
                        }
            }
            else if(!strcmp(argv[i], "-r")) { //rename
                //check for next char
                if(argv[i+1][0] != '-') {
                    data = FileRead(filename); //reset data in case of previous edit
                    char* NewName = (char*)malloc((strlen(argv[i+1])+4)*sizeof(char)); //+4 is or ".txt"
                    double temp;
                    int q = 0;
                    int size = data[0]+2;
                    sprintf(NewName, "%s.txt", argv[i+1]);
                    FILE* new = fopen(NewName, "w");
                    while(q < size) {
                        if(q == 0) fprintf(new, "%.4f ", data[q]);
                        else fprintf(new, "%.4f\n", data[q]);
                        q++;
                    }
                    fclose(new);
                    free(NewName);
                }
                else {
                    printf("%s", error);
                    return 0;
                }
            }
            else if(!strcmp(argv[i], "-h")) { //help
                printf("%s", error);
                return 0;
            }
            else if(!strcmp(argv[i], "-S")) { //statistics
                data = FileRead(filename);
                Stats(data, filenum);
            }
            else if(!strcmp(argv[i], "-C")) {
                data = FileRead(filename);
                Center(data, filenum);
            }
            else if(!strcmp(argv[i], "-N")) {
                data = FileRead(filename);
                Normalize(data, filenum);
            }
            i++;
        }
        free(data);
        free(filename);
	return 0;
}

double* FileRead(char* filename)
{
    FILE* fp = fopen(filename, "r");
    int i, size, temp, max;
    if(fp == NULL) {
        printf("The file was not opened!\n");
        return NULL;
    }
    fscanf(fp, "%d", &size);
    size = size + 2;
    double* data = (double*)malloc(sizeof(double)*size); //allocates correct space
    rewind(fp);
    for(i = 0; i < size; i++) {
        fscanf(fp, "%lf", &data[i]);
    }
    fclose(fp);
    return data;
}

void Offset(double* data, double shift, int filenum) {
    int length = data[0], i;
    char filename[18];
    sprintf(filename, "Offset_data_%.2d.txt", filenum);
    FILE* fp = fopen(filename, "w");
    for(i=1; i < length+2; i++) {
        if(i == 1) data[i] = shift;
        else data[i] += shift;
    }
    for(i=0; i < length+2; i++) {
        if(i == 0) fprintf(fp, "%.4f ",data[i]);
        else fprintf(fp, "%.4f\n",data[i]);
    }
    /*for(i=0; i < length+2; i++) {
        printf("%.2f ", data[i]);
    }*/
    free(fp);
}

void Scale(double* data, double factor, int filenum) {
    int length = data[0], i;
    char filename[18];
    sprintf(filename, "Scaled_data_%.2d.txt", filenum);
    FILE* fp = fopen(filename, "w");
    for(i=1; i < length+2; i++) {
        if(i == 1) data[i] = factor;
        else data[i] *= factor;
    }
    for(i=0; i < length+2; i++) {
        if(i == 0) fprintf(fp, "%.4f ",data[i]);
        else fprintf(fp, "%.4f\n",data[i]);
    }
    free(fp);
}

void Stats(double* data, int filenum) {
    char filename[22];
    int maxval;
    double avg;
    sprintf(filename, "Statistics_data_%.2d.txt", filenum);
    FILE* fp = fopen(filename, "w");
    avg = Average(data);
    maxval = Max(data);
    fprintf(fp, "%.4f %d", avg, maxval);
    fclose(fp);
}

double Average(double* data) {
    double average, size, total = 0;
    int i;
    size = data[0];
    for(i=2; i < size+2; i++) {
        total += data[i];
    }
    average = total/size;
    return average;
}

int Max(double* data) {
    int max = data[2], i, size = data[0];
    for(i=2; i < size+2; i++) {
        if(data[i] > max) max = data[i];
    }
    return max;
}

void Center (double* data, int filenum) {
    int max = data[1], i, size = data[0];
    char filename[20];
    double avg;
    avg = Average(data);
    for(i=2; i < size+2; i++) {
        data[i] -= avg;
    }
    sprintf(filename, "Centered_data_%.2d.txt", filenum);
    FILE* fp = fopen(filename, "w");
        for(i=0; i < size+2; i++) {
        if(i == 0) fprintf(fp, "%.4f ",data[i]);
        else fprintf(fp, "%.4f\n",data[i]);
    }
    fclose(fp);
}

void Normalize(double* data, int filenum) {
    int max = data[1], i, size = data[0], min = data[2];
    char filename[22];
    sprintf(filename, "Normalized_data_%.2d.txt", filenum);
    for(i=2; i < size+2; i++) {
        if(data[i] < min) min = data[i];
    }
    for(i=2; i < size+2; i++) {
        data[i] = (double)((data[i]-min)/(max-min));
    }
    FILE* fp = fopen(filename, "w");
        for(i=0; i < size+2; i++) {
        if(i == 0) fprintf(fp, "%.4f ",data[i]);
        else fprintf(fp, "%.4f\n",data[i]);
    }
    fclose(fp);
}