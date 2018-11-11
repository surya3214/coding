// TLE on 23-27
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, max_days;
int plants[BUFF(N_MAX)];
int plants_buffer[BUFF(N_MAX)];
void reduce(int l, int r) {
  for (int i = l; i <= r; ++i)
    plants_buffer[i - l + 1] = plants[i];
  plants_buffer[0] = r - l + 1;
  int times = 0, x;
  while (plants_buffer[0] != 1) {
    x = plants_buffer[0];
    plants_buffer[0] = 1; 
    for (int i = 2; i <= x; ++i) {
      if (plants_buffer[i] <= plants_buffer[i - 1])
        plants_buffer[++plants_buffer[0]] = plants_buffer[i];
    }
    ++times;
  }
  max_days = max(max_days, times);
}
void solve() {
  int cur_valid = 1;
  for (int i = 2; i <= n; ++i) {
    if (plants[i] <= plants[cur_valid]) {
      reduce(cur_valid, i - 1);
      cur_valid = i;
    }
  }
  reduce(cur_valid, n);
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &plants[i]);
  solve();
  printf("%d\n", max_days);
}
int main() {
  program();
  return 0;
}