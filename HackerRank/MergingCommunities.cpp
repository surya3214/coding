// AC Union Find
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e5)
#pragma GCC optimize "O0"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  int parent;
  int count;
} nodes[BUFF(N_MAX)];
void init() {
  for (int i = 1; i <= n; ++i) {
    nodes[i].parent = i;
    nodes[i].count = 1;
  }
}
int findParent(int x) {
  if (nodes[x].parent != x)
    nodes[x].parent = findParent(nodes[x].parent);
  return nodes[x].parent;
}
void program() {
  int q, x, y, p1, p2;
  char type;
  scanf("%d %d", &n, &q);
  init();
  for (int i = 1; i <= q; ++i) {
    scanf(" %c", &type);
    if (type == 'Q') {
      scanf("%d", &x);
      p1 = findParent(x);
      printf("%d\n", nodes[p1].count);
    } else if (type == 'M') {
      scanf("%d %d", &x, &y);
      p1 = findParent(x);
      p2 = findParent(y);
      if (p1 != p2) {
        nodes[p2].parent = p1;
        nodes[p1].count += nodes[p2].count;
      }
    }
  }
}
int main() {
  program();
  return 0;
}