// AC Aha-Corasick String matching algorithm, Ayyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) (2 * 1e6)
#define STATES_MAX LEN_MAX
#define N_MAX (int) 1e5
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, root, total_nodes;
char gene[BUFF(LEN_MAX)];
int health[BUFF(N_MAX)];
int l, r;
struct {
  bool set;
  ll min, max;
} ans;
struct T {
  int processed_at;
  ll val;
  map<char, int> go_to;
  int fail;
  vector<int> matches;
} tries[BUFF(STATES_MAX)];
int t_time;
void updateAns(ll x) {
  if (!ans.set) {
    ans.max = ans.min = x;
    ans.set = true;
  } else {
    ans.min = min(ans.min, x);
    ans.max = max(ans.max, x);
  }
}
void insertInTrie(int idx) {
  int current_state = root;
  char x;
  for (int i = 0; gene[i]; ++i) {
    x = gene[i];
    if (!tries[current_state].go_to[x])
      tries[current_state].go_to[x] = ++total_nodes;
    current_state = tries[current_state].go_to[x];
  }
  tries[current_state].matches.push_back(idx);
}
int findNextState(int state, char x) {
  while (state && !tries[state].go_to[x])
    state = tries[state].fail;
  return state ? tries[state].go_to[x] : root;
}
void bfs() {
  queue<int> q;
  tries[root].fail = 0; // invalid state
  int u, v, f;
  char x;
  for (q.push(root); !q.empty(); q.pop()) {
    u = q.front();
    for (map<char, int>::iterator it = tries[u].go_to.begin(); it != tries[u].go_to.end(); ++it) {
      x = it->first;
      v = it->second;
      f = findNextState(tries[u].fail, x);
      tries[v].fail = f;
      q.push(v);
    }
  }
}
void calculateForNode(int n_id) {
  if (n_id && tries[n_id].processed_at != t_time) {
    int f = tries[n_id].fail;
    calculateForNode(f);
    tries[n_id].val = tries[f].val;
    for (int i = 0; i < tries[n_id].matches.size(); ++i)
      if (l <= tries[n_id].matches[i] && tries[n_id].matches[i] <= r)
        tries[n_id].val += health[tries[n_id].matches[i]];
    tries[n_id].processed_at = t_time;
  }
}
ll search() {
  ll total = 0;
  ++t_time;
  int current_state = root;
  for (int i = 0; gene[i]; ++i) {
    current_state = findNextState(current_state, gene[i]);
    calculateForNode(current_state);
    total += tries[current_state].val;
  }
  return total;
}
void program() {
  int q;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", gene);
    insertInTrie(i);
  }
  bfs();
  for (int i = 1; i <= n; ++i)
    scanf("%d", &health[i]);
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %s", &l, &r, gene);
    ++l; ++r;
    updateAns(search());
  }
  printf("%lld %lld\n", ans.min, ans.max);
}
int main() {
  root = ++total_nodes;
  program();
  return 0;
}