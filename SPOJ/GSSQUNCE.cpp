// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 50000
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
bool isFound;
int input[BUFF(N_MAX)];
void reset() { isFound = true; }
void program() {
  int tcase;
  int n, x;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &input[i]);
    if (n <= 1) isFound = false;
    else {
      sort(input + 1, input + 1 + n);
      for (int i = 3; i <= n; ++i) {
        if (input[i] == input[i - 1] && input[i] == input[i - 2]) {
          isFound = false;
          break;
        }
      }
    }
    if (isFound) printf("YES\n");
    else printf("NO\n");
  }
}
int main() {
  program();
  return 0;
}