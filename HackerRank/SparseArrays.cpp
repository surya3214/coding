// AC Trie
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
#define LEN_MAX 20
#define CHARS_MAX 26
#define NODES_MAX (N_MAX * LEN_MAX)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct {
  int go_to[BUFF(CHARS_MAX)];
  int cnt;
} trie[BUFF(NODES_MAX)];
int root, total_nodes;
int getIndexFromChar(char x) { return x - 'a' + 1; }
int navigate(bool is_insert) {
  int cur = root, x;
  for (int i = 0; str[i]; ++i) {
    x = getIndexFromChar(str[i]);
    if (!trie[cur].go_to[x]) {
      if (is_insert)
        trie[cur].go_to[x] = ++total_nodes;
      else return 0;
    }
    cur = trie[cur].go_to[x];
  }
  return cur;
}
void insert() {
  int node_id = navigate(true);
  ++trie[node_id].cnt;
}
int locate() {
  int node_id = navigate(false);
  return trie[node_id].cnt;
}
void program() {
  root = ++total_nodes;
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", str);
    insert();
  }
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", str);
    printf("%d\n", locate());
  }
}
int main() {
  program();
  return 0;
}