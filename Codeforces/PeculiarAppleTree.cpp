// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
using namespace std;
int n;
int top;
int max_depth;
struct L {
  int idx;
  struct L *next;
} nodes[BUFF(N_MAX)];
struct {
  struct L *front;
} my_list[BUFF(N_MAX)];
int foundAtDepth[BUFF(N_MAX)];
void addChild(int p, int c) {
  struct L *t = &nodes[top++];
  t->idx = c;
  t->next = my_list[p].front;
  my_list[p].front = t;
}
void bfs(int node_idx, int depth) {
  max_depth = max(max_depth, depth);
  foundAtDepth[depth]++;
  struct L *t = my_list[node_idx].front;
  while (t) {
    bfs(t->idx, depth + 1);
    t = t->next;
  }
}
void program() {
  int parent;
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &parent);
    addChild(parent, i);
  }
  int ans = 0;
  bfs(1, 1);
  for (int i = 1; i <= max_depth; i++)
    ans += foundAtDepth[i] % 2;
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}