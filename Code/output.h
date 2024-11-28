// Vector<output-format> 
#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
using namespace std;

class OUTPUT{
public:
    vector<int> bottomLeft, topRight; // these vectors store the coordinates of two diagonally opposite corners of the package
    int uldNumber, packageNumber; // These are the package number and uldNumber in which the package is stored

    // Constructor definition
    OUTPUT(int packageNumber){
        bottomLeft.resize(3, 0); // Size is three because we are dealing with 3D space
        topRight.resize(3, 0);
        uldNumber = -1; // Initially no ULD is assigned to the package
        this->packageNumber = packageNumber; // The package Number is updated for the package whose output is begin created.
    }
    void updateOutput();
};

void OUTPUT::updateOutput(vector<int> bottomLeft, vector<int> topRight, int uldNumber){
    this->bottomLeft = bottomLeft;
    this->topright = topRight;
    this->uldNumber = uldNumber;
}

#endif