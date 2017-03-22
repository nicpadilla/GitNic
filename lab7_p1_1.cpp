// Lab7_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.
// Reference: Lippman, section 3.2

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab7_strings.cpp -o Lab7_strings -std=c++11
//      or:  g++ Lab7_strings.cpp -o Lab7_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard. 

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	string s1, s2("Hello"), s3 = "World";
        string s5("meh"), s6; //new strings
	cout << "\nEnter a word:" << endl;
	cin >> s1;
	cin.ignore();	// to consume the '\n' character. Otherwise, you may get issues with
					// the getline() below. Try commenting this out. Any issues?
	//New examples
        cout << s5 << endl; //write to output stream
        cin >> s5; //reads from input stream
        cin.ignore();
        cout << "Enter new string for s5 again: ";
        getline(cin, s5); //read line of input
        if(s5.empty()) cout << "string s5 is empty." << endl; //test s.empty()
	cout << "String s5 has length: " << s5.size() << endl; //tests s.size()
        cout << "3rd character is string s2 is: " << s1[3] << endl;
        cout << s2 + s5 << endl;
        s2 = s5;
        if(s2 == s5) cout << "strings s2 and s5 are equal." << endl;
        if(s2 != s3) cout << "strings s2 and s3 are not equal." << endl;
        if(s2 > s3) cout << "s2 > s3" << endl;
        
        string s4(s1);
	
	cout << s1 << endl
		 << s2 << endl
		 << s3 << endl
		 << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;

// ***********************************************************************
// Try all the operations in Table 3.2 using the strings above and
// using new strings that you may declare.
// Some of those operations have already been used, but write your
// own examples.
// ***********************************************************************

// -----------------------------------------------------------------------
	string line;
	cout << "\nEnter some text:" << endl;
	getline(cin, line);
	cout << line << endl;
	
	cout << "\nEnter some text, finish it with an &:" << endl;
	getline(cin, line, '&');	// the delimiter can be any character
	cout << line << endl;
        for(auto &c : line) {
            if(isupper(c)) c = tolower(c);
            else if(islower(c)) c = toupper(c);
            if(isspace(c)) c = ('.');
        }
        cout << line << endl;
// ***********************************************************************
// Use a "Range for" (Lippman, page 93) and operations in table 3.3 to:
// 1) change the case of the letters in your input line above (upper to
//    lowercase and vice-versa).
// 2) Replace any whitespace with a dot ('.').
// Print the converted text.
// ***********************************************************************

	return 0;
}
