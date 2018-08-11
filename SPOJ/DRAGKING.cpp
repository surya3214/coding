// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
#define LEN_MAX 26
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
char input[BUFF(N_MAX)];
ll cubes[BUFF(N_MAX)];
ll ans;
int len;
struct {
  int time;
  int count;
} counts[BUFF(N_MAX)];
struct {
  int time;
  bool ans;
} dp[BUFF(N_MAX)][BUFF(N_MAX)];
struct L { int pos; L *next; } l_nodes_pool[BUFF(N_MAX)];
int l_ptr;
struct M {
  struct L *front, *rear;
  int time;
} m_list[BUFF(LEN_MAX)];
int t_time;
void reset() { ++t_time; len = l_ptr = ans = 0; }
struct L *getLNodeFromPool() { return &l_nodes_pool[l_ptr++]; }
void sanitizeList(int idx) {
  if (m_list[idx].time != t_time) {
    m_list[idx].front = m_list[idx].rear = NULL;
    m_list[idx].time = t_time;
  }
}
void computeCubes() {
  for (int i = 1; i <= N_MAX; ++i)
    cubes[i] = 1LL * i * i * i;
}
void sanitizeCounts(int i) {
  if (counts[i].time != t_time) {
    counts[i].count = 0;
    counts[i].time = t_time;
  }
}
int getIndexFromCharacter(char x) { return x - 'a'; }
void addToList(int idx, int pos) {
  sanitizeList(idx);
  struct L *t = getLNodeFromPool();
  t->pos = pos;
  t->next = NULL;
  struct M *p = &m_list[idx];
  if (!p->front) p->front = p->rear = t;
  else {
    p->rear->next = t;
    p->rear = t;
  }
}
void addToCount(int n) { sanitizeCounts(n); ++counts[n].count; }
bool isPalindrome(int l, int r) {
  if (l >= r) return true;
  if (dp[l][r].time == t_time)
    return dp[l][r].ans;
  dp[l][r].time = t_time;
  if (input[l] != input[r]) return false;
  bool ans;
  ans = isPalindrome(l + 1, r - 1);
  return dp[l][r].ans = ans;
}
void compute() {
  struct M *p;
  struct L *t;
  for (int i = 0; input[i] != '\0'; ++i) {
    p = &m_list[getIndexFromCharacter(input[i])];
    t = p->front->next;
    while (t) {
      if (isPalindrome(p->front->pos, t->pos))
        addToCount(t->pos - p->front->pos + 1);
      t = t->next;
    }
    p->front = p->front->next;
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  computeCubes();
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%s", input);
    for (len = 0; input[len] != '\0'; ++len)
      addToList(getIndexFromCharacter(input[len]), len);
    compute();
    ans = len;
    for (int i = 2; i <= N_MAX; ++i) {
      sanitizeCounts(i);
      ans += counts[i].count * cubes[i];
    }
    printf("%lld\n", ans);
  }
}
int main() {
  program();
  return 0;
}