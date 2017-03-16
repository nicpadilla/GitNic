#include <cstdlib>
#include <cstring>
#include<iostream>
#include<fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <limits.h>
using namespace std;

class Signal {
    private:
        int length;
        double maxval;
        double average, shift, scale;
        double* data;
        void Average();
        void Max();
    public:
        void Save_file(char*);
        void Sig_info(); //display length, maxval, average
        void Offset(double); //offset factor
        void Scale(double); //scale factor
        void Stats();
        void Center();
        void Normalize();
        Signal();
        Signal(int); //file num
        Signal(char*); //filename
        ~Signal(); //destructor
};

Signal::Signal() {
    ifstream file;
    file.open("Raw_data_01.txt");
    file >> length >> maxval;
    data = new double[length];
    for(int i = 0; i < length; i++) {
        file >> *(data+i);
    }
    Average();
    shift = 0;
    scale = 0;
    file.close();
}

Signal::Signal(int filenum) {
    char filename[15];
    sprintf(filename, "Raw_data_%.2d.txt", filenum);
    ifstream file;
    file.open(filename);
    file >> length >> maxval;
    data = new double[length];
    for(int i = 0; i < length; i++) {
        file >> *(data+i);
    }
    Average();
    shift = 0;
    scale = 0;
    file.close();
}

Signal::Signal(char* filename) {
    ifstream file;
    file.open(filename);
    file >> length >> maxval;
    data = new double[length];
    for(int i = 0; i < length; i++) {
        file >> *(data+i);
    }
    Average();
    shift = 0;
    scale = 0;
    file.close();
}

Signal::~Signal() {
    delete[] data;
}

void Signal::Save_file(char* filename) {
    ofstream file;
    file.open(filename);
    file << length << ' ' << setprecision(4) << fixed << maxval << endl;
    for(int i=0; i < length; i++) {
        file << setprecision(4) << fixed << *(data+i) << endl;
    }
}

void Signal::Sig_info() { //display length, maxval, average
    cout << "Length: " << length << endl
            << "Max value: " << setprecision(4) << fixed << maxval << endl
            << "Average: " << setprecision(4) << fixed << average << endl;
    if(shift != 0) cout << "Shift : " << setprecision(4) << fixed << shift << endl;
    if(scale != 0) cout << "Scale factor: " << setprecision(4) << fixed << scale << endl;
}

void Signal::Offset(double num) {
    for(int i=0; i < length; i++) {
        *(data+i) += num;
    }
    Max(); //we reset maxval to shift so we do not need to save it in the data array
    Average();
    shift = num;
}

void Signal::Scale(double factor) {
    for(int i=0; i < length; i++) {
        data[i] *= factor;
    }
    Max();
    Average();
    scale = factor;
}

void Signal::Stats() {
    Average();
    Max();
}

void Signal::Center() {
    for(int i=0; i < length; i++) {
        *(data+i) -= average;
    }
    Max();
    Average();
}

void Signal::Normalize() {
    double min = *data;
    for(int i=0; i < length; i++) {
        if(data[i] < min) min = data[i];
    }
    for(int i=0; i < length; i++) {
        data[i] = (double)((data[i]-min)/(maxval-min));
    }
    Max();
    Average();
}

void Signal::Average() {
    double total = 0;
    for(int i = 0; i < length; i++) {
        total += *(data+i);
    }
    average = total/length;
}

void Signal::Max() {
    double max = *data;
    for(int i=0; i < length; i++) {
        if(*(data+i) > max) maxval = *(data+i);
    }
}

int main(int argc, char** argv) {
    char* filename = new char [15]; //given length of filename
    Signal *sigObj = NULL;
    double num;
    for(int i = 0; i < argc; i++) { //checks for file name or number
        if(string(argv[i]) == "-n") {
            if(isdigit(argv[i+1][0])) { //file num case
                sigObj = new Signal(atoi(argv[i+1]));
                break;
            }
        }
        if(string(argv[i]) == "-f") {
            if(access(argv[i+1], F_OK ) == 0) { //checks if file name can be access (exists)
                filename = argv[i+1];
                sigObj = new Signal(filename);
                break;
            }
        }
        if(i == argc-1) {
            sigObj = new Signal(); //if no filename or num provided, use default file
            cerr << "no valid file information given. Default file selected." << endl;
        }
    }
    if(string(argv[argc-1]) == "-S") sigObj->Stats();
    else if(string(argv[argc-1]) == "-C") sigObj->Center();
    else if(string(argv[argc-1]) == "-N") sigObj->Normalize();
    else if(isdigit(argv[argc-1][0]) && argc > 3) {
        num = atof(argv[argc-1]); //sets parameter for offset or scale
        if(string(argv[argc-2]) == "-o") sigObj->Offset(num);
        else if(string(argv[argc-2]) == "-s") sigObj->Scale(num);
    }
    else {
        string command;
        double operand;
        cerr << "You've not entered correct commands. Try again." << endl;
        cout << "What would you like to do? First, enter only the command, then the operand if necessary." << endl;
        while(1) {
            cin >> command;
            if(string(command) == "-S") {
                sigObj->Stats();
                break;
            }
            if(string(command) == "-C") {
                sigObj->Center();
                break;
            }
            if(string(command) == "-N") {
                sigObj->Normalize();
                break;
            }
            if(string(command) == "-o") {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Enter your offset : ";
                cin >> operand;
                sigObj->Offset(operand);
                break;
            }
            if(string(command) == "-s") {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Enter your scaling factor: ";
                cin >> operand;
                sigObj->Scale(operand);
                break;
            }
            cerr << "Incorrect input, try again." << endl;
        }
    }
    sigObj->Sig_info();
    sigObj->Save_file((char*)"modified_file.txt");
        delete[] filename;
}