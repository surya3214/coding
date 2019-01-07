// AC Simple
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
void program() {
  int tcase, x;
  float cgpa;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%d %f", &x, &cgpa);
    --x;
    cgpa = (cgpa * x);
    cgpa += ((8 - x) * 4);
    cgpa /= 8;
    printf("%.2f\n", cgpa);
  }
}
int main() {
  program();
  return 0;
}