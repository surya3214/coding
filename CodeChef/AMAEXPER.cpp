// WA
#include <iostream>
#include <cstdio>
#define N_MAX 100010
using namespace std;
typedef long long int ll;
ll ans[N_MAX];
struct list {
  ll v, w;
  struct list *next;
};
struct Node {
  ll max1, max2;
  struct list *edges;
} nodes[N_MAX];
int n;
void reset() {
  for (int i = 0; i <= n; i++) {
    nodes[i].edges = NULL;
    nodes[i].max1 = nodes[i].max2 = -1;
  }
}
struct list *createEdge(int u, int v, int w) {
  struct list *t = new struct list;
  t->v = v;
  t->w = w;
  t->next = nodes[u].edges;
  return t;
}
void calculate(int u, ll upward_dist, struct Node *p) {
  struct Node *q;
  struct list *t = p->edges;
  ll tmp;
  tmp = max(upward_dist, p->max1);
  if (tmp <= ans[u])
    ans[u] = tmp;
  else return;
  while (t) {
    q = &nodes[t->v];
    if ((t->w + q->max1) == p->max1) // this is one of the max1 branches; needs vetting nodes in the branch
      calculate(u, upward_dist + t->w, q);
    t = t->next;
  }
}
void traverse(int u, struct Node *p) {
  struct Node *q;
  struct list *t = p->edges;
  ll tmp;
  if (!t)
    p->max1 = ans[u] = 0;
  else {
    while (t) {
      q = &nodes[t->v];
      traverse(t->v, q);
      if (p->max1 == -1)
        p->max1 = t->w + q->max1;
      else {
        tmp = t->w + q->max1;
        if (p->max2 == -1) {
          p->max2 = min(p->max1, tmp);
          p->max1 = max(p->max1, tmp);
        } else {
          if (p->max1 <= tmp)
            p->max2 = p->max1, p->max1 = tmp;
          else p->max2 = max(p->max2, tmp);
        }
      }
      t = t->next;
    }
  }
}
void calculateUtil(int u, Node *p) {
  struct Node *q;
  struct list *t = p->edges;
  // find the min value - ans[u] rooted at p
  ans[u] = p->max1;
  while (t) {
    q = &nodes[t->v];
    if ((t->w + q->max1) == p->max1) {
      // this is one of the max1 branches; needs vetting nodes in the branch
      if (p->max2 == -1)
        calculate(u, t->w, q);
      else calculate(u, t->w + p->max2, q);
    }
    t = t->next;
  }
}
void compute() {
  traverse(1, &nodes[1]);
  for (int i = 1; i <= n; i++)
    calculateUtil(i, &nodes[i]);
}
void program() {
  int t, u, v, w;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    reset();
    for (int i = 1; i < n; i++) {
      scanf("%d %d %d", &u, &v, &w);
      nodes[u].edges = createEdge(u, v, w);
    }
    compute();
    for (int i = 1; i <= n; i++)
      printf("%lld\n", ans[i]);
  }
}
int main() {
  program();
  return 0;
}