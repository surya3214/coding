// AC Treap Ayyyyyyyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX 10000
#define LEN_MAX 10000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct N {
  int priority;
  char x;
  int sub_height;
  N *l, *r;
} *root, nodes_pool[BUFF(LEN_MAX)];
int nodes_ptr;
typedef struct N* pnode;
struct Q {
  int time, idx;
  int type, x, y;
} queries[BUFF(Q_MAX)];
int t_time;
struct A {
  int idx;
  char x;
} answers[BUFF(Q_MAX)];
int a_ptr;
pnode getNNodesFromPool(char x) {
  pnode t = &nodes_pool[nodes_ptr++];
  t->priority = rand();
  t->x = x;
  t->sub_height = 1;
  t->l = t->r = NULL;
  return t;
}
int getSubHeight(pnode t) { return t ? t->sub_height : 0; }
void updateNode(pnode t) {
  if (t)
    t->sub_height = getSubHeight(t->l) + 1 + getSubHeight(t->r);
}
void Merge(pnode &t, pnode l, pnode r) {
  if (!l) t = r;
  else if (!r) t = l;
  else if (l->priority > r->priority)
    Merge(l->r, l->r, r), t = l;
  else Merge(r->l, l, r->l), t = r;
  updateNode(t);
}
void insertIntoTreap(char x) {
  pnode p = getNNodesFromPool(x);
  Merge(root, root, p);
}
void buildTreap() {
  for (int i = 0; str[i]; ++i)
    insertIntoTreap(str[i]);
}
bool q_comparator(Q a, Q b) {
  if (a.time != b.time)
    return a.time < b.time;
  return a.type < b.type;
}
bool a_comparator(A a, A b) {
  return a.idx < b.idx;
}
void Split(pnode t, pnode &l, pnode &r, int pos, int add) {
  if (!t)
    l = r = NULL;
  else {
    int cur_pos = add + getSubHeight(t->l) + 1; // implicit key
    if (cur_pos <= pos)
      Split(t->r, t->r, r, pos, cur_pos), l = t;
    else Split(t->l, l, t->l, pos, add), r = t;
    updateNode(t);
  }
}
void SplitAndMerge(pnode &t, int l, int r, bool type) {
  pnode l1, r1;
  Split(t, l1, r1, l - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, r - l + 1, 0);
  Merge(l1, l1, r2);
  if (type) // front
    Merge(t, l2, l1);
  else Merge(t, l1, l2);
}
char query(pnode &t, int pos) {
  pnode l1, r1;
  Split(t, l1, r1, pos - 1, 0);
  pnode l2, r2;
  Split(r1, l2, r2, 1, 0);
  char ret = l2->x;
  Merge(r1, l2, r2);
  Merge(t, l1, r1);
  return ret;
}
void addToAnswers(char x, int idx) {
  ++a_ptr;
  answers[a_ptr].x = x;
  answers[a_ptr].idx = idx;
}
void program() {
  int q;
  scanf("%s", str);
  buildTreap();
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    ++t_time;
    scanf("%d", &queries[i].type);
    if (queries[i].type == 4)
      scanf("%d", &queries[i].time);
    else queries[i].time = t_time;
    queries[i].idx = i;
    if (queries[i].type == 3 || queries[i].type == 4)
      scanf("%d", &queries[i].x);
    else scanf("%d %d", &queries[i].x, &queries[i].y);
    ++queries[i].x;
    ++queries[i].y;
  }
  sort(queries + 1, queries + 1 + q, q_comparator);
  for (int i = 1; i <= q; ++i) {
    if (queries[i].type == 3 || queries[i].type == 4)
      addToAnswers(query(root, queries[i].x), queries[i].idx);
    else SplitAndMerge(root, queries[i].x, queries[i].y, queries[i].type == 1);
  }
  sort(answers + 1, answers + 1 + a_ptr, a_comparator);
  for (int i = 1; i <= a_ptr; ++i)
    printf("%c\n", answers[i].x);
}
int main() {
  program();
  return 0;
}