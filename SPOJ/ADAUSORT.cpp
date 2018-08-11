// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
struct I {
  int idx;
  int val;
} input[BUFF(N_MAX)];
int n;
bool m_comparator(I a, I b) {
  if (a.val != b.val)
    return a.val < b.val;
  return a.idx > b.idx;
}
void program() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &input[i].val);
    input[i].idx = i;
  }
  sort(input + 1, input + 1 + n, m_comparator);
  for (int i = 1; i <= n; ++i)
    printf("%d ", input[i].idx);
}
int main() {
  program();
  return 0;
}