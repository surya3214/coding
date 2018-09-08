// NA
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
struct {
  bool set;
  int val;
} ans;
char str[BUFF(N_MAX)];
int max_freq;
int frequency[BUFF(N_MAX)][BUFF(TOTAL_CHARS)];
int t_frequency[BUFF(TOTAL_CHARS)];
int getIndexFromChar(char x) {
  switch(x) {
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
  }
  return 0;
}
void updateAns(int x) {
  if (ans.set)
    ans.val = min(ans.val, x);
  else {
    ans.val = x;
    ans.set = true;
  }
}
bool isValidOutOf(int l, int r) {
  for (int x = 1; x <= 4; ++x) {
    t_frequency[x] = (l >= 0 ? frequency[l][x] : 0) + frequency[n - 1][x] - (r - 1 >= 0 ? frequency[r - 1][x] : 0);
    if (t_frequency[x] > max_freq)
      return false;
  }
  return true;
}
int calculate() {
  int x;
  int ans;
  bool is_valid;
  for (int i = 0; str[i]; ++i) {
    for (x = 1; x <= 4; ++x)
      frequency[i][x] = (i - 1) >= 0 ? frequency[i - 1][x] : 0;
    x = getIndexFromChar(str[i]);
    ++frequency[i][x];
    is_valid = true;
    for (x = 1; x <= 4; ++x) {
      if (frequency[i][x] > max_freq) {
        is_valid = false;
        break;
      }
    }
    if (is_valid) ans = n - i - 1;
  }
  is_valid = true;
  for (int i = n - 1; i >= 1 && is_valid; --i) {
    for (x = 1; x <= 4; ++x) {
      if (frequency[n - 1][x] - frequency[i - 1][x] > max_freq) {
        is_valid = false;
        break;
      }
    }
    ans = min(ans, i);
  }
  for (int i = 0; str[i]; ++i)
    for (int j = i; str[j] && j - i + 1 <= ans; ++j)
      if (isValidOutOf(i - 1, j + 1))
        ans = j - i + 1;
  return ans;
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