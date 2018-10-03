// AC Stack
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) 1e6
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
char l_stack[BUFF(LEN_MAX)], r_stack[BUFF(LEN_MAX)];
int l_s_ptr, r_s_ptr;
void resetStack() { l_s_ptr = r_s_ptr = 0; }
char pop(bool s_type) {
  if (s_type) {
    if (l_s_ptr)
      return l_stack[l_s_ptr--];
  } else if (r_s_ptr)
    return r_stack[r_s_ptr--];
  return 0;
}
bool isEmpty(bool s_type) {
  if (s_type)
    return l_s_ptr == 0;
  return r_s_ptr == 0;
}
void push(char x, bool s_type) {
  if (s_type)
    l_stack[++l_s_ptr] = x;
  else r_stack[++r_s_ptr] = x;
}
void fromLToR() {
  if (isEmpty(true))
    return;
  char x = pop(true);
  push(x, false);
}
void fromRToL() {
  if (isEmpty(false))
    return;
  char x = pop(false);
  push(x, true);
}
void process() {
  for (int i = 0; str[i]; ++i) {
    switch (str[i]) {
      case '<':
        fromLToR();
        break;
      case '>':
        fromRToL();
        break;
      case '-':
        pop(true);
        break;
      default:
        push(str[i], true);
    }
  }
  while (!isEmpty(false))
    fromRToL();
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    resetStack();
    scanf("%s", str);
    process();
    for (int i = 1; i <= l_s_ptr; ++i)
      printf("%c", l_stack[i]);
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}