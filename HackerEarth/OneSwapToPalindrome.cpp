// AC
#include <bits/stdc++.h>
#include <cstring>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
using namespace std;
typedef long long int ll;
char str[BUFF(N_MAX)];
int n;
char lookingFor, replaceWith;
bool possible(int i, int j, bool swapped) {
  if (i > j) {
    if (lookingFor == 0) return true;
    return false;
  } else if (i == j) {
    if (lookingFor == 0 || str[i] == lookingFor) return true;
    return false;
  }
  if (str[i] == str[j])
    return possible(i + 1, j - 1, swapped);
  else if (!swapped) { // swap str[i] or str[j]
    lookingFor = str[j];
    replaceWith = str[i];
    if (possible(i + 1, j - 1, true))
      return true;
    lookingFor = str[i];
    replaceWith = str[j];
    if (possible(i + 1, j - 1, true))
      return true;
  } else { // already swapped
    if (str[i] == lookingFor && str[j] == replaceWith) {
      lookingFor = 0;
      if (possible(i + 1, j - 1, swapped))
        return true;
      else lookingFor = str[i];
    }
    if (str[j] == lookingFor && str[i] == replaceWith) {
      lookingFor = 0;
      if (possible(i + 1, j - 1, swapped))
        return true;
      else lookingFor = str[j];
    }
  }
  return false;
}
void reset() { lookingFor = 0; }
void program() {
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; ++i) {
    reset();
    scanf(" %s", str);
    n = strlen(str);
    if (possible(0, n - 1, 0))
      printf("Yes\n");
    else printf("No\n");
  }
}
int main() {
  program();
  return 0;
}