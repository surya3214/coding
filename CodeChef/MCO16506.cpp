// AC Treap Ayyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(N_MAX)];
struct N {
  int priority;
  int s_size;
  int val;
  bool lazy_reverse;
  int lazy_shift;
  N *l, *r;
} *root, n_nodes_pool[BUFF(N_MAX)];
int n_ptr;
typedef struct N* pnode;
int getIndexFromChar(char x) { return x - 'a'; }
pnode getNNodesFromPool(char val) {
  pnode p = &n_nodes_pool[n_ptr++];
  p->priority = rand();
  p->val = getIndexFromChar(val);
  p->s_size = 1;
  p->lazy_reverse = false;
  p->lazy_shift = 0;
  p->l = p->r = NULL;
  return p;
}
void reverseNode(pnode &t) {
  pnode tmp;
  tmp = t->l;
  t->l = t->r;
  t->r = tmp;
  if (t->l) t->l->lazy_reverse = !t->l->lazy_reverse;
  if (t->r) t->r->lazy_reverse = !t->r->lazy_reverse;
  t->lazy_reverse = false;
}
void applyShift(pnode &t) {
  t->val = (t->val + t->lazy_shift) % 26;
  if (t->l)
    t->l->lazy_shift = (t->l->lazy_shift + t->lazy_shift) % 26;
  if (t->r)
    t->r->lazy_shift = (t->r->lazy_shift + t->lazy_shift) % 26;
  t->lazy_shift = 0;
}
void sanitizeNode(pnode t) {
  if (t) {
    if (t->lazy_reverse)
      reverseNode(t);
    if (t->lazy_shift)
      applyShift(t);
  }
}
int getSSize(pnode t) { return t ? t->s_size : 0; }
void updateNode(pnode &t) {
  if (t)
    t->s_size = getSSize(t->l) + 1 + getSSize(t->r);
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
void Split(pnode t, pnode &l, pnode &r, int pos) {
  if (!t)
    l = r = NULL;
  else {
    sanitizeNode(t);
    int cur_pos = getSSize(t->l) + 1;
    if (cur_pos <= pos)
      Split(t->r, t->r, r, pos - cur_pos), l = t;
    else Split(t->l, l, t->l, pos), r = t;
    updateNode(t);
  }
}
void CutAndPaste(pnode &t, int l, int r, int pos) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  Merge(l1, r2, r2);
  Split(r2, l1, r1, pos);
  Merge(l1, l2, l1);
  Merge(l1, r1, t);
}
void ApplyShift(pnode &t, int l, int r, int c) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  l2->lazy_shift = (l2->lazy_shift + c) % 26;
  Merge(l2, r2, r1);
  Merge(l1, r1, t);
}
void ApplyReverse(pnode &t, int l, int r) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  l2->lazy_reverse = !l2->lazy_reverse;
  Merge(l2, r2, r1);
  Merge(l1, r1, t);
}
void PrintString(pnode &t) {
  if (!t) return;
  sanitizeNode(t);
  PrintString(t->l);
  printf("%c", 'a' + t->val);
  PrintString(t->r);
}
void BuildTreap() {
  for (int i = 0; str[i]; ++i)
    Merge(root, getNNodesFromPool(str[i]), root);
}
void program() {
  scanf("%s", str);
  BuildTreap();
  int q, type, l, r, c, pos;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &type, &l, &r);
    switch (type) {
      case 1:
        scanf("%d", &pos);
        CutAndPaste(root, l, r, pos);
        break;
      case 2:
        scanf("%d", &c);
        ApplyShift(root, l, r, c);
        break;
      case 3:
        ApplyReverse(root, l, r);
        break;
    }
  }
  PrintString(root);
  printf("\n");
}
int main() {
  program();
  return 0;
}