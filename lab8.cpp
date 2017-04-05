#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

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
    vector<char> upper = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ' '};
    vector<string> mcode = {".-", "-...", "-.-.", "-..", ".", "..-.", //a-f
    "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", //g-p
    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", //q-z
    ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", //1-8
    "----.", "-----", "/"}; //9-0 and space
    string morse;
public:
    void translate();
    virtual void print();
    morseCodeMessage();
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

void morseCodeMessage::translate() {
    string space = {" "};
    for(int i = 0; i < str.size(); i++) {
        for(int j = 0; j < mcode.size(); j++) {
            if(str[i] == upper[j]) morse = morse + mcode[j] + space;
        }
    }
}

void morseCodeMessage::print() {
    cout << "morseCodeMessage Class: " << endl << "\tOriginal Message: " << endl << "\t" << str << endl << endl
            << "\tTranslated Message: " << endl << "\t" << morse << endl << endl;
}

//*********************************************************
//Stack class
//
//*********************************************************

class messageStack {
private:
    vector<message*> stack;
    int top = -1; //so top is actually pointing to the last Pushed obj
public:
    messageStack(message&);
    ~messageStack();
    void Push(message&);
    void Pop(message&);
    void Printstack();
};

messageStack::messageStack(message &obj) {
    Push(obj);
}

messageStack::~messageStack() {
    
}

void messageStack::Push(message &obj) {
    stack.push_back(&obj);
    top++;
}

void messageStack::Pop(message &obj) {
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
    morseCodeMessage test1("HELLO THERE I AM 20");
    message test2("Hello there, I am 20.");
    morseCodeMessage test3("LIONS ARE THE SUPERIOR ANIMAL.");
    morseCodeMessage test4;
    test4.print();
    test1.print();
    test2.print();
    messageStack s(test1);
    s.Push(test2);
    s.Push(test3);
    s.Printstack();
    return 0;
}

