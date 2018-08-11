// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (2 * 1e7)
#define MOD (int) (1e9 + 7)
#define BASE 10
#define BUCKETS_MAX 10
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n;
struct {
  int val;
  int cur_val;
} input[BUFF(N_MAX)];
struct L {
  int idx;
  struct L *next;
} l_nodes_pool[2][BUFF(N_MAX)];
int l_pool_ptr[2];
struct B {
  struct L *front, *rear;
} buckets[2][BUFF(BUCKETS_MAX)];
bool cur;
void resetRadix() {
  cur = !cur;
  l_pool_ptr[cur] = 0;
  for (int i = 0; i <= BUCKETS_MAX; ++i)
    buckets[cur][i].front = buckets[cur][i].rear = NULL;
}
struct L *getLNodesFromPool() { return &l_nodes_pool[cur][l_pool_ptr[cur]++]; }
void pushToBucket(int idx, int bucket_no) {
  struct L *t = getLNodesFromPool();
  t->idx = idx;
  t->next = NULL;
  struct B *b = &buckets[cur][bucket_no];
  if (b->rear == NULL) b->front = b->rear = t;
  else {
    b->rear->next = t;
    b->rear = t;
  }
}
ll ans;
int seen;
void m_mod(ll &x) { while (x >= MOD) x -= MOD; }
void addToAnswer(int idx) {
  ++seen;
  ans = (ans + 1LL * seen * input[idx].val % MOD);
  m_mod(ans);
}
void radix_sort() {
  bool prev;
  resetRadix();
  for (int i = 1; i <= n; ++i) {
    if (!input[i].cur_val) addToAnswer(i);
    else {
      pushToBucket(i, input[i].cur_val % BASE);
      input[i].cur_val /= BASE;
    }
  }
  struct L *t;
  for (int i = 1; i <= BASE; ++i) {
    prev = cur;
    resetRadix();
    for (int b_id = 0; b_id < BUCKETS_MAX; ++b_id) {
      t = buckets[prev][b_id].front;
      while (t) {
        if (!input[t->idx].cur_val) addToAnswer(t->idx);
        else {
          pushToBucket(t->idx, input[t->idx].cur_val % BASE);
          input[t->idx].cur_val /= BASE;
        }
        t = t->next;
      }
    }
  }
}
void addToInput(int val, int idx) {
  input[idx].val = input[idx].cur_val = val;
}
void reset() { ans = seen = 0; }
void program() {
  int tcase, a, b;
  ll ret;
  struct L *q;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d %d %d %lld", &n, &a, &b, &ret);
    addToInput(ret, 1);
    for (int i = 2; i <= n; ++i) {
      ret = (ret * a + b) % MOD;
      addToInput(ret, i);
    }
    radix_sort();
    printf("%lld\n", ans);
  }
}
int main() {
  freopen("ADATOMAT_input.txt", "r", stdin);
  program();
  return 0;
}
/*
1
20000000 5 6 7
*/