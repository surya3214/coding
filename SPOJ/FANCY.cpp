// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 30
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int ways[BUFF(LEN_MAX)];
char str[BUFF(LEN_MAX)];
void ready() {
  ways[0] = ways[1] = 1;
  int sum_so_far = 2;
  for (int i = 2; i <= LEN_MAX; ++i) {
    ways[i] = sum_so_far;
    sum_so_far += ways[i];
  }
}
ll compute() {
  int l, r;
  l = 0;
  ll ret = 1;
  while (str[l]) {
    r = l;
    while (str[r + 1] && str[r + 1] == str[l])
      ++r;
    ret = ret * ways[r - l + 1];
    l = r + 1;
  }
  return ret;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%s", str);
    printf("%lld\n", compute());
  }
}
int main() {
  ready();
  program();
  return 0;
}