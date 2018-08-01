// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
using namespace std;
typedef long long int ll;
char buffer[BUFF(N_MAX)][BUFF(N_MAX)];
int n, h;
char input[BUFF(N_MAX)];
int col, t_ptr;
int col_max[BUFF(N_MAX)];
bool addIndex(int row, int col) {
  if (input[t_ptr] == '\0') return false;
  buffer[row][col] = input[t_ptr++];
  col_max[row] = max(col_max[row], col);
  return true;
}
bool startRFrom() {
  for (int row = h - 1; row >= 0; --row)
    if (!addIndex(row, col))
      return false;
  if (input[t_ptr] == '\0') return false;
  int t = (h / 2) + 1;
  for (int t_col = col + 1; t_col < col + t; ++t_col)
    if (!addIndex(0, t_col))
      return false;
  for (int t_row = 1; t_row < t; ++t_row)
    if (!addIndex(t_row, col + t - 1))
      return false;
  for (int t_col = col + t - 2; t_col > col; --t_col)
    if (!addIndex(t - 1, t_col))
      return false;
  for (int row = t; row < h; ++row) {
    ++col;
    if (!addIndex(row, col))
      return false;
  }
  ++col;
  if (!addIndex(h - 1, col))
    return false;
  ++col;
  if (input[t_ptr] == '\0') return false;
  return true;
}
void program() {
  scanf("%d %d", &n, &h);
  scanf(" %s", input);
  bool ret = startRFrom();
  while (ret)
    ret = startRFrom();
  for (int row = 0; row <= h - 1; ++row) {
    for (int col = 0; col <= col_max[row]; ++col) {
      if (buffer[row][col]) printf("%c", buffer[row][col]);
      else printf("#");
    }
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}