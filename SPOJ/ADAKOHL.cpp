// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 3000
#define SLOPES_MAX 4501500
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
int n, ans;
struct {
  int x, y, q;
} points[BUFF(N_MAX)];
int d_slopes[BUFF(SLOPES_MAX)];
void reset() { ans = d_slopes[0] = 0; }
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (const std::pair<T1,T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    return h1 ^ h2;  
  }
};
struct L {
  L() { idx = -1; }
  int idx;
  bool taken[BUFF(N_MAX)];
};
bool visited_h[BUFF(N_MAX)], visited_v[BUFF(N_MAX)];
unordered_map<pair<int, int>, L, pair_hash> slopeMap;
void compute() {
  ans = 0;
  int v_s, h_s, g;
  struct L *t;
  struct {
    int num;
    int den;
  } slope;
  slopeMap.clear();
  for (int i = 1; i <= n; ++i) {
    v_s = h_s = points[i].q;
    for (int j = i + 1; j <= n; ++j) {
      if (points[i].x == points[j].x) {
        if (!visited_v[j]) {
          v_s += points[j].q;
          visited_v[j] = true;
        }
      } else if (points[i].y == points[j].y) {
        if (!visited_h[j]) {
          h_s += points[j].q;
          visited_h[j] = true;
        }
      } else {
        slope.num = points[j].y - points[i].y;
        slope.den = points[j].x - points[i].x;
        if (slope.num < 0 && slope.den < 0)
          slope.num = -slope.num, slope.den = -slope.den;
        else if (slope.den < 0) slope.den = -slope.den, slope.num = -slope.num;
        g = __gcd(slope.num, slope.den);
        slope.num /= g;
        slope.den /= g;
        t = &slopeMap[make_pair(slope.num, slope.den)];
        if (t->idx == -1) {
          t->idx = ++d_slopes[0];
          d_slopes[t->idx] = points[i].q;
          t->taken[i] = true;
        }
        if (!t->taken[j]) {
          d_slopes[t->idx] += points[j].q;
          t->taken[j] = true;
        }
      }
      ans = max(ans, max(h_s, v_s));
    }
    ans = max(ans, points[i].q);
  }
  for (int i = 1; i <= d_slopes[0]; ++i)
    ans = max(ans, d_slopes[i]);
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].q);
      visited_h[i] = visited_v[i] = false;
    }
    compute();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}