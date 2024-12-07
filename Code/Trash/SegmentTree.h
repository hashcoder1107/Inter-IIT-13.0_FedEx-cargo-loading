```
// C++ code to implement the sparse table

#include <bits/stdc++.h>
using namespace std;

const int N = 100;
// int table[N][N][(int)(log2(N) + 1)][(int)(log2(N) + 1)];
class RMQ2D {
  int n, m, lgn, lgm;
  // int matrix[N][N];
  vector<vector<vector<vector<int>>>> table;

  virtual int merge(int a, int b) = 0;
public:
  // Function to build the sparse table
  void build_sparse_table(int _n, int _m, vector<vector<int>> &matrix) {
    n = _n;
    m = _m;
    lgn = log2(n) + 1;
    lgm = log2(m) + 1;
    // Copy the values of the original matrix
    // to the first element of the table
    table.assign(n, vector<vector<vector<int>>>(
                      m, vector<vector<int>>(lgn, vector<int>(lgm, 0))));
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        table[i][j][0][0] = matrix[i][j];
      }
    }

    // Building the table
    for(int k = 1; k <= (int)(log2(n)); k++) {
      for(int i = 0; i + (1 << k) - 1 < n; i++) {
        for(int j = 0; j + (1 << k) - 1 < m; j++) {
          table[i][j][k][0] = merge(table[i][j][k - 1][0],
                                  table[i + (1 << (k - 1))][j][k - 1][0]);
        }
      }
    }

    for(int k = 1; k <= (int)(log2(m)); k++) {
      for(int i = 0; i < n; i++) {
        for(int j = 0; j + (1 << k) - 1 < m; j++) {
          table[i][j][0][k] = merge(table[i][j][0][k - 1],
                                  table[i][j + (1 << (k - 1))][0][k - 1]);
        }
      }
    }

    for(int k = 1; k <= (int)(log2(n)); k++) {
      for(int l = 1; l <= (int)(log2(m)); l++) {
        for(int i = 0; i + (1 << k) - 1 < n; i++) {
          for(int j = 0; j + (1 << l) - 1 < m; j++) {
            table[i][j][k][l] = merge(
              merge(table[i][j][k - 1][l - 1],
                  table[i + (1 << (k - 1))][j][k - 1][l - 1]),
              merge(
                table[i][j + (1 << (l - 1))][k - 1][l - 1],
                table[i + (1 << (k - 1))][j + (1 << (l - 1))][k - 1][l - 1]));
          }
        }
      }
    }
  }

  // Function to find the maximum value in a submatrix
  int query(int x1, int y1, int x2, int y2) {
    // log2(x2-x1+1) gives the power of 2
    // which is just less than or equal to x2-x1+1
    int k = log2(x2 - x1 + 1);
    int l = log2(y2 - y1 + 1);

    // Lookup the value from the table which is
    // the maximum among the 4 submatrices
    return merge(merge(table[x1][y1][k][l], table[x2 - (1 << k) + 1][y1][k][l]),
               merge(table[x1][y2 - (1 << l) + 1][k][l],
                   table[x2 - (1 << k) + 1][y2 - (1 << l) + 1][k][l]));
  }

  void update(int i, int j, int v) {
    vector<vector<int>> matrix(n, vector<int>(m));
    for(int x = 0; x < n; x++) {
      for(int y = 0; y < m; y++) {
        matrix[x][y] = query(x, y, x, y);
      }
    }
    matrix[i][j] = v;
    this->build_sparse_table(n, m, matrix);
  }
};

class MinQuery2D: public RMQ2D {
  int merge(int a, int b) override {
    return min(a, b);
  }
};

class MaxQuery2D: public RMQ2D {
  int merge(int a, int b) override {
    return max(a, b);
  }
};

class RangeSum {
  vector<vector<int>> table;
  int n, m;
  
  public:
  void build(int _n, int _m,vector<vector<int>> &matrix) {
    n = _n;
    m = _m;
    table = matrix;
    for(int i = 0; i < n; i++) {
      for(int j = 1; j < m; j++ ) {
        table[i][j] += table[i][j - 1];
      }
    }
    for(int j = 0; j < m; j++ ) {
      for(int i = 1; i < n; i++) {
        table[i][j] += table[i - 1][j];
      }
    }
  }

  int query(int x1, int y1, int x2, int y2) {
    int ans = table[x2][y2];
    if(x1 && y1) ans += table[x1][y1];
    if(x1) ans -= table[x1][y2];
    if(y1) ans -= table[x2][y1];
    return ans;
  }

  
  void update(int i, int j, int v) {
    vector<vector<int>> matrix(n, vector<int>(m));
    for(int x = 0; x < n; x++) {
      for(int y = 0; y < m; y++) {
        matrix[x][y] = query(x, y, x, y);
      }
    }
    matrix[i][j] = v;
    this->build(n, m, matrix);
  }
};

// Function to solve the queries
void solve(int n, int m, vector<vector<int>> &matrix1, int q,
           vector<int> queries[]) {
  int i = 0;
  vector<vector<int>> matrix(n, vector<int>(m, 0));
  while(i < n) {
    int j = 0;
    while(j < m) {
      matrix[i][j] = matrix1[i][j];
      j++;
    }
    i++;
  }
  MaxQuery2D rmq;
  rmq.build_sparse_table(n, m, matrix);
  i = 0;
  // cout << rmq.query(1, 1, 1, 1) << endl;
  while(i < q) {
    int x1, y1, x2, y2;
    x1 = queries[i][0];
    y1 = queries[i][1];
    x2 = queries[i][2];
    y2 = queries[i][3];
    cout << rmq.query(x1, y1, x2, y2) << endl;
    i++;
  }
  rmq.update(1, 2, 7);
  i = 0;
  while(i < q) {
    int x1, y1, x2, y2;
    x1 = queries[i][0];
    y1 = queries[i][1];
    x2 = queries[i][2];
    y2 = queries[i][3];
    cout << rmq.query(x1, y1, x2, y2) << endl;
    i++;
  }
}

// Driver code
int main() {
  int N = 4, M = 4;
  vector<vector<int>> matrix1
    = {{5, 8, 2, 4}, {7, 2, 9, 1}, {1, 4, 7, 3}, {3, 5, 6, 8}};
  int Q = 2;
  vector<int> queries[] = {{0, 0, 3, 3}, {1, 1, 2, 2}};

  // Function call
  solve(N, M, matrix1, Q, queries);

  return 0;
}
```