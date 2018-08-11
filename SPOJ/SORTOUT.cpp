// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 200000
#define CHILDREN_MAX 27
#define ALPHA_MAX 26
#define NULL_INDEX 0
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
struct {
  char str[BUFF(N_MAX)];
} buffer;
struct T {
  bool updated;
  ll accessed[BUFF(CHILDREN_MAX)];
  struct T *children[BUFF(CHILDREN_MAX)];
} *root, t_nodes_pool[BUFF(N_MAX)];
int t_pool_ptr;
int getIndexFromCharacter(char x) {
  if (x == '\0') return NULL_INDEX;
  return x - 'a' + 1;
}
struct T *getTNodesFromPool() { return &t_nodes_pool[t_pool_ptr++]; }
struct T *insertIntoTrie(struct T *t, int idx) {
  if (t == NULL) t = getTNodesFromPool();
  int x = getIndexFromCharacter(buffer.str[idx]);
  ++t->accessed[x];
  if (buffer.str[idx] != '\0')
    t->children[x] = insertIntoTrie(t->children[x], idx + 1);
  return t;
}
ll ans;
void updateNode(struct T *t) {
  if (t->updated) return;
  for (int i = 1; i <= ALPHA_MAX; ++i)
    t->accessed[i] += t->accessed[i - 1];
  t->updated = true;
}
void findInTrie() {
  struct T *t = root;
  ans = 0;
  int idx = 0;
  int x;
  while (t) {
    if (buffer.str[idx] == '\0') {
      ans += t->accessed[NULL_INDEX];
      break;
    }
    x = getIndexFromCharacter(buffer.str[idx]);
    updateNode(t);
    ans += t->accessed[x - 1];
    t = t->children[x];
    ++idx;
  }
}
void program() {
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", buffer.str);
    root = insertIntoTrie(root, 0);
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%s", buffer.str);
    findInTrie();
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}