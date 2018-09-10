// AC Adhoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define VAL_MAX 200
#define N_MAX (int) (2 * 1e5)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k;
int nums[BUFF(N_MAX)];
int freq[BUFF(VAL_MAX)];
bool type;
void getMedian(int &a, int &b) {
  b = 0;
  int median = (k + 1) / 2;
  int seen = 0;
  bool finding_a = true;
  for (int i = 0; i <= VAL_MAX; ++i) {
    if (seen + freq[i] >= median) {
      if (finding_a) {
        a = i;
        ++median;
        finding_a = false;
        --i;
        continue;
      }
      b = i;
      return;
    }
    seen += freq[i];
  }
}
void program() {
  int cnt = 0;
  scanf("%d %d", &n, &k);
  int a, b, m_val, d;
  type = !(k % 2); // false if odd, true if even
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &nums[i]);
    if (i > k) {
      getMedian(a, b);
      if (type) m_val = a + b;
      else m_val = 2 * a;
      if (nums[i] >= m_val)
        ++cnt;
      --freq[nums[i - k]];
    }
    ++freq[nums[i]];
  }
  printf("%d\n", cnt);
}
int main() {
  program();
  return 0;
}