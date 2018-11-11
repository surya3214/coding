// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define Q_MAX (int) (3 * 1e5)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, q, k, x;
int numbers[BUFF(2 * N_MAX)];
int answers[BUFF(2 * N_MAX)];
char query[BUFF(Q_MAX)];
int findMaxLength(int l, int r) {
  int cur_length, ret;
  cur_length = ret = 0;
  for (int i = l; i <= r; ++i) {
    if (numbers[i]) {
      ++cur_length;
      ret = max(ret, cur_length);
      if (ret >= k)
        return k;
    } else cur_length = 0;
  }
  return ret;
}
void preprocess() {
  for (int i = 1; i <= n + 1; ++i)
    answers[i] = findMaxLength(i, i + n - 1);
}
void program() {
  scanf("%d %d %d", &n, &q, &k);
  for (int i = n + 1; i <= (2 * n); ++i) {
    scanf("%d", &numbers[i]);
    numbers[i - n] = numbers[i];
  }
  preprocess();
  scanf("%s", query);
  x = n + 1;
  for (int i = 0; query[i]; ++i) {
    switch (query[i]) {
      case '?':
        printf("%d\n", answers[x]);
        break;
      case '!':
        if (x == 1)
          x = n + 1;
        else --x;
        break;
    }
  }
}
int main() {
  program();
  return 0;
}