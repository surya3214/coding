// WA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define M_MAX 100000
#define LEN_MAX 1000000
#define Q_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m;
struct {
  vector<char> str;
} words[BUFF(N_MAX)];
struct {
  vector<int> made_of;
} meta_words[BUFF(M_MAX)];
char str[BUFF(LEN_MAX)];
struct Q {
  int idx;
  int word_id;
  ll position;
} queries[BUFF(Q_MAX)];
int q_ptr;
int q;
char ans[BUFF(Q_MAX)];
bool q_comparator(Q a, Q b) {
  if (a.word_id != b.word_id)
    return a.word_id < b.word_id;
  return a.position < b.position;
}
struct {
  ll seen_so_far;
  int word_id;
  int m_word_id;
} cursor;
void moveCursor(ll pos) {
  int actual_word_id = meta_words[cursor.word_id].made_of[cursor.m_word_id];
  ll next = words[actual_word_id].str.size();
  while (cursor.m_word_id < meta_words[cursor.word_id].made_of.size() && cursor.seen_so_far + next <= pos) {
    cursor.seen_so_far += next;
    actual_word_id = meta_words[cursor.word_id].made_of[++cursor.m_word_id];
    next = words[actual_word_id].str.size();
  }
}
void process(int q_l, int q_r) {
  cursor.seen_so_far = 0;
  cursor.word_id = queries[q_l].word_id;
  cursor.m_word_id = 0;
  int actual_word_id;
  char x;
  for (int i = q_l; i <= q_r; ++i) {
    moveCursor(queries[i].position);
    actual_word_id = meta_words[cursor.word_id].made_of[cursor.m_word_id];
    x = words[actual_word_id].str[queries[i].position - cursor.seen_so_far];
    ans[queries[i].idx] = x;
  }
}
void compute() {
  int l = 1, r;
  while (l <= q_ptr) {
    r = l;
    while (r + 1 <= q_ptr && queries[r + 1].word_id == queries[r].word_id)
      ++r;
    process(l, r);
    l = r + 1;
  }
}
void addToQueries(int m_word_id, ll position, int idx) {
  ++q_ptr;
  queries[q_ptr].word_id = m_word_id;
  queries[q_ptr].position = position;
  queries[q_ptr].idx = --idx;
}
void program() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", str);
    for (int j = 0; str[j]; ++j)
      words[i].str.push_back(str[j]);
  }
  int len, x;
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &len);
    for (int j = 1; j <= len; ++j) {
      scanf("%d", &x);
      meta_words[i].made_of.push_back(x);
    }
  }
  int word_id;
  ll position;
  scanf("%d", &q);
  char y;
  for (int i = 1; i <= q; ++i) {
    scanf("%d %lld", &word_id, &position);
    if (word_id <= n) {
      y = words[word_id].str[position - 1];
      ans[i - 1] = y;
    }
    else addToQueries(word_id - n, position, i);
  }
  sort(queries + 1, queries + 1 + q_ptr, q_comparator);
  compute();
  ans[q] = '\0';
  printf("%s\n", ans);
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}