


// C++ code to implement the sparse table
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <tuple>
#include <functional>
#include "uld.h"
#include "package.h"
#include "output.h"
#include "parser.h"
#include "validator.h"
#include <cmath>
#include "RMQ.h"
using namespace std;

int main() {
    vector<vector<int>> matrix = {
        {3, 5, 3},
        {8, 2, 2},
        {7, 5, 7}
    };

    MaxSumQuery2D segTree;
    segTree.build(3, 3,matrix);

    // Query maximum in range (0, 0) to (2, 2)
    int maxVal = segTree.maxQuery(0, 0, 2, 2);
    cout << "Maximum value: " << maxVal << endl;

    // Query sum in range (1, 1) to (2, 2)
    int sumVal = segTree.sumQuery(1, 1, 2, 2);
    cout << "Sum value: " << sumVal << endl;

    // Update single cell (1, 1) to 10
    segTree.update(1, 1, 10);

    // Query maximum in range (0, 0) to (2, 2) again
    maxVal = segTree.sumQuery(0, 0, 2, 2);
    cout << "Maximum value after update: " << maxVal << endl;

    return 0;
}