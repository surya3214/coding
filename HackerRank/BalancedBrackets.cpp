// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) 1e3
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char input[BUFF(LEN_MAX)];
char m_stack[BUFF(LEN_MAX)];
int top;
void reset() { top = 0; }
void pushToStack(char x) { m_stack[++top] = x; }
void pop() { --top; }
void process() {
  for (int i = 0; input[i]; ++i) {
    switch (input[i]) {
      case '{':
      case '(':
      case '[':
        pushToStack(input[i]);
        break;
      case '}':
        if (m_stack[top] == '{')
          pop();
        else pushToStack(input[i]);
        break;
      case ')':
        if (m_stack[top] == '(')
          pop();
        else pushToStack(input[i]);
        break;
      case ']':
        if (m_stack[top] == '[')
          pop();
        else pushToStack(input[i]);
        break;
    }
  }
}
void program() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    reset();
    scanf("%s", input);
    process();
    if (top)
      printf("NO\n");
    else printf("YES\n");
  }
}
int main() {
  program();
  return 0;
}