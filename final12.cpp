//  main.cpp
//  Finalgr12
//
//  Created by Brooke Bullock on 2016-05-02.
//  Copyright (c) 2016 Brooke Bullock. All rights reserved.

#include "AtoB.h"
#include "ppmToText.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <cassert>

using namespace std;

bool checkfile(string filename);

int main() {
    assert(ppmtest()); // if fails, sets breakpoint
    assert(ABtest()); // if fails, sets breakpoint
    
    ofstream write; //file to be written to
    
    cout << "This program will change a text file to a text file format that, if you change the .txt ending to .ppm, will be read as an image.\nThe two file names that you enter must be in .txt format.\n";
    
    string readfile = " ", writefile = " ", write2 = " ";
    
    cout << "Please enter the whole address of the desired file to be converted.\n";
    getline(cin, readfile);
    
    while (checkfile(readfile) == false){
        cout << "That was not a valid file. Please check and reneter the address of the desired file to be converted.\n";
        getline(cin, readfile);
    }
    
    cout << "Please enter the whole address of the desired output file.\n";
    getline(cin, writefile);
    
    while (checkfile(writefile) == false) {
        cout << "That is an invalid file, please try again" << endl;
        getline(cin, writefile);
    }
    
    string key = "ergve";
    
    do {
        cout << "Can this file be written over? 'Y' for yes, any other key for no" << endl;
        getline(cin, key);
        
        if (key != "Y") {
            cout << "Please enter the whole address of the desired output file." << endl;
            getline(cin, writefile);
        }
        
    }while (checkfile(writefile) == false || key != "Y");
    
    // slurps whole read file into a stringstream
    ifstream read(writefile);
    stringstream buffer;
    buffer << read.rdbuf();
    string wholefile = buffer.str();
    read.close();
    
    int num;
    cout << "To encode a file, enter '1' To decode a file, enter '2'";
    cin >> num;
    while (num != 1 && num != 2) {
        cout << "That is an invalid entry, please try again";
        cin >> num;
    }
    cin.clear();
    
    if (num == 1) { //2 level or 1 level encoding?
        string encoded2 = AtoB(wholefile);
        string encoded = encodeppm(encoded2);
    
        write.open(writefile); //file will have been tested above, no need to check anymore
        write << encoded;
        write.close();
        cout << "File encoded" << endl;
    }
    
    if (num == 2) {
        string decoded = decodeppm(wholefile);
        string decoded2 = BtoA(decoded);
        
        write.open(writefile);
        write << decoded2;
        write.close();
        cout << "File decoded" << endl;
    }
    
    
    return 0;
}

bool checkfile(string filename) {
    ifstream f;
    f.open(filename);

    if (!f.is_open())//if the file is not valid
        return false;
    f.close();
    
    string type = "1234"; //4 characters long
    int b = filename.size() - 4;
    for (int a = 0; a < 4; a++)
        type[a] = filename[b+a];
    
    //cout << "The file type is " << type << endl;
    if (type != ".txt") //recognizes if the file is not in .txt format
        return false;
    
    else return true; //passes both tests
}


/*
 TEST OF WRITEFILE ENTERING SYSTEM
 Please enter the whole address of the desired read file.
 vbekqy
 That is an invalid file, please try again
 /Users/brooke/Desktop/essay.txt
 Can this file be written over? 'Y' for yes, any other key for no
 n
 Please enter the whole address of the desired read file.
 /Users/brooke/Desktop/essay.txt
 Can this file be written over? 'Y' for yes, any other key for no
 Y
 Program ended with exit code: 0
 
*/