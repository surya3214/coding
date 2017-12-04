// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define M_MAX 1010
using namespace std;
int n, k, m;
int groups[N_MAX];
int ranks[N_MAX];
int input[M_MAX];
int dp[M_MAX][M_MAX];
int findGroup(int i) {
  if (groups[i] == -1)
    return i;
  return findGroup(groups[i]);
}
void groupify(int u, int v) {
  int u_g = findGroup(u);
  int v_g = findGroup(v);
  if (u_g == v_g)
    return;
  else if (ranks[u_g] >= ranks[v_g]) {
    groups[v] = groups[v_g] = u_g;
    ranks[u_g] += ranks[v_g];
  } else {
    groups[v] = groups[v_g] = v_g;
    ranks[v_g] += ranks[u_g];
  }
}
void computeDP() {
  for (int i = 1; i <= m; i++)
    dp[i][i] = 1;
  int j;
  for (int str_len = 2; str_len <= m; str_len++) {
    for (int i = 1; i + str_len - 1 <= m; i++) {
      j = i + str_len - 1;
      if (input[i] == input[j]) {
        if (str_len == 2)
          dp[i][j] = 2;
        else dp[i][j] = 2 + dp[i + 1][j - 1];
      } else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
    }
  }
}
void program() {
  int a, b, tmp;
  scanf("%d %d %d", &n, &k, &m);
  for (int i = 1; i <= n; i++)
    groups[i] = -1;
  for (int i = 1; i <= k; i++) {
    scanf("%d %d", &a, &b);
    groupify(a, b);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &tmp);
    input[i] = findGroup(tmp);
  }
  computeDP();
  printf("%d\n", dp[1][m]);
}
int main() {
  program();
  return 0;
}