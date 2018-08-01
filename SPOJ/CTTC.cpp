// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100
using namespace std;
typedef long long int ll;
int child[BUFF(N_MAX)];
int n;
int m_stack[BUFF(N_MAX * 2)];
int top;
bool isEmpty() { return top == 0; }
void pushToStack(int x) { child[x] = 0; m_stack[++top] = x;}
void removeTop() { --top; }
void updateStack(int x) {
  if (m_stack[top] == x)
    removeTop();
  else {
    ++child[m_stack[top]];
    pushToStack(x);
  }
}
void program() {
  int tcase;
  int t_r, x;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d", &n);
    t_r = 2 * n;
    for (int i = 1; i <= t_r; ++i) {
      scanf("%d", &x);
      updateStack(x);
    }
    printf("Case %d:\n", t);
    for (int i = 1; i <= n; ++i)
      printf("%d -> %d\n", i, child[i]);
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}