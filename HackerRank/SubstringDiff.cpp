//
#include <iostream>
#include <cstdio>
#include <cstring>
#define N_MAX 1510
using namespace std;
int max_s;
char a[N_MAX], b[N_MAX];
int dp[N_MAX][N_MAX];
void reset() {
  for (int i = 0; i < N_MAX; i++)
    for (int j = 0; j < N_MAX; j++)
      dp[i][j] = -1;
}
int max_length(int a_ptr, int b_ptr, int length_so_far, int mismatch_so_far) {
  if (a_ptr == -1 || b_ptr == -1)
    return length_so_far;
  if (length_so_far) {
    // need to continue since only contiguous strings are considered
    if (a[a_ptr] == b[b_ptr])
      return max_length(a_ptr - 1, b_ptr - 1, length_so_far + 1, mismatch_so_far);
    else if (mismatch_so_far == max_s)
      return max(length_so_far, max_length(a_ptr, b_ptr, 0, 0));
    else return max_length(a_ptr - 1, b_ptr - 1, length_so_far + 1, mismatch_so_far + 1);
  } else {
    // start a new string from here or skip one of the characters
    int r1, r2;
    if (a[a_ptr] == b[b_ptr])
      r1 = max_length(a_ptr - 1, b_ptr - 1, 1, 0);
    else r2 = max_length(a_ptr - 1, b_ptr - 1, 1, 1);
    return max(max(r1, r2), max(max_length(a_ptr - 1, b_ptr, 0, 0), max_length(a_ptr, b_ptr - 1, 0, 0)));
  }
  return 0;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    reset();
    scanf("%d %s %s", &max_s, a, b);
    printf("%d\n", max_length(strlen(a), strlen(b), 0, 0));
  }
}
int main() {
  program();
  return 0;
}