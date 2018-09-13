// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
char t_str[BUFF(LEN_MAX)];
int t_len;
void program() {
  int tcase, times, x, q;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    t_len = -1;
    scanf("%s", str);
    for (int i = 0; str[i]; ++i) {
      if (str[i] >= '0' && str[i] <= '9') {
        times = str[i] - '0';
        if (!times) t_len = -1;
        else {
          x = t_len;
          --times;
          while (times) {
            for (int j = 0; j <= x; ++j)
              t_str[++t_len] = t_str[j];
            --times;
          }
        }
      } else t_str[++t_len] = str[i];
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
      scanf("%d", &x);
      --x;
      if (x > t_len) printf("-1\n");
      else printf("%c\n", t_str[x]);
    }
  }
}
int main() {
  program();
  return 0;
}