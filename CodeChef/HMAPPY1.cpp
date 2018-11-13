// AC Linked List Ayyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define Q_MAX (int) (3 * 1e5)
#define NODES_MAX (int) (N_MAX + Q_MAX)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, cur_max;
int values[BUFF(N_MAX)];
int right_most;
char query[BUFF(Q_MAX)];
int freq[BUFF(N_MAX)];
struct N {
  int total;
  struct N *prev;
  struct N *next;
} *front, *rear, nodes[BUFF(NODES_MAX)];
int n_ptr;
struct N *get_t_nodes_from_pool() { return &nodes[n_ptr++]; }
void add_to_list(int x) {
  if (!x) return;
  struct N *t = get_t_nodes_from_pool();
  t->total = x;
  t->prev = t->next = NULL;
  if (!front) front = rear = t;
  else {
    rear->next = t;
    t->prev = rear;
    rear = t;
  }
  ++freq[x];
  cur_max = max(cur_max, x);
}
void preprocess() {
  int cur_total = 0;
  for (int i = 1; i <= n; ++i) {
    if (values[i] == 1)
      ++cur_total;
    else {
      add_to_list(cur_total);
      cur_total = 0;
    }
  }
  add_to_list(cur_total);
}
void remove_rear_if_required() {
  if (!rear->total) {
    rear = rear->prev;
    rear->next = NULL;
  }
}
void pop_from_rear() {
  if (front->total)
    --freq[front->total];
  --freq[rear->total];
  --rear->total;
  ++front->total;
  if(rear->total)
    ++freq[rear->total];
  ++freq[front->total];
  remove_rear_if_required();
}
void add_null_to_front_if_required() {
  if (front->total) {
    struct N *t = get_t_nodes_from_pool();
    t->next = front;
    t->prev = NULL;
    t->total = 0;
    front->prev = t;
    front = t;
  }
}
void decrease_right_most() { right_most = (right_most == 1) ? n : --right_most; }
void adjust_cur_max() {
  if (freq[cur_max + 1])
    cur_max = cur_max + 1;
  else if (!freq[cur_max])
    cur_max = cur_max - 1;
}
void right_shift() {
  if (values[right_most]) {
    pop_from_rear();
    adjust_cur_max();
  }
  else add_null_to_front_if_required();
  decrease_right_most();
}
void program() {
  int q, k;
  scanf("%d %d  %d", &n, &q, &k);
  bool no_zeros = true, all_zeros = true;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &values[i]);
    if (!values[i])
      no_zeros = false;
    else all_zeros = false;
  }
  if (!all_zeros && !no_zeros) {
    right_most = n;
    preprocess();
  }
  scanf("%s", query);
  for (int i = 0; query[i]; ++i) {
    if (query[i] == '?') {
      if (no_zeros)
        printf("%d\n", min(n, k));
      else if (all_zeros)
        printf("0\n");
      else printf("%d\n", min(cur_max, k));
    } else {
      if (!no_zeros && !all_zeros)
        right_shift();
    }
  }
}
int main() {
  program();
  return 0;
}