// AC #Easy
#include <bits/stdc++.h>
using namespace std;
static bool isValid(int x, int y) {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}
int moves_x[] = { -1, 0, 1,  0 };
int moves_y[] = {  0, 1, 0, -1 };
int rows, cols;
class Solution {
public:
  int islandPerimeter(vector<vector<int>>& grid) {
    int ret = 0;
    rows = grid.size(), cols = grid[0].size();
    for (int i = 0, next_x, next_y; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
          if (!grid[i][j])
            continue;
        for (int k = 0; k < 4; ++k) {
          next_x = i + moves_x[k];
          next_y = j + moves_y[k];
          if (!isValid(next_x, next_y) || grid[next_x][next_y] == 0)
            ++ret;
        }
      }
    }
    return ret;
  }
};
