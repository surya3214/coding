// AC Aho-Corasick String matching algorithm, Automaton
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#define NEEDLE_MAX 2000
#define N_MAX 1000
#define STATES_MAX NEEDLE_MAX * N_MAX
#define ALPHA_MAX 70
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char haystack[BUFF(LEN_MAX)];
char needle[BUFF(NEEDLE_MAX)];
bool found[BUFF(N_MAX)];
int root, total_states;
struct T {
  bool seen;
  map<char, int> go_to;
  int fail;
  vector<int> matches;
} tries[BUFF(STATES_MAX)];
void insertInTrie(int idx) {
  int current_state = root;
  char x;
  for (int i = 0; needle[i] != '\0'; ++i) {
    x = needle[i];
    if (!tries[current_state].go_to[x])
      tries[current_state].go_to[x] = ++total_states;
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
  tries[root].fail = 0;
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
void search() {
  int current_state = root;
  for (int i = 0; haystack[i] != '\0'; ++i) {
    current_state = findNextState(current_state, haystack[i]);
    for (int t = current_state; t && !tries[t].seen; t = tries[t].fail) {
      tries[t].seen = true;
      for (int i = 0; i < tries[t].matches.size(); ++i)
        found[tries[t].matches[i]] = true;
    }
  }
}
void program() {
  root = ++total_states;
  int n;
  scanf("%s", haystack);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", needle);
    insertInTrie(i);
  }
  bfs();
  search();
  for (int i = 1; i <= n; ++i) {
    if (found[i])
      printf("Y\n");
    else printf("N\n");
  }
}
int main() {
  program();
  return 0;
}