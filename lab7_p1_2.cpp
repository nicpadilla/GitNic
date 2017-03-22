// Lab7_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++11
//      or:  g++ Lab7_vectors.cpp -o Lab7_vectors -std=c++0x
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

        
        //new initialization
        vector<int> v1;
        vector<int> v5{5};
        vector<int> v2(5);
        vector<int> v9=v1;
        vector<int> v3(5, 5);
        vector<int> v10(v5);
        vector<int> v4{25, 34, 15};
        vector<int> v6 = {21, 15, 45};
        
	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
// ***********************************************************************
// Try all the ways to initialize a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.

// Do exercises 3.14 and 3.15 from Lippman (page 102)

// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.
// ***********************************************************************
        
        //exercise 3.14
        string string1;
        int int1;
        
        vector<int> test1;
        vector<string> test2;
        
        cout << "Enter as many integers as you'd like and end with a non-integer character." << endl;
        while(cin >> int1) {
            test1.push_back(int1);
            cin.ignore(1000, '\n');
        }
        cin.clear(); //flush cin for getline
        cin.ignore(1000, '\n');
        cout << "------------------------" << endl;
        for(auto &i:test1) {
            cout << i << endl;
        }
        while(string1 != "&") {
            cout << "Enter strings: " << endl;
            getline(cin, string1);
            if(string1 != "&") test2.push_back(string1);
        }
        cout << "------------------------" << endl;
        for(auto &i:test2) cout << i << endl;
	return 0;
}
