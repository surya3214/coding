// AC Queue, Reverse BFS
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e6
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int dist[BUFF(N_MAX)];
int bfs(int x) {
  memset(dist, 0, sizeof(dist));
  queue<int> q;
  q.push(x);
  dist[x] = 1;
  int cur, next;
  while (1) {
    cur = q.front();
    q.pop();
    if (!dist[cur - 1]) {
      dist[cur - 1] = 1 + dist[cur];
      if (cur - 1 == 0)
        break;
      q.push(cur - 1);
    }
    for (int i = 2; i * i <= cur; ++i) {
      if (!(cur % i)) {
        next = max(i, cur / i);
        if (!dist[next]) {
          dist[next] = 1 + dist[cur];
          q.push(next);
        }
      }
    }
  }
  return dist[0] - 1;
}
void program() {
  int q, n;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &n);
    if (n)
      printf("%d\n", bfs(n));
    else printf("0\n");
  }
}
int main() {
  program();
  return 0;
}