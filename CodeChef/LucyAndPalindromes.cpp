// AC Treap Combinatorics Ayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy! First Attempt!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define MOD (int) (1e9 + 7)
#define ALPHA_CHARS_MAX 10
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int fact[BUFF(N_MAX)];
int rfact[BUFF(N_MAX)];
int n;
char str[BUFF(N_MAX)];
struct N {
  int priority;
  int val;
  int s_size;
  bool lazy;
  int cnt[BUFF(ALPHA_CHARS_MAX)];
  struct N *l, *r;
} n_nodes_pool[BUFF(N_MAX)], *root;
int n_ptr;
typedef struct N* pnode;
int getIndexFromChar(char x) { return x - 'a' + 1; }
pnode getNNodesFromPool(int x) {
  pnode p = &n_nodes_pool[n_ptr++];
  p->priority = rand();
  p->s_size = 1;
  p->val = x;
  ++p->cnt[x];
  p->lazy = false;
  p->l = p->r = NULL;
  return p;
}
struct {
  int cnt[BUFF(ALPHA_CHARS_MAX)];
} buffer;
void resetBuffer() { memset(buffer.cnt, 0, sizeof(buffer.cnt)); }
void updateBuffer(pnode t) {
  if (t) {
    for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
      buffer.cnt[i] += t->cnt[i];
  }
}
int getSSize(pnode t) { return t ? t->s_size : 0; }
void updateNode(pnode &t) {
  if (t) {
    t->s_size = getSSize(t->l) + 1 + getSSize(t->r);
    resetBuffer();
    updateBuffer(t->l);
    updateBuffer(t->r);
    for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
      t->cnt[i] = buffer.cnt[i];
    int x = t->val;
    ++t->cnt[x];
  }
}
void reverseNode(pnode t) {
  if (!t) return;
  pnode tmp = t->l;
  t->l = t->r;
  t->r = tmp;
  if (t->l) t->l->lazy = !t->l->lazy;
  if (t->r) t->r->lazy = !t->r->lazy;
  t->lazy = !t->lazy;
}
void propagateLazy(pnode &t) {
  if (t && t->lazy)
    reverseNode(t);
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
void addToTreap(pnode &t, char x) {
  pnode p = getNNodesFromPool(getIndexFromChar(x));
  Merge(t, p, t);
}
void buildTreap() {
  for (int i = 0; str[i]; ++i)
    addToTreap(root, str[i]);
}
void Split(pnode t, pnode &l, pnode &r, int pos) {
  if (!t)
    l = r = NULL;
  else {
    propagateLazy(t);
    int cur = getSSize(t->l) + 1;
    if (cur <= pos)
      Split(t->r, t->r, r, pos - cur), l = t;
    else Split(t->l, l, t->l, pos), r = t;
    updateNode(t);
  }
}
ll compute(pnode t) {
  resetBuffer();
  updateBuffer(t);
  int even_cnt, odd_cnt;
  even_cnt = odd_cnt = 0;
  ll ret = 1;
  for (int i = 1; i <= ALPHA_CHARS_MAX; ++i) {
    if (buffer.cnt[i] & 1) {
      if (odd_cnt) return 0;
      ++odd_cnt;
    }
    even_cnt += buffer.cnt[i] / 2;
    ret = (ret * rfact[buffer.cnt[i] / 2]) % MOD;
  }
  ret = (ret * fact[even_cnt]) % MOD;
  return ret;
}
int compute(int l, int r) {
  pnode l1, r1;
  Split(root, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  int ret = compute(l2);
  Merge(l2, r2, r1);
  Merge(l1, r1, root);
  return ret;
}
void reverse(int l, int r) {
  pnode l1, r1;
  Split(root, l1, r1, l - 1);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1);
  l2->lazy = !l2->lazy;
  Merge(l2, r2, r1);
  Merge(l1, r1, root);
}
void program() {
  int q, type, l, r;
  scanf("%d %d", &n, &q);
  scanf("%s", str);
  buildTreap();
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &type, &l, &r);
    switch (type) {
      case 1:
        reverse(l, r);
        break;
      case 2:
        printf("%d\n", compute(l, r));
        break;
    }
  }
}
int power(int x, int y) {
  if (!y)
    return 1;
  if (y & 1)
    return (1LL * x * power(x, y - 1)) % MOD;
  else {
    ll t = power(x, y / 2);
    return (t * t) % MOD;
  }
}
void ready() {
  fact[0] = rfact[0] = 1;
  ll ret;
  for (int i = 1; i <= N_MAX; ++i) {
    ret = (1LL * i * fact[i - 1]) % MOD;
    fact[i] = ret;
    ret = power(fact[i], MOD - 2);
    rfact[i] = ret;
  }
}
int main() {
  ready();
  program();
  return 0;
}