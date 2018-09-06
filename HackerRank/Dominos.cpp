// AC Stack
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct D {
  int x, h, idx;
} dominos[BUFF(N_MAX)];
int answers[BUFF(N_MAX)];
int top;
struct {
  int x, falls;
} t_stack[BUFF(N_MAX)];
bool m_comparator(D a, D b) {
  if (a.x != b.x)
    return a.x < b.x;
  return a.h < b.h;
}
int popFromStack(int x) {
  int cnt = 0;
  while (top && t_stack[top].x <= x) {
    cnt += t_stack[top].falls;
    --top;
  }
  return cnt;
}
void pushToStack(int x, int falls) {
  ++top;
  t_stack[top].x = x;
  t_stack[top].falls = falls;
}
void reset() {
  top = 0;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &dominos[i].x, &dominos[i].h);
      dominos[i].idx = i;
    }
    sort(dominos + 1, dominos + 1 + n, m_comparator);
    for (int i = n; i; --i) {
      answers[dominos[i].idx] = 1 + popFromStack(dominos[i].x + dominos[i].h - 1);
      pushToStack(dominos[i].x, answers[dominos[i].idx]);
    }
    for (int i = 1; i <= n; ++i)
      printf("%d ", answers[i]);
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}