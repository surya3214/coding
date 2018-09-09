// AC Binary Search
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 500000
#define TOTAL_CHARS 4
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
char str[BUFF(N_MAX)];
int max_freq;
int frequency[BUFF(N_MAX)][BUFF(TOTAL_CHARS)];
int t_frequency[BUFF(TOTAL_CHARS)];
int w_frequency[BUFF(TOTAL_CHARS)];
int getIndexFromChar(char x) {
  switch(x) {
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
  }
  return 0;
}
bool isTFreqValid() {
  for (int k = 1; k <= 4; ++k)
    if (t_frequency[k] > max_freq)
      return false;
  return true;
}
bool isPossible(int size) {
  for (int k = 1; k <= 4; ++k)
    w_frequency[k] = 0;
  int j = -1, x;
  for (int i = 0; str[i + size - 1]; ++i) {
    while (j + 1 <= i + size - 1) {
      ++j;
      x = getIndexFromChar(str[j]);
      ++w_frequency[x];
    }
    for (int k = 1; k <= 4; ++k)
      t_frequency[k] = frequency[n - 1][k] - w_frequency[k];
    if (isTFreqValid())
      return true;
    x = getIndexFromChar(str[i]);
    --w_frequency[x];
  }
  return false;
}
int getMid(int l, int r) { return l + (r - l) / 2; }
int calculate() {
  int x;
  for (int i = 0; str[i]; ++i) {
    for (int k = 1; k <= 4; ++k)
      frequency[i][k] = (i - 1) >= 0 ? frequency[i - 1][k] : 0;
    x = getIndexFromChar(str[i]);
    ++frequency[i][x];
  }
  for (int k = 1; k <= 4; ++k)
    t_frequency[k] = frequency[n - 1][k];
  if (isTFreqValid())
    return 0;
  int l, r, mid;
  l = 1, r = n;
  while (l <= r) {
    mid = getMid(l, r);
    if (isPossible(mid))
      r = mid - 1;
    else l = mid + 1;
  }
  return r + 1;
}
void program() {
  scanf("%d", &n);
  max_freq = n / 4;
  scanf("%s", str);
  printf("%d\n", calculate());
}
int main() {
  freopen("input.txt", "r", stdin);
  program();
  return 0;
}