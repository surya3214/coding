// AC
#include <iostream>
#include <cstdio>
#define MAX_N 2 * 100010
using namespace std;
char input[MAX_N];
long long int tmp;
long long int ans;
long long int MOD = 1000000000 + 7;
void program() {
  scanf("%s", input);
  ans = tmp = input[0] - '0';
  for (int i = 1; input[i] != '\0'; i++) {
    tmp = (tmp * 10) + (input[i] - '0') * (i + 1);
    tmp %= MOD;
    ans = (ans + tmp) % MOD;
  }
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}