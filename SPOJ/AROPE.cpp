// AC Treap Ayyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct N {
  char x;
  int priority;
  int sub_height;
  struct N *l, *r;
} *root, nodes_pool[BUFF(LEN_MAX)];
typedef struct N* pnode;
int nodes_ptr;
pnode getNNodesFromPool(char val) {
  pnode p = &nodes_pool[nodes_ptr++];
  p->l = p->r = NULL;
  p->priority = rand();
  p->sub_height = 1;
  p->x = val;
  return p;
}
int getSubHeight(pnode t) { return t ? t->sub_height : 0; }
void updateNode(pnode &t) {
  if (t)
    t->sub_height = getSubHeight(t->l) + 1 + getSubHeight(t->r);
}
void Merge(pnode &t, pnode l, pnode r) {
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->priority > r->priority)
    Merge(l->r, l->r, r), t = l;
  else Merge(r->l, l, r->l), t = r;
  updateNode(t);
}
void insert(pnode &t, pnode cur) {
  Merge(t, t, cur);
}
void insertIntoTreap(char val) {
  pnode p = getNNodesFromPool(val);
  insert(root, p);
}
void buildTreap() {
  for (int i = 0; str[i]; ++i)
    insertIntoTreap(str[i]);
}
void Split(pnode t, pnode &l, pnode &r, int pos, int add) {
  if (!t)
    l = r = NULL;
  else {
    int cur_pos = add + getSubHeight(t->l) + 1; // implicit key
    if (cur_pos <= pos)
      Split(t->r, t->r, r, pos, cur_pos), l = t;
    else Split(t->l, l, t->l, pos, add), r = t;
    updateNode(t);
  }
}
void SplitAndMerge(pnode &t, int l, int r, bool type) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1, 0);
  Merge(l1, l1, r2);
  if (type) // stitch it in front
    Merge(t, l2, l1);
  else // stitch it in back
    Merge(t, l1, l2);
}
char query(pnode &t, int pos) {
  pnode l1, r1;
  Split(t, l1, r1, pos - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, 1, 0);
  char ret = l2->x;
  Merge(r1, l2, r2);
  Merge(t, l1, r1);
  return ret;
}
void program() {
  int q, type, x, y;
  scanf("%s", str);
  buildTreap();
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
      SplitAndMerge(root, x, y, type == 1);
    }
  }
}
int main() {
  program();
  return 0;
}