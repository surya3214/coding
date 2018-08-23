// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 10000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n1, n2;
int seq_1[BUFF(N_MAX)], seq_2[BUFF(N_MAX)];
int compute() {
  int sum, a_sum, b_sum;
  sum = a_sum = b_sum = 0;
  int t1, t2;
  t1 = n1, t2 = n2;
  while (t1 && t2) {
    if (seq_1[t1] == seq_2[t2]) {
      sum += seq_1[t1] + max(a_sum, b_sum);
      a_sum = b_sum = 0;
      --t1;
      --t2;
    } else if (seq_1[t1] > seq_2[t2]) {
      a_sum += seq_1[t1];
      --t1;
    } else {
      b_sum += seq_2[t2];
      --t2;
    }
  }
  while (t1) {
    a_sum += seq_1[t1];
    --t1;
  }
  while (t2) {
    b_sum += seq_2[t2];
    --t2;
  }
  sum += max(a_sum, b_sum);
  return sum;
}
void program() {
  scanf("%d", &n1);
  while (n1) {
    for (int i = 1; i <= n1; ++i)
      scanf("%d", &seq_1[i]);
    scanf("%d", &n2);
    for (int i = 1; i <= n2; ++i)
      scanf("%d", &seq_2[i]);
    printf("%d\n", compute());
    scanf("%d", &n1);
  }
}
int main() {
  program();
  return 0;
}