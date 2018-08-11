// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1e9
#define TIMES_MAX 28
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n;
ll cumulative_sum[BUFF(TIMES_MAX)];
int each_players[BUFF(TIMES_MAX)];
char players[6][10] = { "", "Asad", "Foyj", "Juwel", "Mijan", "Tanmay" };
void preprocess() {
  ll s = 5;
  int times = 1;
  cumulative_sum[times] = s;
  each_players[times] = s / 5;
  while (s <= N_MAX) {
    s = s * 2;
    ++times;
    cumulative_sum[times] = s + cumulative_sum[times - 1];
    each_players[times] = s / 5;
  }
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int findBS() {
  int l, r, mid;
  l = 1, r = TIMES_MAX;
  while (l <= r) {
    mid = getMid(l, r);
    if (cumulative_sum[mid] >= n)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
int findPlayer() {
  int x = findBS();
  int player = 1;
  int seen_so_far = (x > 0) ? cumulative_sum[x - 1] : 0;
  while (seen_so_far + each_players[x] < n) {
    seen_so_far += each_players[x];
    ++player;
  }
  return player;
}
void program() {
  preprocess();
  int x;
  while (scanf("%d", &n) != EOF) {
    x = findPlayer();
    printf("%s\n", players[x]);
  }
}
int main() {
  program();
  return 0;
}