// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int alice[BUFF(N_MAX)], bob[BUFF(N_MAX)];
int a_score, b_score;
void program() {
  for (int i = 1; i <= N_MAX; ++i)
    scanf("%d", &alice[i]);
  for (int i = 1; i <= N_MAX; ++i)
    scanf("%d", &bob[i]);
  for (int i = 1; i <= N_MAX; ++i) {
    if (alice[i] > bob[i])
      ++a_score;
    else if (bob[i] > alice[i])
      ++b_score;
  }
  printf("%d %d", a_score, b_score);
}
int main() {
  program();
  return 0;
}