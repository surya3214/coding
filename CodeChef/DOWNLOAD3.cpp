// AC Motha' fuckin yeah!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#pragma GCC optimize "O3"
#define P_MAX (int) 1e5
#define Q_MAX 5000
#define K_MAX 20
#define S_MAX (int) (3 * 1e5)
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct P {
  int s, e;
} points[BUFF(P_MAX)];
enum T {
  // type: 0 - query, 1 - start, 2 - end
  QUERY,
  START,
  END
};
struct S {
  S() {}
  S(int t_val, int t_id, T t_type) : val(t_val), id(t_id), type(t_type) {}
  int val, id;
  T type;
} sorted[BUFF(S_MAX)];
int s_ptr;
struct Q {
  int processed_until, ans;
  vector<int> l_points;
} queries[BUFF(Q_MAX)];
int q;
struct E {
  vector<int> queries;
  vector<int> starts;
  vector<int> ends;
} events[BUFF(S_MAX)];
int e_ptr, opened;
int BIT[BUFF(S_MAX)];
void addToSorted(int val, int id, T type) { sorted[++s_ptr] = { val, id, type }; }
bool s_comparator(S a, S b) { return a.val < b.val; }
void addToEvents(int id, T type) {
  switch (type) {
    case QUERY:
      events[e_ptr].queries.push_back(id);
      break;
    case START:
      events[e_ptr].starts.push_back(id);
      break;
    case END:
      events[e_ptr].ends.push_back(id);
      break;
  }
}
void localizeValues() {
  sort(sorted + 1, sorted + 1 + s_ptr, s_comparator);
  for (int l = 1, r, x; l < s_ptr; l = r + 1) {
    for (r = l; r + 1 < s_ptr && sorted[r + 1].val == sorted[l].val; ++r);
    ++e_ptr;
    for (; l <= r; ++l) {
      x = sorted[l].id;
      addToEvents(x, sorted[l].type);
      if (sorted[l].type == QUERY)
        queries[x].l_points.push_back(e_ptr);
      else if (sorted[l].type == START)
        points[x].s = e_ptr;
      else points[x].e = e_ptr;
    }
  }
}
void addToBIT(int idx, int val) {
  while (idx < S_MAX) {
    BIT[idx] += val;
    idx += (idx & -idx);
  }
}
int queryBIT(int idx) {
  int ret = 0;
  while (idx) {
    ret += BIT[idx];
    idx -= (idx & -idx);
  }
  return ret;
}
void handleEvents() {
  for (int i = 1; i <= e_ptr; ++i) {
    for (auto j: events[i].starts) {
      ++opened;
      addToBIT(points[j].s, 1);
    }
    for (auto j: events[i].queries) {
      queries[j].ans += opened - queryBIT(queries[j].l_points[queries[j].processed_until]);
      ++queries[j].processed_until;
    }
    for (auto j: events[i].ends) {
      --opened;
      addToBIT(points[j].s, -1);
    }
  }
}
void program() {
  int s, e, p;
  scanf("%d", &p);
  for (int i = 1; i <= p; ++i) {
    scanf("%d %d", &s, &e);
    addToSorted(s, i, START);
    addToSorted(e, i, END);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &p);
    queries[i].l_points.push_back(0);
    for (int j = 1; j <= p; ++j) {
      scanf("%d", &s);
      addToSorted(s, i, QUERY);
    }
  }
  localizeValues();
  handleEvents();
  for (int i = 1; i <= q; ++i)
    printf("%d\n", queries[i].ans);
}
int main() {
  program();
  return 0;
}