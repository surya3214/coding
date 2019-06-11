// AC Simple sorting, Graph theory
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
// #pragma GCC optimize "O4"
#define N_MAX (int) 1e5
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct A {
  A() {}
  A(int t_val, int t_idx) : val(t_val), idx(t_idx) {}
  bool operator <(const A &r) { return val < r.val; }
  int val, idx;
} s_arr[BUFF(N_MAX)];
int s_ptr;
struct B {
  int val, s_pos;
  bool visited;
} arr[BUFF(N_MAX)];
int n;
void addToA(int val, int idx) { s_arr[++s_ptr] = { val, idx }; }
void findPositions(bool type) {
  for (int i = 1; i <= n; ++i) {
    if (type)
      arr[s_arr[i].idx].s_pos = i;
    else arr[s_arr[i].idx].s_pos = n - i + 1;
  }
}
int getCycleLength(int idx) {
  if (arr[idx].visited)
    return 0;
  arr[idx].visited = true;
  int ret = 1;
  ret += getCycleLength(arr[idx].s_pos);
  return ret;
}
int countMoves() {
  findPositions(true);
  int ret1 = 0;
  for (int i = 1; i <= n; ++i)
    if (!arr[i].visited)
      ret1 += getCycleLength(i) - 1;
  for (int i = 1; i <= n; ++i)
    arr[i].visited = false;
  findPositions(false);
  int ret2 = 0;
  for (int i = 1; i <= n; ++i)
    if (!arr[i].visited)
      ret2 += getCycleLength(i) - 1;
  return min(ret1, ret2);
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <=n; ++i) {
    scanf("%d", &arr[i].val);
    addToA(arr[i].val, i);
  }
  sort(s_arr + 1, s_arr + 1 + s_ptr);
  printf("%d\n", countMoves());
}
int main() {
  program();
  return 0;
}