//
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
using namespace std;
typedef long long int ll;
struct {
  int height, price;  
} students[BUFF(N_MAX)];
class {
 public:
  void push(int idx, ll cost_so_far) {
    ++top;
    contents[top].idx = idx;
    contents[top].cost = cost_so_far;
  }
  void pop() { --top; }
  void seek(int &idx, ll &cost) {
    idx = contents[top].idx,
    cost = contents[top].cost;
  }
  bool isEmpty() { return top == 0; };
  void reset() { top = 0; }
 private:
  struct {
    int idx;
    ll cost;
  } contents[BUFF(N_MAX)];
  int top;
} t_stack;
int n;
void program() {
  int t_idx;
  ll t_cost, p_cost;
  ll indie_cost;
  scanf("%d", &n);
  scanf("%d", &students[1].height);
  for (int i = 2; i <= n; i++)
    scanf("%d", &students[i].height);
  for (int i = 2; i <= n; i++)
    scanf("%d", &students[i].price);
  t_stack.push(1, 0);
  ll ans = LLONG_MAX;
  for (int i = 2; i <= n; i++) {
    p_cost = LLONG_MAX;
    while (!t_stack.isEmpty()) {
      t_stack.seek(t_idx, t_cost);
      indie_cost = t_cost + students[i].price + i - t_idx;
      if (students[i].height > students[t_idx].height) {
        p_cost = min(p_cost, indie_cost + students[i].height - students[t_idx].height);
        t_stack.pop();
      } else {
        p_cost = min(p_cost, indie_cost + students[t_idx].height - students[i].height);
        break;
      }
    } 
    t_stack.push(i, p_cost);
    // ans = min(ans, p_cost);
  }
  ll ans = LLONG_MAX;
  while (!t_stack.isEmpty()) {
    t_stack.seek(t_idx, t_cost);
    ans = min(ans, t_cost + n + 1 - t_idx);
    t_stack.pop();
  }
  printf("%lld\n", ans);
}
int main() {
  freopen("HackerRank/ARaceAgainstTime_input.txt", "r", stdin);
  program();
  return 0;
}