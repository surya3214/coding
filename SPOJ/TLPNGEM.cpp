// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) 1e4
#define TEL_MAX 5
#define TELEPORTER '@'
#define GEM '*'
#define INF (int) 1e7
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int dp[BUFF(LEN_MAX)];
int s_len, teleporters[BUFF(TEL_MAX)];
bool isFound;
void reset() { isFound = teleporters[0] = 0; }
int getMinimumTransporter() {
  int ret = INF;
  for (int i = 1; i <= teleporters[0]; ++i)
    ret = min(ret, dp[teleporters[i]]);
  return ret;
}
void addToTeleporter(int pos) {
  for (int i = 3; i >= 1; --i)
    teleporters[i] = teleporters[i - 1];
  teleporters[1] = pos;
  if (teleporters[0] < 3)
    ++teleporters[0];
}
void process() {
  for (s_len = 0; str[s_len]; ++s_len);
  dp[s_len] = INF;
  for (int i = s_len - 1; i >= 0; --i) {
    dp[i] = INF;
    if (str[i] == GEM) {
      if (!isFound) {
        dp[i] = 0;
        isFound = true;
      }
      teleporters[0] = 0;
    } else if (str[i] == TELEPORTER && isFound) {
      dp[i] = min(dp[i], 3 + getMinimumTransporter());
      addToTeleporter(i);
    }
    dp[i] = min(dp[i], 1 + dp[i + 1]);
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%s", str);
    process();
    printf("%d\n", dp[0]);
  }
}
int main() {
  program();
  return 0;
}