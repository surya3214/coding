// AC Aho-Corasick String matching Algorithm, Automaton
#include <bits/stdc++.h>
#include <queue>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) (2 * 1e6)
#define ALPHA_CHARS_MAX 26
#define STATES_MAX (int) (2 * 1e6)
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char inp[BUFF(LEN_MAX)];
int go_to[BUFF(STATES_MAX)][BUFF(ALPHA_CHARS_MAX)];
int fail[BUFF(STATES_MAX)];
int out[BUFF(STATES_MAX)];
struct {
  char q[BUFF(LEN_MAX)];
  int q_idx[BUFF(LEN_MAX)];
  int q_ptr;
} queries;
int total_states;
int getIndexFromChar(char x) { return x - 'a'; }
void addToTrie(int idx) {
  int cur_state = 0, x;
  for (int i = 0; inp[i] != '\0'; ++i) {
    x = getIndexFromChar(inp[i]);
    if (go_to[cur_state][x] == -1) {
      go_to[cur_state][x] = ++total_states;
      out[go_to[cur_state][x]] = BUFF(STATES_MAX);
    }
    cur_state = go_to[cur_state][x];
  }
  out[cur_state] = min(out[cur_state], idx);
}
void process() {
  int cur_state = 0, failure;
  queue<int> q;
  for (int c = 0; c < ALPHA_CHARS_MAX; ++c) {
    if (go_to[cur_state][c] == -1)
      go_to[cur_state][c] = 0;
    else {
      fail[go_to[cur_state][c]] = cur_state;
      q.push(go_to[cur_state][c]);
    }
  }
  while (!q.empty()) {
    cur_state = q.front();
    for (int c = 0; c < ALPHA_CHARS_MAX; ++c) {
      if (go_to[cur_state][c] != -1) {
        failure = fail[cur_state];
        while (go_to[failure][c] == -1)
          failure = fail[failure];
        failure = go_to[failure][c];
        fail[go_to[cur_state][c]] = failure;
        out[go_to[cur_state][c]] = min(out[go_to[cur_state][c]], out[failure]);
        q.push(go_to[cur_state][c]);
      }
    }
    q.pop();
  }
}
int nextState(int cur_state, int x) {
  while (go_to[cur_state][x] == -1)
    cur_state = fail[cur_state];
  return go_to[cur_state][x];
}
bool isPresent(int x) {
  int cur_state = 0;
  for (int i = 0; inp[i] != '\0'; ++i) {
    cur_state = nextState(cur_state, getIndexFromChar(inp[i]));
    if (out[cur_state] < x)
      return true;
  }
  return false;
}
void program() {
  int n, type, pos, j;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %s", &type, inp);
    if (type) {
      for (int j = 0; inp[j] != '\0'; ++j)
        queries.q[queries.q_ptr++] = inp[j];
      queries.q[queries.q_ptr++] = '\0';
      pos = ++queries.q_idx[0];
      queries.q_idx[pos] = i;
    } else addToTrie(i);
  }
  process();
  queries.q_ptr = 0;
  for (int i = 1; i <= queries.q_idx[0]; ++i) {
    j = 0;
    while (queries.q[queries.q_ptr] != '\0') {
      inp[j] = queries.q[queries.q_ptr];
      ++j;
      ++queries.q_ptr;
    }
    inp[j] = '\0';
    ++queries.q_ptr;
    if (isPresent(queries.q_idx[i]))
      printf("YES\n");
    else printf("NO\n");
  }
}
void ready() {
  memset(go_to, -1, sizeof(go_to));
  memset(fail, -1, sizeof(fail));
  out[0] = BUFF(STATES_MAX);
}
int main() {
  ready();
  program();
  return 0;
}