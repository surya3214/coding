// AC Persistent Segment Trees
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
int input[BUFF(N_MAX)];
map<int, int> M;
int RM[BUFF(N_MAX)];
struct T {
  int cnt;
  T *left, *right;
  T() : cnt(0), left(nullptr), right(nullptr) {}
} *root[BUFF(N_MAX)];
int getMid(int l, int r) { return l + (r - l) / 2; }
T* createPersistentSegmentTree(T *old, int l, int r, int pos) {
  if (l <= pos && pos <= r) {
    T* node = new T();
    if (l != r) {
      int mid = getMid(l, r);
      node->left = createPersistentSegmentTree(old->left, l, mid, pos);
      node->right = createPersistentSegmentTree(old->right, mid + 1, r, pos);
      node->cnt = node->left->cnt + node->right->cnt;
    } else ++node->cnt;
    return node;
  }
  return old;
}
void compressValues() {
  int comp = 1;
  for (auto it = M.begin(); it != M.end(); ++it, ++comp) {
    M[it->first] = comp;
    RM[comp] = it->first;
  }
}
T* createBaseTree(int l, int r) {
  T* node = new T();
  if (l != r) {
    int mid = getMid(l, r);
    node->left = createBaseTree(l, mid);
    node->right = createBaseTree(mid + 1, r);
  }
  return node;
}
void createTrees() {
  root[0] = createBaseTree(1, n);
  for (int i = 1; i <= n; ++i) {
    root[i] = createPersistentSegmentTree(root[i - 1], 1, n, M[input[i]]);
  }
}
void getKth(T *a, T *b, int l, int r, int &k, int &p) {
  if (!a || !b || !k)
    return;
  int cnt = b->cnt - a->cnt;
  if (l == r && cnt == 1) {
    p = l;
    k -= cnt;
  } else if (cnt < k) {
    k -= cnt;
  } else {
    int mid = getMid(l, r);
    getKth(a->left, b->left, l, mid, k, p);
    getKth(a->right, b->right, mid + 1, r, k, p);
  }
}
void program() {
  int q, u, v, k, p;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i]);
    M[input[i]];
  }
  compressValues();
  createTrees();
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &u, &v, &k);
    getKth(root[u - 1], root[v], 1, n, k, p);
    printf("%d\n", RM[p]);
  }
}
int main() {
  // freopen("input.txt", "r", stdin);
  program();
  return 0;
}