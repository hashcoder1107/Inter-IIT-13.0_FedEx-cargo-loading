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
#include "SegmentTree.h"
using namespace std;

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout<<"Hi"<<endl;

    SegmentTree2D segTree(3, 3);
    cout<<"Hi"<<endl;

    segTree.buildTree(matrix);

    cout<<"Hi"<<endl;

    // Query maximum in range (0, 0) to (2, 2)
    int maxVal = segTree.queryMax(0, 0, 2, 2);
    cout << "Maximum value: " << maxVal << endl;

    // Query sum in range (1, 1) to (2, 2)
    int sumVal = segTree.querySum(1, 1, 2, 2);
    cout << "Sum value: " << sumVal << endl;

    // Update single cell (1, 1) to 10
    segTree.update(1, 1, 10);

    // Query maximum in range (0, 0) to (2, 2) again
    maxVal = segTree.queryMax(0, 0, 2, 2);
    cout << "Maximum value after update: " << maxVal << endl;

    return 0;
}