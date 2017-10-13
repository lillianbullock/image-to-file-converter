#include "ppmToText.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>
#include <string>

using namespace std;

string decodeppm(string text) {
    stringstream textstream(text);
    stringstream output;
    char c;
    int ascii;
    string void_;
    
    //deals with the header info at the start
    for (int a = 0; a < 4; a++)
        textstream >> void_; //goes into the void
    
    while (textstream.good()) {
        textstream >> ascii;
        if (ascii == 0) continue;
        c = ascii; //integer to character
        output << c; //character into output string
    }
    return output.str();
}

string encodeppm (string text) {
    stringstream output;
    size_t num = text.size();
    
    long pix = (num+2)/3; //essentially rounds up instead of down
    
    long height = sqrt(pix); //height is the square root of pix
    if (height * height < pix) //if it pix wasn't an exact square, add one to the width and height
        height++;
    
    long width = height;
    
    if ((height * (width-1)) >= pix) //takes away whole row of dead pixels if applicable
        height--;
    
    pix = height * width; //actual number of pixels in whole image
    
    output << "P3\n" << width << " " << height << "\n255\n"; //ppm image header
    
    for (size_t a = 0; a < pix * 3;a++) {
        if (a < text.size()) // while there are still characters in the file
            output << (int)text[a];
        
        else output << '0'; // after end of file, put zeros
        
        if ((a+1)%3 == 0) //makes format nicer, one pixel per line
            output << endl;
        
        else output << " ";
    }
    return output.str();
}

bool ppmtest() {
    string start = "Hello my name is Brooke.";
    string encoded = encodeppm(start);
    //cout << "The encoded file is;\n" << encoded << endl;
    string decoded = decodeppm(encoded);
    //cout << "The decoded file is;\n" << decoded << endl;
    return start == decoded;
}