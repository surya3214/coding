// 622 Div2 AC
#include <iostream>
#include <cstdio>
#define N_MAX 35
using namespace std;
int n, ans;
int f[N_MAX];
class FibonacciDiv2 {
public:
  static int find(int N);
};
void populateFibonacci() {
  f[0] = 0;
  f[1] = 1;
  for (int i = 2; i < N_MAX; i++)
    f[i] = f[i - 1] + f[i - 2];
}
int mod(int x) {
  return x > 0 ? x : -x;
}
int min(int a, int b) {
  return a < b ? a : b;
}
int FibonacciDiv2::find(int N) {
  ans = 9999999;
  populateFibonacci();
  for (int i = 0; i < N_MAX; i++)
    ans = min(ans, mod(N - f[i]));
  return ans;
}
void program() {
  while (1) {
    scanf("%d", &n);
    printf("%d\n", FibonacciDiv2::find(n));
  }
}
int main() {
  program();
  return 0;
}