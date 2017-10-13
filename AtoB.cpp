// ascii to binary & binary to ascii converter
// adapted from existing code from http://www.cplusplus.com/forum/general/1764/
// changed array of chars to strings
// removed dynamic memory allocation
// generally cleaned up code

#include "AtoB.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

string AtoB(string text) {
    stringstream output;
    
    for(long x = 0; x < text.size(); x++) { // each char converted individually
        int ascii = text[x]; //convert char to ascii number
        string binary = "00000000";
        int count = 7;
        
        while (ascii > 0) {
            if (ascii%2 != 0)
                binary[count] = '1';
            
            ascii = ascii/2;
            count--;
        }
        output << binary; //each binary chunk added to string for final output
    }
    return output.str();
}

string BtoA(string text) {
    char ascii; //the ascii character itself
    string output, binary;
    
    for (int x = 0; x < (text.size()/8); x++) { //reading in bytes. total characters = length / 8
        int v = 0;
        // v = v*2 + (text[x*8 + a] == '0' ? 0 : 1);
        for (int a = 0; a < 8; a++) {//store info into binary[0] through binary[7]
            if (text[x*8 + a] == '1')
                v = v*2 + 1;
            
            else v = v*2;
        }
        ascii = v;
        output += ascii;
    }
    return output;
}

bool ABtest() {
    string original = "lkjasdfoic9$nqls";
    string tmp = AtoB(original);
    string final = BtoA(tmp);
    return original == final;
}