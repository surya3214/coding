// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
ll numbers[BUFF(N_MAX)], prefix_sum[BUFF(N_MAX)];
int n;
ll m, ans;
struct {
  int idx;
} m_stack[BUFF(N_MAX)];
int top;
void reset() { ans = top = 0; }
void pushToStack(int idx) {
  ++top;
  m_stack[top].idx = idx;
}
void pop() { --top; }
bool isEmpty() { return top == 0; }
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %lld", &n, &m);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &numbers[i]);
      prefix_sum[i] = (prefix_sum[i - 1] + numbers[i]) % m;
      ans = max(ans, prefix_sum[i]);
      if (!prefix_sum[i])
        prefix_sum[i] = m;
    }
    for (int i = n; i >= 1; --i) {
      ans = max(ans, (prefix_sum[n] - prefix_sum[i - 1]) % m);
      while (!isEmpty() && prefix_sum[m_stack[top].idx] >= prefix_sum[i]) {
        ans = max(ans, (prefix_sum[m_stack[top].idx] - prefix_sum[i]) % m);
        pop();
      }
      pushToStack(i);
    }
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}