// AC Holy heck! Treap
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#define ALPHA_CHARS_MAX 26
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct N {
  int x;
  int priority;
  int s_height;
  int lazy_update;
  int presence[BUFF(ALPHA_CHARS_MAX)];
  struct N *l, *r;
} *root, n_nodes_pool[BUFF(LEN_MAX)];
int n_nodes_ptr;
typedef struct N* pnode;
int getIndexFromChar(char x) { return x - 'a' + 1; }
pnode getNNodesFromPool(int val) {
  pnode p = &n_nodes_pool[n_nodes_ptr++];
  p->x = val;
  p->priority = rand();
  p->s_height = 1;
  p->l = p->r = NULL;
  ++p->presence[p->x];
  return p;
}
int getSHeight(pnode t) { return t ? t->s_height : 0; }
int getXPresence(int x, pnode t) { return t ? t->presence[x] : 0; }
void updateNode(pnode t) {
  if (t) {
    t->s_height = getSHeight(t->l) + 1 + getSHeight(t->r);
    for (int x = 1; x <= ALPHA_CHARS_MAX; ++x)
      t->presence[x] = getXPresence(x, t->l) + getXPresence(x, t->r);
    ++t->presence[t->x];
  }
}
void markLazy(pnode t, int x) {
  if (!t) return;
  t->x = x;
  for (int x = 1; x <= ALPHA_CHARS_MAX; ++x)
    t->presence[x] = 0;
  t->presence[t->x] = t->s_height;
  t->lazy_update = x;
}
void propagateLazy(pnode t) {
  if (!t) return;
  if (t->lazy_update) {
    markLazy(t->l, t->lazy_update);
    markLazy(t->r, t->lazy_update);
    t->lazy_update = 0;
  }
}
void Merge(pnode l, pnode r, pnode &t) {
  propagateLazy(l);
  propagateLazy(r);
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->priority > r->priority)
    Merge(l->r, r, l->r), t = l;
  else Merge(l, r->l, r->l), t = r;
  updateNode(t);
}
void insert(pnode &t, pnode cur) {
  Merge(t, cur, t);
}
void insertIntoTreap(int val) {
  pnode p = getNNodesFromPool(val);
  insert(root, p);
}
void buildTreap() {
  for (int i = 0; str[i]; ++i)
    insertIntoTreap(getIndexFromChar(str[i]));
}
void Split(pnode t, pnode &l, pnode &r, int pos) {
  if (!t) l = r = NULL;
  else {
    propagateLazy(t);
    int cur_pos = getSHeight(t->l) + 1;
    if (cur_pos <= pos) // t goes to l
      Split(t->r, t->r, r, pos - cur_pos), l = t;
    else Split(t->l, l, t->l, pos), r = t;
    updateNode(t);
  }
}
void update(int l, int r, int x) {
  pnode l1, r1;
  Split(root, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  markLazy(l2, x);
  Merge(l2, r2, r1);
  Merge(l1, r1, root);
}
int getKthIndexOfC(pnode t, int k, int x, int add = 0) {
  if (!t) return -1;
  propagateLazy(t);
  int x_found = getXPresence(x, t->l) + (t->x == x);
  if (t->x == x && x_found == k)
    return add + getSHeight(t->l) + 1;
  else if (x_found < k)
    return getKthIndexOfC(t->r, k - x_found, x, add + getSHeight(t->l) + 1);
  else return getKthIndexOfC(t->l, k, x, add);
}
int printKthC(int k, int x) {
  if (getXPresence(x, root) < k) return -1;
  return getKthIndexOfC(root, k, x);
}
void program() {
  scanf("%s", str);
  buildTreap();
  int q, type, l, r, x, k;
  char c;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &type);
    if (type) {
      scanf("%d %c", &k, &c);
      x = getIndexFromChar(c);
      printf("%d\n", printKthC(k, x));
    } else {
      scanf("%d %d %c", &l, &r, &c);
      x = getIndexFromChar(c);
      update(l, r, x);
    }
  }
}
int main() {
  program();
  return 0;
}