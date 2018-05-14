// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100
using namespace std;
char str[BUFF(LEN_MAX)];
int cnt[BUFF(LEN_MAX)];
void program() {
  long long ans, n;
  scanf("%s", str + 1);
  scanf("%lld", &n);
  cnt[0] = 0;
  int len = 0;
  for (int i = 1; str[i] != '\0'; i++) {
    cnt[i] = cnt[i - 1] + (str[i] == 'a');
    ++len;
  }
  ans = cnt[len] * (n / len) + cnt[n % len];
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}