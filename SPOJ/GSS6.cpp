// AC Treap Ayyyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define Q_MAX 100000
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
int inp[BUFF(N_MAX)];
struct N {
  int priority;
  int val;
  int s_size;
  int best_sum, p_sum, s_sum, t_sum;
  N *l, *r;
} n_nodes_pool[BUFF(N_MAX + Q_MAX)], *root;
typedef struct N* pnode;
int n_ptr;
pnode getNNodesFromPool(int val) {
  pnode p = &n_nodes_pool[n_ptr++];
  p->priority = rand();
  p->val = val;
  p->s_size = 1;
  p->best_sum = p->p_sum = p->s_sum = p->t_sum = val;
  p->l = p->r = NULL;
  return p;
}
int getSSize(pnode t) { return t ? t->s_size : 0; }
int getTotalSum(pnode t) { return t ? t->t_sum : 0; }
int getBestSum(pnode t) { return t ? t->best_sum : INT_MIN; }
int getPrefixSum(pnode t) { return t ? t->p_sum : INT_MIN; }
int getSuffixSum(pnode t) { return t ? t->s_sum : INT_MIN; }
void updateNode(pnode t) {
  if (t) {
    t->s_size = getSSize(t->l) + 1 + getSSize(t->r);
    t->t_sum = t->val + getTotalSum(t->l) + getTotalSum(t->r);
    t->p_sum = max(getPrefixSum(t->l), getTotalSum(t->l) + t->val + max(0, getPrefixSum(t->r)));
    t->s_sum = max(getSuffixSum(t->r), getTotalSum(t->r) + t->val + max(0, getSuffixSum(t->l)));
    t->best_sum = t->val + max(0, getSuffixSum(t->l)) + max(0, getPrefixSum(t->r));
    t->best_sum = max(t->best_sum, max(getBestSum(t->l), getBestSum(t->r)));
    t->best_sum = max(t->best_sum, max(t->t_sum, max(t->p_sum, t->s_sum)));
  }
}
void Split(pnode t, pnode &l, pnode &r, int pos) {
  if (!t)
    l = r = NULL;
  else {
    int cur_pos = getSSize(t->l) + 1;
    if (cur_pos <= pos)
      Split(t->r, t->r, r, pos - cur_pos), l = t;
    else Split(t->l, l, t->l, pos), r = t;
    updateNode(t);
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
void Add(pnode p, int pos) {
  pnode l1, r1;
  Split(root, l1, r1, pos - 1);
  Merge(p, r1, r1);
  Merge(l1, r1, root);
}
void addToTreap(int pos, int val) {
  pnode p = getNNodesFromPool(val);
  Add(p, pos);
}
void Delete(int pos) {
  pnode l1, r1;
  Split(root, l1, r1, pos - 1);
  pnode l2, r2;
  Split(r1, l2, r2, 1);
  Merge(l1, r2, root);
}
void Replace(pnode t, int pos, int val) {
  if (t) {
    int cur_pos = getSSize(t->l) + 1;
    if (cur_pos == pos)
      t->val = val;
    else if (cur_pos < pos)
      Replace(t->r, pos - cur_pos, val);
    else Replace(t->l, pos, val);
    updateNode(t);
  }
}
int Query(int l, int r) {
  pnode l1, r1;
  Split(root, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  int ret = l2->best_sum;
  Merge(l2, r2, r1);
  Merge(l1, r1, root);
  return ret;
}
void t_swap(int &x, int &y) {
  if (x > y) {
    int tmp = x;
    x = y;
    y = tmp;
  }
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &inp[i]);
    Merge(root, getNNodesFromPool(inp[i]), root);
  }
  int q, x, y;
  char type;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf(" %c", &type);
    if (type == 'D') {
      scanf("%d", &x);
      Delete(x);
    } else {
      scanf("%d %d", &x, &y);
      switch (type) {
        case 'I':
          addToTreap(x, y);
          break;
        case 'R':
          Replace(root, x, y);
          break;
        case 'Q':
          t_swap(x, y);
          printf("%d\n", Query(x, y));
          break;
      }
    }
  }
}
int main() {
  program();
  return 0;
}