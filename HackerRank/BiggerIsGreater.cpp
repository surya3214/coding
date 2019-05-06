// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100
#define CHARS_MAX 26
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(LEN_MAX)];
int numbers[BUFF(LEN_MAX)];
int len;
int getInteger(char x) { return x - 'a' + 1; }
char getChar(int x) { return 'a' + x - 1; }
int isFound[BUFF(CHARS_MAX)];
void reset() {
  for (int i = 0; i <= CHARS_MAX; ++i)
    isFound[i] = 0;
}
void m_swap(int i, int j) {
  int t = numbers[i];
  numbers[i] = numbers[j];
  numbers[j] = t;
}
bool isPossible() {
  reset();
  for (int i = len; i >= 1; --i) {
    for (int j = numbers[i] + 1; j <= CHARS_MAX; ++j) {
      if (isFound[j]) {
        m_swap(i, isFound[j]);
        sort(numbers + 1 + i, numbers + 1 + len);
        return true;
      }
    }
    isFound[numbers[i]] = i;
  }
  return false;
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    scanf("%s", str);
    for (len = 0; str[len]; ++len)
      numbers[len + 1] = getInteger(str[len]);
    if (isPossible()) {
      for (int i = 1; i <= len; ++i)
        printf("%c", getChar(numbers[i]));
    } else printf("no answer");
    printf("\n");
  }
}
int main() {
  program();
  return 0;
}