// AC STL
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, last_answer, seq;
vector<int> sequences[BUFF(N_MAX)];
struct {
  int type;
  int x, y;
} buffer;
void program() {
  int q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", &buffer.type, &buffer.x, &buffer.y);
    seq = (buffer.x ^ last_answer) % n;
    if (buffer.type == 1)
      sequences[seq].push_back(buffer.y);
    else {
      last_answer = sequences[seq][(buffer.y % sequences[seq].size())];
      printf("%d\n", last_answer);
    }
  }
}
int main() {
  program();
  return 0;
}