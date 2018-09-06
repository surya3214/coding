// AC Aho-Corasick String matching Algorithm, Automaton
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3000
#define LEN_MAX 500000
#define Q_MAX LEN_MAX
#define STATES_MAX LEN_MAX
#define ALPHA_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char haystack[BUFF(N_MAX)];
char needle[BUFF(LEN_MAX)];
int root, total_states;
int cnt[BUFF(Q_MAX)];
struct {
  bool inited;
  int go_to[BUFF(ALPHA_MAX)];
  int fail;
  vector<int> word_ids;
  bool processed;
  vector<int> matches;
} tries[BUFF(STATES_MAX)];
void initializeNode(int idx) {
  if (!tries[idx].inited) {
    memset(tries[idx].go_to, -1, sizeof(tries[idx].go_to));
    tries[idx].inited = true;
  }
}
int getIndexFromChar(char x) { return x - 'a'; }
void insertIntoTrie(int word_id) {
  int current_state = root;
  int x;
  for (int i = 0; needle[i] != '\0'; ++i) {
    x = getIndexFromChar(needle[i]);
    if (tries[current_state].go_to[x] == -1) {
      tries[current_state].go_to[x] = ++total_states;
      initializeNode(total_states);
    }
    current_state = tries[current_state].go_to[x];
  }
  tries[current_state].word_ids.push_back(word_id);
}
int findNextState(int state, int x) {
  while (state && tries[state].go_to[x] == -1)
    state = tries[state].fail;
  return state ? tries[state].go_to[x] : root;
}
void bfs() {
  queue<int> q;
  tries[root].fail = 0;
  int u, v, fail_state;
  for (q.push(root); !q.empty(); q.pop()) {
    u = q.front();
    for (int c = 0; c < ALPHA_MAX; ++c) {
      v = tries[u].go_to[c];
      if (v != -1) {
        fail_state = findNextState(tries[u].fail, c);
        tries[v].fail = fail_state;
        q.push(v);
      }
    }
  }
}
void processNode(int idx) {
  if (!tries[idx].processed && idx) {
    processNode(tries[idx].fail);
    tries[idx].matches = tries[tries[idx].fail].matches;
    for (int i = 0; i < tries[idx].word_ids.size(); ++i)
      tries[idx].matches.push_back(tries[idx].word_ids[i]);
    tries[idx].processed = true;
  }
}
void search() {
  int current_state = root;
  for (int i = 0; haystack[i] != '\0'; ++i) {
    current_state = findNextState(current_state, getIndexFromChar(haystack[i]));
    processNode(current_state);
    for (int j = 0; j < tries[current_state].matches.size(); ++j)
      ++cnt[tries[current_state].matches[j]];
  }
}
void program() {
  int n, q;
  scanf("%d %d", &n, &q);
  scanf("%s", haystack);
  for (int i = 1; i <= q; ++i) {
    scanf("%s", needle);
    insertIntoTrie(i);
  }
  bfs();
  search();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", cnt[i]);
}
void ready() {
  root = ++total_states;
  initializeNode(total_states);
}
int main() {
  freopen("input.txt", "r", stdin);
  ready();
  program();
  return 0;
}