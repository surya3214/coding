// AC Sliding Window
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX (int) 1e5
#pragma GCC optimize "O3"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
struct {
  int l, r;
} ans;
struct {
  int s_cnt;
  int m_cnt;
  int sm_cnt;
  int ms_cnt;
  int sms_cnt;
} window;
int x;
void resetWindow() {
  window.s_cnt = window.m_cnt = window.sm_cnt = window.ms_cnt = window.sms_cnt = 0;
}
void updateAns(int l, int r) {
  if (ans.l == -1 || ans.r - ans.l + 1 < r - l + 1)
    ans.l = l, ans.r = r;
}
void compute() {
  int l = 0;
  for (int i = 0; str[i]; ++i) {
    switch (str[i]) {
      case 's':
        window.ms_cnt += window.m_cnt;
        window.sms_cnt += window.sm_cnt;
        ++window.s_cnt;
        break;
      case 'm':
        window.sm_cnt += window.s_cnt;
        ++window.m_cnt;
        break;
    }
    while (window.sms_cnt > x) {
      switch (str[l]) {
        case 's':
          window.sms_cnt -= window.ms_cnt;
          window.sm_cnt -= window.m_cnt;
          --window.s_cnt;
          break;
        case 'm':
          window.ms_cnt -= window.s_cnt;
          --window.m_cnt;
          break;
      }
      ++l;
    }
    if (window.sms_cnt == x)
      updateAns(l + 1, i + 1);
  }
}
void reset() {
  ans.l = -1;
  resetWindow();
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%s %d", str, &x);
    compute();
    if (ans.l == -1)
      printf("-1\n");
    else printf("%d %d\n", ans.l, ans.r);
  }
}
int main() {
  program();
  return 0;
}