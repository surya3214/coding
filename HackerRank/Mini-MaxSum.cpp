// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int num[BUFF(N_MAX)];
int max_idx, min_idx;
ll max_sum, min_sum;
void program() {
  min_idx = max_idx = 1;
  for (int i = 1; i <= N_MAX; ++i) {
    scanf("%d", &num[i]);
    if (num[i] > num[max_idx])
      max_idx = i;
    if (num[i] < num[min_idx])
      min_idx = i;
  }
  for (int i = 1; i <= N_MAX; ++i) {
    if (i != max_idx)
      min_sum += num[i];
    if (i != min_idx)
      max_sum += num[i];
  }
  printf("%lld %lld", min_sum, max_sum);
}
int main() {
  program();
  return 0;
}