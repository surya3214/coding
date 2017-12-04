// AC
#include <iostream>
#include <cstdio>
#define N_MAX 1010
#define INF 1E9
#define MAX_BITMASK 1024
using namespace std;
int n, m, k, max_k, front, rear, ans;
int dp[N_MAX][MAX_BITMASK];
int fishes_in[N_MAX];
int two_powers[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
struct node {
  int market, dist, bit_mask;
} queue[N_MAX * N_MAX * N_MAX / 50];
struct list {
  int neighbor;
  int dist;
  struct list *next;
};
struct {
  struct list *paths;
} centres[N_MAX];
struct list *insert(int u, int v, int dist) {
  struct list *t = new struct list;
  t->neighbor = v;
  t->dist = dist;
  t->next = centres[u].paths;
  return t;
}
bool isEmpty() {
  if (front == rear)
    return true;
  return false;
}
void enqueue(int market, int dist, int bit_mask) {
  queue[rear].market = market;
  queue[rear].dist = dist;
  queue[rear].bit_mask = bit_mask;
  rear++;
}
void dequeue() {
  front++;
}
void compute() {
  dp[1][fishes_in[1]] = 0;
  enqueue(1, 0, fishes_in[1]);
  struct node *t;
  int to_v, to_dist, to_bitmask;
  while (!isEmpty()) {
    t = &queue[front];
    dequeue();
    for (struct list *l = centres[t->market].paths; l != NULL; l = l->next) {
      to_v = l->neighbor;
      to_dist = t->dist + l->dist;
      to_bitmask = t->bit_mask | fishes_in[to_v];
      if (dp[to_v][to_bitmask] > to_dist) {
        dp[to_v][to_bitmask] = to_dist;
        enqueue(to_v, to_dist, to_bitmask);
      }
    }
  }
}
void reset() {
  front = rear = 0;
  max_k = two_powers[k];
  ans = INF;
}
void program() {
  int cnt, tmp, u, v, dist;
  scanf("%d %d %d", &n, &m, &k);
  reset();
  for (int i = 1; i <= n; i++) {
    scanf("%d", &cnt);
    centres[i].paths = NULL;
    for (int j = 0; j < cnt; j++) {
      scanf("%d", &tmp);
      fishes_in[i] |= (1 << (tmp - 1));
    }
    for (int k = 0; k < max_k; k++)
      dp[i][k] = INF;
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &u, &v, &dist);
    centres[u].paths = insert(u, v, dist);
    centres[v].paths = insert(v, u, dist);
  }
  compute();
  for (int i = 0; i < max_k; i++) {
    for (int j = 0; j < max_k; j++) {
      if ((i | j) == (max_k - 1))
        ans = min(ans, max(dp[n][i], dp[n][j]));
    }
  }
  printf("%d\n", ans);
}
int main() {
  freopen("SynchronousShopping_input.txt", "r", stdin);
  program();
  return 0;
}