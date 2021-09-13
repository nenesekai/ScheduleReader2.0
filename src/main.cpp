#include <OpenXLSX.hpp>
#include <iostream>

using namespace std;
using namespace OpenXLSX;

int main(int argc, char* argv[]) {
    string fileName;
    for (int argIndex = 1; argIndex < argc; argIndex++) {
        if (argv[argIndex][0] != '-') {
            fileName = argv[argIndex];
        }
    }
    if (fileName == "") {
        cerr << "No Input File" << endl;
    } else {
        cout << "Reading File: " << fileName << endl;
    }
    return 0;
}