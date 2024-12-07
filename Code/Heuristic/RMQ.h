#pragma once

#include <vector>

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
    if(x1 && y1) ans += table[x1-1][y1-1];
    if(x1) ans -= table[x1-1][y2];
    if(y1) ans -= table[x2][y1-1];
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

class MaxSumQuery2D {
  RangeSum range_sum;
  MaxQuery2D range_max;
  int n, m;

  public:
  void build(int _n, int _m, vector<vector<int>> &matrix) {
    n = _n;
    m = _m;
    range_sum.build(n, m, matrix);
    range_max.build_sparse_table(n, m, matrix);
  } 

  int sumQuery(int x1, int y1, int x2, int y2) {
    return range_sum.query(x1, y1, x2, y2);
  }

  int maxQuery(int x1, int y1, int x2, int y2) {
    return range_max.query(x1, y1, x2, y2);
  }

  void update(int x1, int y1, int val) {
    range_sum.update(x1, y1, val);
    range_max.update(x1, y1, val);
  }

  vector<vector<int>> getState() {
    vector<vector<int>> state(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        state[i][j] = sumQuery(i, j, i, j);
      }
    }
    return state;
  }
};

