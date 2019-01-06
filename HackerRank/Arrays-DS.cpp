// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) (1e3)
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int arr[BUFF(N_MAX)];
void program() {
  int n;
  scanf("%d", &n);
  for (int i = n; i >= 1; --i)
    scanf("%d", &arr[i]);
  for (int i = 1; i <= n; ++i)
    printf("%d ", arr[i]);
}
int main() {
  program();
  return 0;
}