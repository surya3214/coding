// AC Treap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define NODES_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct N {
  int val;
  int priority;
  int s_height;
  struct N *l, *r;
} t_nodes_pool[BUFF(NODES_MAX)], *root;
int t_n_ptr;
int linearized_tree[BUFF(NODES_MAX)];
int l_ptr;
typedef struct N* pnode;
pnode getTNodesFromPool(int val) {
  pnode p = &t_nodes_pool[t_n_ptr++];
  p->val = val;
  p->priority = rand();
  p->s_height = 1;
  p->l = p->r = NULL;
  return p;
}
int getSHeight(pnode t) { return t ? t->s_height : 0; }
void updateNode(pnode t) {
  if (t)
    t->s_height = getSHeight(t->l) + 1 + getSHeight(t->r);
}
void Merge(pnode l, pnode r, pnode &t) {
  if (!l)
    t = r;
  else if (!r)
    t = l;
  else if (l->priority > r->priority)
    Merge(l->r, r, l->r), t = l;
  else Merge(l, r->l, r->l), t = r;
  updateNode(t);
}
void Split(pnode t, pnode &l, pnode &r, int k) {
  if (!t)
    l = r = NULL;
  else {
    int rel_pos = getSHeight(t->l) + 1;
    if (rel_pos <= k)
      Split(t->r, t->r, r, k - rel_pos), l = t;
    else Split(t->l, l, t->l, k), r = t;
    updateNode(t);
  }
}
void addToTreap(int x) {
  pnode p = getTNodesFromPool(x);
  Merge(root, p, root);
}
void reorderTreap(int l, int r, bool type) {
  pnode l1, r1;
  Split(root, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  Merge(l1, r2, l1);
  if (type)
    Merge(l2, l1, root);
  else Merge(l1, l2, root);
}
void addToLinearizedTree(int val) {
  ++l_ptr;
  linearized_tree[l_ptr] = val;
}
void linearizeTree(pnode t) {
  if (!t) return;
  linearizeTree(t->l);
  addToLinearizedTree(t->val);
  linearizeTree(t->r);
}
int t_abs(int x) { return x >= 0 ? x : -x; }
void program() {
  int n, m;
  int type, l, r;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &type);
    addToTreap(type);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &type, &l, &r);
    reorderTreap(l, r, type == 1);
  }
  linearizeTree(root);
  printf("%d\n", t_abs(linearized_tree[l_ptr] - linearized_tree[1]));
  for (int i = 1; i <= l_ptr; ++i)
    printf("%d ", linearized_tree[i]);
}
int main() {
  program();
  return 0;
}