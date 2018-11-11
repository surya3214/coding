// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  int time;
  vector<int> q;
} m_list[BUFF(VAL_MAX)];
int t_time;
void reset() { ++t_time; }
void sanitizeList(int num) {
  if (m_list[num].time != t_time) {
    m_list[num].q.clear();
    m_list[num].time = t_time;
  }
}
void addIndex(int num, int idx) {
  sanitizeList(num);
  m_list[num].q.push_back(idx);
}
bool isPossible() {
  int present_at;
  for (int i = 1; i <= n; ++i) {
    present_at = 0;
    sanitizeList(i);
    for (int j = 0; j < m_list[i].q.size(); ++j) {
      sanitizeList(m_list[i].q[j]);
      if (m_list[m_list[i].q[j]].q.size()) {
        ++present_at;
        if (present_at == 2)
          return true;
      }
    }
  }
  return false;
}
void program() {
  int tcase, num;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &num);
      addIndex(num, i);
    }
    if (isPossible())
      printf("Truly Happy\n");
    else printf("Poor Chef\n");
  }
}
int main() {
  program();
  return 0;
}