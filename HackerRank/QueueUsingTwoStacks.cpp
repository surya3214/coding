// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct S {
  int elements[BUFF(Q_MAX)];
  int top;
} m_stack[2];
void pushToStack(int x) { m_stack[1].elements[++m_stack[1].top] = x; }
void turnOver() {
  while (m_stack[0].top) {
    pushToStack(m_stack[0].elements[m_stack[0].top]);
    --m_stack[0].top;
  }
}
void turnOverIfRequired() {
  if (!m_stack[1].top)
    turnOver();
}
void enqueue(int x) { m_stack[0].elements[++m_stack[0].top] = x; }
void dequeue() {
  turnOverIfRequired();
  --m_stack[1].top;
}
void program() {
  int q, type, x;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &type);
    switch (type) {
      case 1:
        scanf("%d", &x);
        enqueue(x);
        break;
      case 2:
        dequeue();
        break;
      case 3:
        turnOverIfRequired();
        printf("%d\n", m_stack[1].elements[m_stack[1].top]);
        break;
    }
  }
}
int main() {
  program();
  return 0;
}