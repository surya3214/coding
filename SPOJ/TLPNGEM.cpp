// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) (1e4)
#define INF (int) (1e9)
#define GEM '*'
#define TRANSPORTER '@'
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int dp[BUFF(LEN_MAX)];
int last_gem;
int transporter_positions[BUFF(LEN_MAX)];
int total_transporters, cur;
void addToTransporters(int x) { transporter_positions[++total_transporters] = x; }
void process() {
  total_transporters = last_gem = 0;
  for (int i = 0; str[i]; ++i) {
    dp[i] = INF;
    if (str[i] == GEM)
      last_gem = i;
    else if (str[i] == TRANSPORTER)
      addToTransporters(i);
  }
}
void compute() {
  dp[0] = 0;
  cur = 1;
  for (int i = 0; str[i]; ++i) {
    dp[i + 1] = min(dp[i + 1], dp[i] + 1);
    if ()
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%s", str);
    process();
    compute();
    printf("%d\n", dp[last_gem]);
  }
}
int main() {
  program();
  return 0;
}