// AC - Trie String Matching
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3000
#define Q_MAX 500000
#define CHILD_MAX 27
#define NODES_MAX 4501500
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, q, ans;
char str[BUFF(N_MAX)];
char buffer[BUFF(Q_MAX)];
struct T {
  int count;
  struct T *children[BUFF(CHILD_MAX)];
} *root, t_nodes_pool[BUFF(NODES_MAX)];
int t_pool_ptr;
struct T *getTNodesFromPool() { return &t_nodes_pool[t_pool_ptr++]; }
int getIndexFromChar(char x) { if (x == '\0') return 0; return x - 'a' + 1; }
struct T *insertIntoTrie(struct T *t, int x) {
  int idx = getIndexFromChar(str[x]);
  if (t == NULL) t = getTNodesFromPool();
  ++t->count;
  if (idx) t->children[idx] = insertIntoTrie(t->children[idx], x + 1);
  return t;
}
void process() {
  for (int i = 0; str[i] != '\0'; ++i)
    root = insertIntoTrie(root, i);
}
int searchInTrie(struct T *t, int x) {
  int idx = getIndexFromChar(buffer[x]);
  if (!t) return 0;
  if (!idx) return t->count;
  return searchInTrie(t->children[idx], x + 1);
}
void program() {
  scanf("%d %d", &n, &q);
  scanf("%s", str);
  process();
  for (int i = 1; i <= q; ++i) {
    scanf("%s", buffer);
    ans = searchInTrie(root, 0);
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}