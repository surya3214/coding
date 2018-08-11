// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define LEN_MAX 100000
#define CHARS_MAX 26
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
char input[BUFF(LEN_MAX)];
int seen[BUFF(CHARS_MAX)];
bool one_assigned;
bool possible;
void reset() {
  one_assigned = false;
  possible = true;
  for (int i = 0; i < CHARS_MAX; ++i)
    seen[i] = 0;
}
int getIndexFromCharacter(char x) { return x - 'a'; }
void addToTotal(char x) {
  int idx = getIndexFromCharacter(x);
  ++seen[idx];
}
void program() {
  while (scanf("%s", input) != EOF) {
    reset();
    for (int i = 0; input[i] != '\0'; ++i)
      addToTotal(input[i]);
    for (int i = 0; i < CHARS_MAX; ++i) {
      if (seen[i] & 1) {
        if (one_assigned) {
          possible = false; break;
        } else one_assigned = true;
      }
    }
    if (possible) printf("1\n");
    else printf("-1\n");
  }
}
int main() {
  program();
  return 0;
}