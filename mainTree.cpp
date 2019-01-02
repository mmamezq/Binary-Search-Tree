//
//  mainTree.cpp
//  x
//
//  Created by Tony Biehl on 11/6/17.
//  Copyright © 2017 Tony Biehl. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "BinarySearchTree.h"

using namespace std;

void print(string& n){
	cout << n << " " << endl;
}

int main()
{
    string filename;
    ifstream file;
    BinarySearchTree<string> t;
    bool contains;
        
    cout << "\nEnter a file name: ";
    cin >> filename;
    file.open(filename.c_str());
    while(file.fail()) {
        cout << "\nFile name does not exist.\n"
        << "Enter new file name or press q to exit: ";
        filename.clear();
        cin >> filename;
        if(tolower(filename[0])== 'q'){
            cout << "You have quit the program.\n";
            exit(1);
        } else {
            file.clear();
            file.open(filename.c_str());
        }
    }
    file.close();
    ifstream ifile;
    string name;
    ifile.open(filename.c_str());
    getline(ifile, name);
    t.add(name);
    while(!ifile.eof()) {
        getline(ifile, name);
        t.add(name);
    }


	t.preorderTraverse(print);
    t.displayTree();
    
    cout << "\nThis program will now search for: Nancy Drew." << endl;
    contains = t.contains("Nancy Drew");
    if(contains)
        cout << "This Tree contains the name Nancy Drew" << endl;
    else
        cout << "This Tree did not contain Nancy Drew" << endl;
    
    
    
    cout << "\nThis program will now search for: Monica Amezquita." << endl;
    contains = t.contains("Monica Amezquita");
    if(contains)
        cout << "This Tree contains the name Monica Amezquita" << endl;
    else
        cout << "This Tree did not contain Monica Amezquita" << endl;
    
    
    
    
    //Now, we will remove a name.
    cout << "\nWe will remove the root to see what happens." << endl << endl;
    t.remove("Nancy Drew");
    t.preorderTraverse(print);
    t.displayTree();
    
	cout << endl;
}
