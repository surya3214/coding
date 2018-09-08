// TLE
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 2000
#define STATES_MAX (int) 1e7
#define ALPHA_CHARS_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
char str[BUFF(LEN_MAX)];
struct {
  int cnt[BUFF(ALPHA_CHARS_MAX)];
  int go_to[BUFF(ALPHA_CHARS_MAX)];
  bool computed;
} tries[BUFF(STATES_MAX)];
int root, total_nodes;
char ans[BUFF(LEN_MAX)];
int getIndexFromChar(char x) { return x - 'a' + 1; }
void insertIntoTrie() {
  int current_state, x, t;
  bool is_unique;
  for (int i = 0; str[i]; ++i) {
    current_state = root;
    for (int j = i; str[j]; ++j) {
      x = getIndexFromChar(str[j]);
      if (!tries[current_state].go_to[x]) {
        tries[current_state].go_to[x] = ++total_nodes;
        tries[total_nodes].cnt[0] = 1;
        // t = root;
        // for (int j = i; str[j]; ++j) {
        //   if (t == total_nodes) break;
        //   x = getIndexFromChar(str[j]);
        //   ++tries[t].cnt[x];
        //   t = tries[t].go_to[x];
        // }
      }
      current_state = tries[current_state].go_to[x];
    }
  }
}
void compute(int n_id) {
  if (!tries[n_id].computed) {
    for (int i = 1; i <= ALPHA_CHARS_MAX; ++i)
      tries[n_id].cnt[i] += tries[n_id].cnt[i - 1];
    tries[n_id].computed = true;
  }
}
bool isPossible(int k) {
  compute(root);
  if (k > tries[root].cnt[ALPHA_CHARS_MAX]) return false;
  int idx = 0;
  int current_state = root;
  while (1) {
    compute(current_state);
    for (int i = 0; i <= ALPHA_CHARS_MAX; ++i) {
      if (tries[current_state].cnt[i] >= k) {
        if (!i) {
          ans[idx] = '\0';
          return true;
        }
        ans[idx++] = 'a' + i - 1;
        k -= tries[current_state].cnt[i - 1];
        current_state = tries[current_state].go_to[i];
        break;
      }
    }
  }
}
void program() {
  int q, k;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", str);
    insertIntoTrie();
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &k);
    if (isPossible(k))
      printf("%s\n", ans);
    else printf("INVALID\n");
  }
}
int main() {
  root = ++total_nodes;
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}