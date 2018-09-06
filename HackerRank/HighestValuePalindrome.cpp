// AC Adhoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, k;
char str[BUFF(N_MAX)];
char ans[BUFF(N_MAX)];
void program() {
  int min_needed = 0;
  scanf("%d %d", &n, &k);
  scanf("%s", str);
  int t_r = ((n + 1) / 2) - 1;
  for (int i = 0; i <= t_r; ++i)
    if (str[i] != str[n - i - 1])
      ++min_needed;
  if (min_needed > k)
    printf("-1\n");
  else {
    int j;
    for (int i = 0; i <= t_r; ++i) {
      j = n - i - 1;
      ans[i] = str[i], ans[j] = str[j];
      if (str[i] == str[j])
        continue;
      if (str[i] > str[j])
        ans[j] = str[i];
      else ans[i] = str[j];
      --k;
    }
    for (int i = 0; i <= t_r; ++i) {
      if (ans[i] == '9')
        continue;
      j = n - i - 1;
      if (i != j && str[i] == str[j] && k >= 2) {
        ans[i] = ans[j] = '9';
        k -= 2;
      } else if ((i == j || str[i] != str[j]) && k >= 1) {
        ans[i] = ans[j] = '9';
        --k;
      }
    }
    ans[n] = '\0';
    printf("%s\n", ans);
  }
}
int main() {
  program();
  return 0;
}