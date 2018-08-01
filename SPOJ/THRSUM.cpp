// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
using namespace std;
typedef long long int ll;
int input[BUFF(N_MAX)];
struct {
  int a, b, c;
} ans[BUFF(N_MAX * N_MAX)];
int rear;
int n;
void reset() { rear = 0; }
void addToAnswer(int a, int b, int c) {
  ++rear;
  ans[rear].a = a;
  ans[rear].b = b;
  ans[rear].c = c;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int search(int l, int r, int x) {
  int mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (input[mid] >= x)
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void compute() {
  int a_idx, b_idx, c_idx;
  int next_a, next_b;
  a_idx = 1;
  int req;
  while (a_idx <= n && input[a_idx] <= 0) {
    next_a = input[a_idx];
    b_idx = search(a_idx + 1, n, next_a);
    while (b_idx <= n) {
      req = input[a_idx] + input[b_idx];
      c_idx = search(b_idx + 1, n, -req);
      if (c_idx <= n && req + input[c_idx] == 0)
        addToAnswer(input[a_idx], input[b_idx], input[c_idx]);
      b_idx = search(b_idx + 1, n, input[b_idx] + 1);
    }
    a_idx = search(a_idx + 1, n, input[a_idx] + 1);
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <=n; ++i)
      scanf("%d", &input[i]);
    sort(input + 1, input + 1 + n);
    compute();
    printf("%d\n", rear);
    for (int i = 1; i <= rear; ++i)
      printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
  }
}
int main() {
  program();
  return 0;
}