// AC
#include <iostream>
#include <cstdio>
#define N_MAX 1000100
#define INF 1E9
using namespace std;
int ratings[N_MAX];
int candies[N_MAX];
enum {
  PEAK = 0,
  VALLEY,
  RISE,
  FALL
} types[N_MAX];
void program() {
  int n;
  scanf("%d", &n);
  ratings[0] = ratings[n + 1] = INF;
  for (int i = 1; i <= n; i++)
    scanf("%d", &ratings[i]);
  for (int i = 1; i <= n; i++) {
    if (ratings[i - 1] < ratings[i] && ratings[i] > ratings[i + 1])
      types[i] = PEAK;
    else if (ratings[i - 1] < ratings[i] && ratings[i] <= ratings[i + 1])
      types[i] = RISE;
    else if (ratings[i - 1] >= ratings[i] && ratings[i] > ratings[i + 1])
      types[i] = FALL;
    else types[i] = VALLEY;
  }
  long long int ans = 0, tmp = 0;
  for (int i = 1; i <= n; i++) {
    if (types[i] == VALLEY)
      tmp = candies[i] = 1;
    else if (types[i] == RISE)
      tmp = candies[i] = candies[i - 1] + 1;
    ans += tmp;
    tmp = 0;
  }
  for (int i = n; i >= 1; i--) {
    if (types[i] == FALL)
      tmp = candies[i] = candies[i + 1] + 1;
    ans += tmp;
    tmp = 0;
  }
  for (int i = 1; i <= n; i++) {
    if (types[i] == PEAK)
      tmp = candies[i] = max(candies[i - 1], candies[i + 1]) + 1;
    ans += tmp;
    tmp = 0;
  }
  printf("%lld\n", ans);
}
int main() {
  // freopen("Candies_input.txt", "r", stdin);
  program();
  return 0;
}