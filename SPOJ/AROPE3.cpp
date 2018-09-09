// AC Treap Ayyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct N {
  bool lazy;
  int priority;
  char x;
  int s_height;
  N *l, *r;
} nodes_pool[BUFF(LEN_MAX)], *root;
typedef struct N* pnode;
int nodes_ptr;
pnode getNNodesFromPool(char val) {
  pnode p = &nodes_pool[nodes_ptr++];
  p->priority = rand();
  p->x = val;
  p->s_height = 1;
  p->lazy = false;
  p->l = p->r = NULL;
  return p;
}
void reverseNode(pnode t) {
  if (!t) return;
  pnode tmp = t->l;
  t->l = t->r;
  t->r = tmp;
  if (t->l) t->l->lazy = !t->l->lazy;
  if (t->r) t->r->lazy = !t->r->lazy;
}
void sanitizeNode(pnode t) {
  if (!t) return;
  if (t->lazy) {
    reverseNode(t);
    t->lazy = false;
  }
}
int getSHeight(pnode t) { return t ? t->s_height : 0; }
void updateNode(pnode t) {
  sanitizeNode(t);
  if (t)
    t->s_height = getSHeight(t->l) + 1 + getSHeight(t->r);
}
void Merge(pnode l, pnode r, pnode &t) {
  sanitizeNode(l);
  sanitizeNode(r);
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->priority > r->priority)
    Merge(l->r, r, l->r), t = l;
  else Merge(l, r->l, r->l), t = r;
  updateNode(t);
}
void Split(pnode t, pnode &l, pnode &r, int pos, int add) {
  if (!t)
    l = r = NULL;
  else {
    sanitizeNode(t);
    int cur_pos = add + getSHeight(t->l) + 1;
    if (cur_pos <= pos)
      Split(t->r, t->r, r, pos, cur_pos), l = t;
    else Split(t->l, l, t->l, pos, add), r = t;
    updateNode(t);
  }
}
void SplitReverseAndMerge(pnode &t, int l, int r, bool type) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1, 0);
  Merge(l1, r2, l1);
  reverseNode(l2);
  if (type) // front
    Merge(l2, l1, t);
  else Merge(l1, l2, t);
}
char query(pnode &t, int pos) {
  pnode l1, r1;
  Split(t, l1, r1, pos - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, 1, 0);
  char ret = l2->x;
  Merge(l2, r2, r1);
  Merge(l1, r1, t);
  return ret;
}
void insertIntoTreap(char val) {
  pnode p = getNNodesFromPool(val);
  Merge(root, p, root);
}
void buildTreap() {
  for (int i = 0; str[i]; ++i)
    insertIntoTreap(str[i]);
}
void program() {
  scanf("%s", str);
  buildTreap();
  int q, type, x, y;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &type);
    if (type == 3) {
      scanf("%d", &x);
      ++x;
      printf("%c\n", query(root, x));
    } else {
      scanf("%d %d", &x, &y);
      ++x; ++y;
      SplitReverseAndMerge(root, x, y, type == 1);
    }
  }
}
int main() {
  program();
  return 0;
}