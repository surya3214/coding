// AC Trie
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 1000000
#define STATES_MAX LEN_MAX
#define ALPHA_CHARS_MAX 26
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct {
  int go_to[BUFF(ALPHA_CHARS_MAX)];
  int cnt;
} tries[BUFF(STATES_MAX)];
int total_states, root;
int getIndexFromChar(char x) { return x - 'a' + 1; }
void InsertIntoTrie() {
  int cur_state = root;
  int x;
  for (int i = 0; str[i]; ++i) {
    x = getIndexFromChar(str[i]);
    if (!tries[cur_state].go_to[x])
      tries[cur_state].go_to[x] = ++total_states;
    cur_state = tries[cur_state].go_to[x];
    ++tries[cur_state].cnt;
  }
}
int CountTries() {
  int cur_state = root, x;
  for (int i = 0; str[i]; ++i) {
    x = getIndexFromChar(str[i]);
    if (!tries[cur_state].go_to[x]) {
      cur_state = 0;
      break;
    }
    cur_state = tries[cur_state].go_to[x];
  }
  return tries[cur_state].cnt;
}
void program() {
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", str);
    InsertIntoTrie();
  }
  for (int i = 1; i <= q; ++i) {
    scanf("%s", str);
    printf("%d\n", CountTries());
  }
}
int main() {
  root = ++total_states;
  program();
  return 0;
}