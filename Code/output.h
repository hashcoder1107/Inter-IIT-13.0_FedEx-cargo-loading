// Vector<output-format>
#ifndef OUTPUT_H
#define OUTPUT_H

using namespace std;

class OUTPUT_ROW
{
public:
    // These vectors store the coordinates of two diagonally opposite corners of the package
    vector<int> bottomLeft; // This is the coordinate which will be closer to (0, 0, 0) (that is origin of the ULD)
    vector<int> topRight;   // This is the coordinate which is diagonally opposite to bottomLeft

    int uldNumber, packageNumber; // These are the package number and uldNumber in which the package is stored

    // Constructor definition
    OUTPUT_ROW(int packageNumber)
    {
        bottomLeft.resize(3, 0); // Size is three because we are dealing with 3D space
        topRight.resize(3, 0);
        uldNumber = -1;                      // Initially no ULD is assigned to the package
        this->packageNumber = packageNumber; // The package Number is updated for the package whose output is begin created.
    }

    OUTPUT_ROW()
    {
        bottomLeft.resize(3, 0); // Size is three because we are dealing with 3D space
        topRight.resize(3, 0);
        uldNumber = -1;          // Initially no ULD is assigned to the package
        this->packageNumber = 0; // The package Number is updated for the package whose output is begin created.
    }
    void updateOutput(vector<int> bottomLeft, vector<int> topRight, int uldNumber);
};

class OUTPUT
{
public:
    vector<OUTPUT_ROW> outputRows;

    OUTPUT(int totalPackages)
    {
        outputRows.resize(totalPackages);
    }
};

void OUTPUT_ROW::updateOutput(vector<int> bottomLeft, vector<int> topRight, int uldNumber)
{
    this->bottomLeft = bottomLeft;
    this->topRight = topRight;
    this->uldNumber = uldNumber;
}

#endif