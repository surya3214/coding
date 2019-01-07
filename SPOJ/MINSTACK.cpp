// AC Stack
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 5
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
stack<int> m_stack;
void program() {
  int n, x, y;
  char operation[BUFF(LEN_MAX)];
  scanf("%d", &n);
  for (int t = 1; t <= n; ++t) {
    scanf(" %s", operation);
    if (operation[0] == 'P') {
      if (operation[1] == 'U') {
        scanf("%d", &x);
        if (m_stack.empty())
          m_stack.push(x);
        else {
          y = m_stack.top();
          m_stack.push(min(y, x));
        }
      } else if (operation[1] == 'O') {
        if (!m_stack.empty())
          m_stack.pop();
        else printf("EMPTY\n");
      }
    } else if (operation[0] == 'M') {
      if (!m_stack.empty())
        printf("%d\n", m_stack.top());
      else printf("EMPTY\n");
    }
  }
}
int main() {
  program();
  return 0;
}