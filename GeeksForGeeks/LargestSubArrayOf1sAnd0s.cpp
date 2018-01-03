// AC
#include <bits/stdc++.h>
#define N_MAX 110
#define COUNT_MAX N_MAX * 2 + 10
using namespace std;
int numbers[N_MAX];
int hash_tbl[COUNT_MAX];
int n, cnt, ans;
void reset() {
  for (int i = 0; i < COUNT_MAX; i++)
    hash_tbl[i] = -1;
  hash_tbl[n] = cnt = ans = 0;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    reset();
    for (int i = 1; i <= n; i++) {
      scanf("%d", &numbers[i]);
      if (numbers[i])
        cnt++;
      else cnt--;
      if (hash_tbl[cnt + n] != -1)
        ans = max(ans, i - hash_tbl[cnt + n]);
      else hash_tbl[cnt + n] = i;
    }
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}

/*
int maxLen(int numbers[], int t_n) {
  n = t_n;
  reset();
  for (int i = 0; i < n; i++) {
    if (numbers[i])
      cnt++;
    else cnt--;
    if (hash_tbl[cnt + n] != -1)
      ans = max(ans, (i + 1) - hash_tbl[cnt + n]);
    else hash_tbl[cnt + n] = i + 1;
  }
  return ans;
}
*/