// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 6
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int arr[BUFF(N_MAX)][BUFF(N_MAX)];
struct {
  bool set;
  int val;
} ans;
void updateAns(int x) {
  if (!ans.set) {
    ans.val = x;
    ans.set = true;
  } else ans.val = max(ans.val, x);
}
int getSum(int x, int y) {
  int ret = arr[x][y];
  for (int j = y - 1; j <= y + 1; ++j)
    ret += arr[x - 1][j] + arr[x + 1][j];
  return ret;
}
void program() {
  for (int i = 1; i <= N_MAX; ++i)
    for (int j = 1; j <= N_MAX; ++j)
      scanf("%d", &arr[i][j]);
  int x;
  for (int i = 2; i < N_MAX; ++i) {
    for (int j = 2; j < N_MAX; ++j) {
      x = getSum(i, j);
      updateAns(x);
    }
  }
  printf("%d\n", ans.val);
}
int main() {
  program();
  return 0;
}