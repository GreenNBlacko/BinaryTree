// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "GrayStl.h"

using namespace std;

int main() {
    Math* math = new Math("3+5*25+3");

    cout << math->parse() << endl;
}
