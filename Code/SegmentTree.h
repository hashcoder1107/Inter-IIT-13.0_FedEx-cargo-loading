#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct SegmentTreeNode {
    int maxVal = 0;   // Stores max value for the segment
    int sumVal = 0;   // Stores sum of values for the segment
};

class SegmentTree2D {
private:
    vector<vector<SegmentTreeNode>> tree;
    int n, m; // n: number of rows, m: number of columns

    // Helper function to build the tree
    void build(vector<vector<int>>& matrix, int nodeX, int nodeY, int lx, int rx, int ly, int ry) {
        if (lx == rx && ly == ry) {
            tree[nodeX][nodeY].maxVal = matrix[lx][ly];
            tree[nodeX][nodeY].sumVal = matrix[lx][ly];
        } else {
            int mx = (lx + rx) / 2;
            int my = (ly + ry) / 2;
            
            build(matrix, 2 * nodeX + 1, 2 * nodeY + 1, lx, mx, ly, my);  // Bottom-left
            build(matrix, 2 * nodeX + 1, 2 * nodeY + 2, lx, mx, my + 1, ry); // Bottom-right
            build(matrix, 2 * nodeX + 2, 2 * nodeY + 1, mx + 1, rx, ly, my); // Top-left
            build(matrix, 2 * nodeX + 2, 2 * nodeY + 2, mx + 1, rx, my + 1, ry); // Top-right

            tree[nodeX][nodeY].maxVal = max({tree[2 * nodeX + 1][2 * nodeY + 1].maxVal,
                                             tree[2 * nodeX + 1][2 * nodeY + 2].maxVal,
                                             tree[2 * nodeX + 2][2 * nodeY + 1].maxVal,
                                             tree[2 * nodeX + 2][2 * nodeY + 2].maxVal});
            tree[nodeX][nodeY].sumVal = tree[2 * nodeX + 1][2 * nodeY + 1].sumVal + 
                                        tree[2 * nodeX + 1][2 * nodeY + 2].sumVal + 
                                        tree[2 * nodeX + 2][2 * nodeY + 1].sumVal + 
                                        tree[2 * nodeX + 2][2 * nodeY + 2].sumVal;
        }
    }

public:
    SegmentTree2D(int n, int m) : n(n), m(m) {
        tree.resize(4 * n, vector<SegmentTreeNode>(4 * m));
    }

    // Initialize segment tree with the matrix
    void buildTree(vector<vector<int>>& matrix) {
        build(matrix, 0, 0, 0, n - 1, 0, m - 1);
    }

    // Query the maximum value in the range (x1, y1) to (x2, y2)
    int queryMax(int nodeX, int nodeY, int lx, int rx, int ly, int ry, int x1, int y1, int x2, int y2) {
        if (x1 > rx || x2 < lx || y1 > ry || y2 < ly) {
            return INT_MIN; // No overlap
        }
        if (x1 <= lx && rx <= x2 && y1 <= ly && ry <= y2) {
            return tree[nodeX][nodeY].maxVal; // Total overlap
        }
        int mx = (lx + rx) / 2;
        int my = (ly + ry) / 2;
        return max({queryMax(2 * nodeX + 1, 2 * nodeY + 1, lx, mx, ly, my, x1, y1, x2, y2),
                    queryMax(2 * nodeX + 1, 2 * nodeY + 2, lx, mx, my + 1, ry, x1, y1, x2, y2),
                    queryMax(2 * nodeX + 2, 2 * nodeY + 1, mx + 1, rx, ly, my, x1, y1, x2, y2),
                    queryMax(2 * nodeX + 2, 2 * nodeY + 2, mx + 1, rx, my + 1, ry, x1, y1, x2, y2)});
    }

    // Query the sum of values in the range (x1, y1) to (x2, y2)
    int querySum(int nodeX, int nodeY, int lx, int rx, int ly, int ry, int x1, int y1, int x2, int y2) {
        if (x1 > rx || x2 < lx || y1 > ry || y2 < ly) {
            return 0; // No overlap
        }
        if (x1 <= lx && rx <= x2 && y1 <= ly && ry <= y2) {
            return tree[nodeX][nodeY].sumVal; // Total overlap
        }
        int mx = (lx + rx) / 2;
        int my = (ly + ry) / 2;
        return querySum(2 * nodeX + 1, 2 * nodeY + 1, lx, mx, ly, my, x1, y1, x2, y2) +
               querySum(2 * nodeX + 1, 2 * nodeY + 2, lx, mx, my + 1, ry, x1, y1, x2, y2) +
               querySum(2 * nodeX + 2, 2 * nodeY + 1, mx + 1, rx, ly, my, x1, y1, x2, y2) +
               querySum(2 * nodeX + 2, 2 * nodeY + 2, mx + 1, rx, my + 1, ry, x1, y1, x2, y2);
    }

    // Update the value in the range (x1, y1) to (x2, y2) with new value
    void update(int nodeX, int nodeY, int lx, int rx, int ly, int ry, int x1, int y1, int x2, int y2, int newValue) {
        if (x1 > rx || x2 < lx || y1 > ry || y2 < ly) {
            return; // No overlap
        }
        if (lx == rx && ly == ry) {
            tree[nodeX][nodeY].maxVal = newValue;
            tree[nodeX][nodeY].sumVal = newValue;
            return;
        }
        int mx = (lx + rx) / 2;
        int my = (ly + ry) / 2;

        update(2 * nodeX + 1, 2 * nodeY + 1, lx, mx, ly, my, x1, y1, x2, y2, newValue);
        update(2 * nodeX + 1, 2 * nodeY + 2, lx, mx, my + 1, ry, x1, y1, x2, y2, newValue);
        update(2 * nodeX + 2, 2 * nodeY + 1, mx + 1, rx, ly, my, x1, y1, x2, y2, newValue);
        update(2 * nodeX + 2, 2 * nodeY + 2, mx + 1, rx, my + 1, ry, x1, y1, x2, y2, newValue);

        tree[nodeX][nodeY].maxVal = max({tree[2 * nodeX + 1][2 * nodeY + 1].maxVal,
                                         tree[2 * nodeX + 1][2 * nodeY + 2].maxVal,
                                         tree[2 * nodeX + 2][2 * nodeY + 1].maxVal,
                                         tree[2 * nodeX + 2][2 * nodeY + 2].maxVal});
        tree[nodeX][nodeY].sumVal = tree[2 * nodeX + 1][2 * nodeY + 1].sumVal +
                                     tree[2 * nodeX + 1][2 * nodeY + 2].sumVal +
                                     tree[2 * nodeX + 2][2 * nodeY + 1].sumVal +
                                     tree[2 * nodeX + 2][2 * nodeY + 2].sumVal;
    }

    // Query the maximum value in the range (x1, y1) to (x2, y2)
    int queryMax(int x1, int y1, int x2, int y2) {
        return queryMax(0, 0, 0, n - 1, 0, m - 1, x1, y1, x2, y2);
    }

    // Query the sum of values in the range (x1, y1) to (x2, y2)
    int querySum(int x1, int y1, int x2, int y2) {
        return querySum(0, 0, 0, n - 1, 0, m - 1, x1, y1, x2, y2);
    }

    // Update a single cell value at (x, y)
    void update(int x, int y, int newValue) {
        update(0, 0, 0, n - 1, 0, m - 1, x, y, x, y, newValue);
    }

    // Update all values in the range (x1, y1) to (x2, y2) to newValue
    void update(int x1, int y1, int x2, int y2, int newValue) {
        update(0, 0, 0, n - 1, 0, m - 1, x1, y1, x2, y2, newValue);
    }
};
