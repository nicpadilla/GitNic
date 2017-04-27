#include <cstdlib>
#include <cstring>
#include<iostream>
#include<fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <limits.h>
#include <vector>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <exception>
using namespace std;

class myexception : public exception {
    virtual const char* what() const throw() {
        return "Error occurred!";
    }
} myex;

class Signal {
    private:
        int length;
        double maxval;
        double average, shift, scale;
        //double* data;
        vector<double> data;
    public:
        void Save_file(char*);
        void Sig_info(); //display length, maxval, average
        void Offset(double); //offset factor
        void Scale(double); //scale factor
        void Stats() throw(myexception);
        void Center();
        void Normalize();
        void Max();
        void Average();
        void operator+(const double);
        void operator*(const double);
        vector<double> getInfo();
        vector<double> getData();
        int getLength();
        void saveData(vector<double>&, double, double);
        Signal();
        Signal(int); //file num
        Signal(char*); //filename
        ~Signal(); //destructor
};

void checkLength(Signal&, Signal&);

vector<double> Signal::getData() {
    return data;
}

int Signal::getLength() {
    return length;
}

void Signal::saveData(vector<double> &newData, double max, double avg) {
    length = newData.size();
    data = newData;
    maxval = max;
    average = avg;
}
Signal operator+(Signal &obj1,Signal &obj2) {
    Signal sum; //initializes everything to zero
    double maxm, avg;
    try{checkLength(obj1, obj2);}
    catch(int i) {if(i == -1) throw;}
    cout << "----------------------------" << endl << "Object addition info: " << endl;
        vector<double> data1 = obj1.getData();
        vector<double> data2 = obj2.getData();
        vector<double> data3 = data1;
        auto it1 =max_element(data1.begin(), data1.end());
        auto it2 =max_element(data2.begin(), data2.end());
        maxm = max(*it1, *it2);
        avg = (double)(accumulate(data1.begin(), data1.end(), 0LL)+accumulate(data2.begin(), data2.end(), 0LL)) / (data1.size()+data2.size());
        //cout << "data1 size: " << data1.size() << "\ndata2size: " << data2.size() << endl;
        //cout << "data1 sum: " << accumulate(data1.begin(), data1.end(), 0LL) << endl;
        //cout << "data2 sum: " << accumulate(data2.begin(), data2.end(), 0LL) << endl;
        transform(data3.begin(), data3.end(), data2.begin(), data3.begin(), plus<int>());
        sum.saveData(data3, maxm, avg);
        return sum;
    
}

void checkLength(Signal &obj1,Signal &obj2) {
    if(obj1.getLength() != obj2.getLength()) throw(-1);
}

void Signal::operator+(double offset) {
    for(auto &i:data)
        i += offset;
    Max();
    Average();
}

void Signal::operator*(double factor) {
    for(auto &i:data)
        i *= factor;
    Max();
    Average();
}

Signal::Signal() {
    length = 0;
    maxval = 0;
    shift = 0; //initialize to zero in for later use
    scale = 0;
    average = 0;
}

Signal::Signal(int filenum) {
    char filename[15];
    sprintf(filename, "Raw_data_%.2d.txt", filenum);
    ifstream file;
    double temp;
    try {
        file.open(filename);
        if(!file.is_open()) throw -1;
    }
    catch(int i) {
        cout << "File does not exist." << endl;
        exit(0);
    }
    file >> length >> maxval;
    //data = new double[length];
    for(int i = 0; i < length; i++) {
        file >> temp;
        data.push_back(temp);
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
    double temp;
    for(int i = 0; i < length; i++) {
        file >> temp;
        data.push_back(temp);
    }
    Average();
    shift = 0;
    scale = 0;
    file.close();
}

Signal::~Signal() { //destructor
    //delete[] data; //clears allocated data
}

void Signal::Save_file(char* filename) {
    ofstream file; //writes data to new file specified by method parameter
    file.open(filename);
    file << length << ' ' << setprecision(4) << fixed << maxval << endl;
    //for(int i=0; i < length; i++) {
    for(auto &i:data) {
        file << setprecision(4) << fixed << i << endl;
    }
}

void Signal::Sig_info() { //display length, maxval, average
    cout << "Length: " << length << endl //"setprecision" and "fixed" specify decimal places when reading/writing/printing
            << "Max value: " << setprecision(4) << fixed << maxval << endl
            << "Average: " << setprecision(4) << fixed << average << endl;
    if(shift != 0) cout << "Shift : " << setprecision(4) << fixed << shift << endl;
    if(scale != 0) cout << "Scale factor: " << setprecision(4) << fixed << scale << endl;
    cout << "---------------------------------" << endl;
    for(auto i:data) cout << i << endl;
} //if shift or scale == 0, they are ignored

void Signal::Offset(double num) {
    /*for(int i=0; i < length; i++) {
        *(data+i) += num;
    }*/
    for(auto &i:data) {
        i += num;
    }
    Max(); //reset average and max values (done at end of each data modification method)
    Average();
    shift = num;
}

void Signal::Scale(double factor) {
    *this*factor;
    scale = factor;
}

void Signal::Stats() throw(myexception) {
    if(length <= 0) throw(myex);
    Average();
    Max();
    
}

void Signal::Center() {
    *this+(-average);
}

void Signal::Normalize() {
    *this*(1/maxval);
}

void Signal::Average() {
    double total = 0;
    for(auto &i:data)
        total += i;
    average = total/length;
}

void Signal::Max() {
    double max = data[0];
    for(auto &i:data)
        if(i > max) maxval = i;
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
            cerr << "no valid file information given. Initialized to zero." << endl;
        }
    }
    if(string(argv[argc-1]) == "-S") {
        try {sigObj->Stats();}
        catch(exception& e) {cout << e.what() << '\n'; exit(0);}
    }
    else if(string(argv[argc-1]) == "-C") sigObj->Center();
    else if(string(argv[argc-1]) == "-N") sigObj->Normalize();
    else if(isdigit(argv[argc-1][0]) && argc > 3) {
        num = atof(argv[argc-1]); //sets parameter for offset or scale
        if(string(argv[argc-2]) == "-o") {
            //sigObj->Offset(num);
            *sigObj+num;
        }
        else if(string(argv[argc-2]) == "-s") {
            *sigObj*num;
            sigObj->Sig_info();
        }
    }
    else {
        string command;
        double operand;
        cerr << "You've not entered correct commands. Try again." << endl;
        cout << "What would you like to do? First, enter only the command, then the operand if necessary." << endl;
        while(1) { //case in which incorrect or insufficient command is given
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
                //sigObj->Offset(operand);
                *sigObj+operand;
                break;
            }
            if(string(command) == "-s") {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Enter your scaling factor: ";
                cin >> operand;
                //sigObj->Scale(operand);
                *sigObj*operand;
                break;
            }
            cerr << "Incorrect input, try again." << endl;
        }
    }
    sigObj->Sig_info();
    sigObj->Save_file((char*)"modified_file.txt");
        delete[] filename;
        //Here we test the object addition operator
        Signal obj((char*)"Raw_data_01(2).txt");
        Signal obj2((char*)"Raw_data_01.txt");
        Signal obj3;
        try{obj3 = obj+obj2;}
        catch(...) {cout << "\n Error: Objects not of equal length." << endl; exit(0);}
        obj3.Sig_info();
}