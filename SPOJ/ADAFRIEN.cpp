// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 40
#define N_MAX 100000
#define CHILDREN_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, k;
struct {
  char name[BUFF(LEN_MAX)];
  ll expense;
} buffer;
ll expenses[BUFF(N_MAX)];
struct T {
  int idx;
  struct T *children[BUFF(CHILDREN_MAX)];
} *root, t_nodes_pool[BUFF(N_MAX * LEN_MAX)];
int t_pool_ptr;
int getIndexFromCharacter(char x) { return x - 'a' ;}
struct T *getTNodesFromPool() { return &t_nodes_pool[t_pool_ptr++]; }
struct T *addToTrie(struct T *t, int idx) {
  if (t == NULL) { t = getTNodesFromPool(); t->idx = 0; };
  if (buffer.name[idx] == '\0') {
    if (!t->idx) t->idx = ++expenses[0];
    expenses[t->idx] += buffer.expense;
  } else {
    int x = getIndexFromCharacter(buffer.name[idx]);
    t->children[x] = addToTrie(t->children[x], idx + 1);
  }
  return t;
}
void program() {
  ll ans = 0;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%s %lld", buffer.name, &buffer.expense);
    root = addToTrie(root, 0);
  }
  sort(expenses + 1, expenses + 1 + expenses[0]);
  for (int i = expenses[0]; i >= 1 && k; --i, --k)
    ans += expenses[i];
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}