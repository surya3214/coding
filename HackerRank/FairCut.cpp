// AC
#include <iostream>
#include <cstdio>
#define N_MAX 3010
#define K_MAX 3010
#define INF 1E18
using namespace std;
typedef long long int ll;
int n, k;
int numbers[N_MAX];
// dp[i][j] returns the minimal possible fairness where i elements have been processed & j elements belong in I set
ll dp[N_MAX][K_MAX];
void swap(int i, int j) {
  if (i != j) {
    int tmp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = tmp;
  }
}
int partition(int l, int r) {
  int small_index = l;
  int pivot = numbers[r];
  for (int i = l; i < r; i++) {
    if (numbers[i] <= pivot) {
      swap(small_index, i);
      small_index++;
    }
  }
  swap(small_index, r);
  return small_index;
}
void quick_sort(int l, int r) {
  if (l < r) {
    int pivot = partition(l, r);
    quick_sort(l, pivot - 1);
    quick_sort(pivot + 1, r);
  }
}
void compute() {
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= k; j++)
      dp[i][j] = INF;
  dp[0][0] = 0;
  ll cur_I, cur_J;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= k; j++) {
      if (dp[i][j] < INF) {
        // from every reached state, let's research putting numbers[i + 1] to I set or J set
        // put numbers[i + 1] in I set
        cur_I = (ll) numbers[i + 1] * (i - j) - (ll) numbers[i + 1] * (n - k - (i - j));
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + cur_I);
        // put numbers[i + 1] in J set
        cur_J = (ll) numbers[i + 1] * j - (ll) numbers[i + 1] * (k - j);
        dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + cur_J);
      }
    }
  }
}
void program() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &numbers[i]);
  quick_sort(1, n);
  // for (int i = 1; i <= n; i++)
  //   printf("%d\n", numbers[i]);
  compute();
  printf("%lld\n", dp[n][k]);
}
int main() {
  program();
  return 0;
}