#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

//for TS7250
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

string mcode[] = {".-", "-...", "-.-.", "-..", ".", "..-.", //a-f
		    "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", //g-p
		    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", //q-z
		    ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", //1-8
		    "----.", "-----", "/"};

	 char upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
			    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
			    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' '};

class message {
protected:
    string str;
public:
    message();
    message(string);
    virtual ~message();
    virtual void print();
};



message::message() {
    cout << "Enter the message you would like translated in all caps: " << endl;
    getline(cin, str);
}

message::message(string input) {
    str = input;
}

message::~message() {
    //delete[] str;
}

void message::print() {
    cout << "Base Class: " << endl << "\tOriginal Message: " << endl << "\t" << str << endl << endl;
}

//*********************************************************
//extended class
//
//*********************************************************

class morseCodeMessage : public message {
protected:
    string morse;
public:
    void translate();
    virtual void print();
    morseCodeMessage();
    void initializeValues();
    morseCodeMessage(string);
    virtual ~morseCodeMessage();
};




morseCodeMessage::morseCodeMessage() : message() {
    translate();
}

morseCodeMessage::morseCodeMessage(string input) : message(input) {
    str = input;
    translate();
}

morseCodeMessage::~morseCodeMessage() {

}


void morseCodeMessage::initializeValues()
{




}

void morseCodeMessage::translate() {
    string space = " ";
    int i, j;
    int d = (int)(sizeof(mcode)/sizeof(mcode[j]));
    //cout << "d = " << d << endl;
    for(i = 0; i < (int)str.length(); i++) {
        for(j = 0; j < d; j++) {
            if(str[i] == upper[j]) morse = morse + mcode[j] + space;
        }
    }
}

void morseCodeMessage::print() {
    cout << "morseCodeMessage Class: " << endl << "\tOriginal Message: " << endl << "\t" << str << endl << endl
            << "\tTranslated Message: " << endl << "\t" << morse << endl;
    cout << morse.length() << endl;

    //*****************************************************
    //code for TS7250
    //*****************************************************
    int fd, i;
    unsigned long *BasePtr, *PBDR, *PBDDR;
    fd = open("/dev/mem", O_RDWR|O_SYNC);
    if(fd == -1) {
        printf("\n error\n");
	return;  // failed open
	}
    BasePtr = (unsigned long*)mmap(NULL,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0x80840000);
    if(BasePtr == MAP_FAILED){
    	printf("\n Unable to map memory space \n");
    	return;
    }
    PBDR = BasePtr + 1;		// Address of port B DR is 0x80840004
    PBDDR = BasePtr + 5;	// Address of port B DDR is 0x80840014

    *PBDDR |= 0xE0;	// configures port B7, B6, B5 as output (Green LED)
    *PBDR &= ~0x60; //initialize all LED to off
    for(i = 0; i < (int)morse.length(); i++) {
        if(morse[i] == '.') {
            *PBDR |= 0x20; //turn red LED on
            usleep(500*1000);
            *PBDR &= ~0x20;
            usleep(500*1000);
        }
        else if(morse[i] == '-') {
            *PBDR |= 0x40; //turn yellow LED on
            usleep(500*1000);
            *PBDR &= ~0x40;
            usleep(500*1000);
        }
        else if(morse[i] == '/') {
            *PBDR |= 0x80; //turn green on
            usleep(500*1000);
            *PBDR &= ~0x80;
            usleep(500*1000);
        }
    }
    close(fd);
}

//*********************************************************
//Stack class
//
//*********************************************************

class messageStack {
private:
    vector<message*> stack;
    int top; //= -1; //so top is actually pointing to the last Pushed obj
public:
    messageStack(message&);
    ~messageStack();
    void Push(message&);
    void Pop();
    void Printstack();
};

messageStack::messageStack(message &obj) {
	top = -1;
    Push(obj);
}

messageStack::~messageStack() {

}

void messageStack::Push(message &obj) {
    stack.push_back(&obj);
    top++;
}

void messageStack::Pop() {
    if(top <= 0) {
        cerr << "Stack is empty!" << endl;
        top = -1;
    }
    else {
        stack.erase (stack.begin()+top);
        top--;
    }

}

void messageStack::Printstack() {
    int cur; //current location in stack
    cout << "***********************************" << endl;
    cout << "Printing Messages on Stack: " << endl << endl;
    for(cur = top; cur > -1; cur--) {
        stack[cur]->print();
    }
    cout << "***********************************" << endl;
}

int main(int argc, char** argv) {
    morseCodeMessage test1("THIS IS A TEST");
    test1.print();
    return 0;
}

