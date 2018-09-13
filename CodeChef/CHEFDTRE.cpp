// AC Treap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define Q_MAX (2 * 100000)
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, s_id;
struct N {
  int s_size;
  int priority;
  int val;
  int max, min;
  N *l, *r;
} *sets[BUFF(N_MAX + Q_MAX)], n_nodes_pool[BUFF(N_MAX)];
typedef struct N* pnode;
int n_ptr;
pnode getNNodesFromPool(int val) {
  pnode p = &n_nodes_pool[n_ptr++];
  p->s_size = 1;
  p->priority = rand();
  p->val = p->max = p->min = val;
  p->l = p->r = NULL;
  return p;
}
int getSSize(pnode t) { return t ? t->s_size : 0; }
int getMin(pnode t) { return t ? t->min : INT_MAX; }
int getMax(pnode t) { return t ? t->max : INT_MIN; }
void updateNode(pnode t) {
  if (t) {
    t->s_size = getSSize(t->l) + 1 + getSSize(t->r);
    t->max = max(t->val, max(getMax(t->l), getMax(t->r)));
    t->min = min(t->val, min(getMin(t->l), getMin(t->r)));
  }
}
void Merge(pnode l, pnode r, pnode &t) {
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->priority > r->priority)
    Merge(l->r, r, l->r), t = l;
  else Merge(l, r->l, r->l), t = r;
  updateNode(t);
}
void Split(pnode t, pnode &l, pnode &r, int key) {
  if (!t)
    l = r = NULL;
  else {
    if (t->val <= key)
      Split(t->r, t->r, r, key), l = t;
    else Split(t->l, l, t->l, key), r = t;
    updateNode(t);
  }
}
void Union(pnode l, pnode r, pnode &t) {
  if (!l) t = r;
  else if (!r) t = l;
  else {
    if (l->priority < r->priority)
      swap(l, r);
    pnode l1, r1;
    Split(r, l1, r1, l->val);
    Union(l->l, l1, l->l);
    Union(l->r, r1, l->r);
    t = l;
    updateNode(t);
  }
}
int Kth(pnode x, int k) {
  if (getSSize(x->l) + 1 == k)
    return x->val;
  else if (getSSize(x->l) < k)
    return Kth(x->r, k - getSSize(x->l) - 1);
  else return Kth(x->l, k);
}
void program() {
  int q;
  scanf("%d %d", &n, &q);
  s_id = n;
  for (int i = 1; i <= n; ++i)
    sets[i] = getNNodesFromPool(i);
  char op[10];
  int l, r;
  for (int i = 1; i <= q; ++i) {
    scanf("%s %d %d", op, &l, &r);
    if (op[0] == 'U') {
      Union(sets[l], sets[r], sets[++s_id]);
      sets[l] = sets[r] = NULL;
    } else if (op[0] == 'G')
      printf("%d\n", Kth(sets[l], r));
  }
}
int main() {
  program();
  return 0;
}