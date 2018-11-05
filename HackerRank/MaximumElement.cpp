// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int answers[BUFF(N_MAX)];
int top;
void pushToStack(int x) {
  ++top;
  answers[top] = max(answers[top - 1], x);
}
void pop() { --top; }
void program() {
  int n, x, type;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &type);
    switch (type) {
      case 1:
        scanf("%d", &x);
        pushToStack(x);
        break;
      case 2:
        pop();
        break;
      case 3:
        printf("%d\n", answers[top]);
        break;
    }
  }
}
int main() {
  program();
  return 0;
}