// AC Game Theory
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
bool win[BUFF(N_MAX)];
void ready() {
  win[2] = win[3] = win[4] = win[5] = true;
  for (int i = 6; i <= N_MAX; ++i)
    win[i] = !win[i - 2] || !win[i - 3] || !win[i - 5];
}
void program() {
  int tcase, rocks;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &rocks);
    if (win[rocks])
      printf("First\n");
    else printf("Second\n");
  }
}
int main() {
  ready();
  program();
  return 0;
}