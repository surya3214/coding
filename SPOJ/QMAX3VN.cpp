// AC Treap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct N {
  int height; // actual value at node's position
  int priority; // rand()
  int subtree_max_height; // best value in the subtree
  int subtree_size; // size of the subtree
  N *l, *r; // children
} nodes_pool[BUFF(N_MAX)], *root;
int node_ptr;
typedef N* pnode;
pnode getNNodesFromPool(int h) {
  pnode t = &nodes_pool[node_ptr++];
  t->height = h;
  t->priority = rand();
  t->subtree_max_height = t->height;
  t->subtree_size = 1;
  t->l = t->r = NULL;
  return t;
}
int getSubtreeSize(pnode t) { return t ? t->subtree_size : 0; }
int getSubtreeHeight(pnode t) { return t ? t->subtree_max_height : INT_MIN; }
void updateNode(pnode t) {
  if (t) {
    t->subtree_size = getSubtreeSize(t->l) + 1 + getSubtreeSize(t->r);
    t->subtree_max_height = max(getSubtreeHeight(t->l), max(t->height, getSubtreeHeight(t->r)));
  }
}
void Split(pnode t, pnode &l, pnode &r, int pos, int add) {
  if (!t)
    l = r = NULL;
  else {
    int cur_pos = add + getSubtreeSize(t->l) + 1; // implicit key
    if (cur_pos <= pos)
      Split(t->r, t->r, r, pos, cur_pos), l = t;
    else Split(t->l, l, t->l, pos, add), r = t;
    updateNode(t);
  }
}
void Merge(pnode &t, pnode l, pnode r) {
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->priority > r->priority)
    Merge(l->r, l->r, r), t = l;
  else Merge(r->l, l, r->l), t = r;
  updateNode(t);
}
void Insert(pnode &t, pnode cur, int pos) {
  pnode l1, r1;
  Split(t, l1, r1, pos - 1, 0);
  Merge(l1, l1, cur);
  Merge(t, l1, r1);
}
void insertIntoTreap(pnode &t, int pos, int h) {
  pnode p = getNNodesFromPool(h);
  Insert(t, p, pos);
}
int query(pnode &t, int l, int r) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1, 0);
  int ret = getSubtreeHeight(l2);
  Merge(r1, l2, r2);
  Merge(t, l1, r1);
  return ret;
}
void program() {
  int q, l, r;
  char type;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf(" %c %d %d", &type, &l, &r);
    switch (type) {
      case 'A':
        insertIntoTreap(root, r, l);
        break;
      case 'Q':
        printf("%d\n", query(root, l, r));
        break;
    }
  }
}
int main() {
  program();
  return 0;
}