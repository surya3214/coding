// AC Simluation Adhoc
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 1000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, m;
struct {
  int speed, waiting_already;
} desks[BUFF(N_MAX)];
int total_time, total_speed;
void program() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &desks[i].speed, &desks[i].waiting_already);
    total_speed += desks[i].speed;
    total_time = max(total_time, (desks[i].waiting_already - 1 + desks[i].speed) / desks[i].speed);
  }
  for (int i = 1; m > 0 && i <= n; ++i)
    m -= (desks[i].speed * total_time) - desks[i].waiting_already;
  if (m > 0)
    total_time += (m - 1 + total_speed) / total_speed;
  printf("%d\n", total_time);
}
int main() {
  program();
  return 0;
}