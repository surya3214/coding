// AC Graph Theory, Easy, BFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int f, s, g, u, d;
struct {
  bool visited;
  int moves;
} floors[BUFF(N_MAX)];
queue<int> q;
void pushToQueue(int u, int moves) {
  floors[u].visited = true;
  floors[u].moves = moves;
  q.push(u);
}
bool isPossible(int x) {
  if (x >= 1 && x <= f && !floors[x].visited)
    return true;
  return false;
}
void bfs() {
  int c, next;
  for (pushToQueue(s, 0); !q.empty(); q.pop()) {
    c = q.front();
    if (c == g)
      return;
    next = c + u;
    if (isPossible(next))
      pushToQueue(next, floors[c].moves + 1);
    next = c - d;
    if (isPossible(next))
      pushToQueue(next, floors[c].moves + 1);
  }
}
void program() {
  scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
  bfs();
  if (floors[g].visited)
    printf("%d\n", floors[g].moves);
  else printf("use the stairs\n");
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}