#include <iostream>
#include <cstdio>
using namespace std;
void program() {
  int n, m, tmp;
  scanf("%d %d", &n, &m);
  int ans = 0;
  while (n--) {
    scanf("%d", &tmp);
    ans += tmp;
  }
  printf("%d\n", ans);
}
int main() {
  freopen("MatrixLand_input.txt", "r", stdin);
  program();
  return 0;
}