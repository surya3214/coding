// AC
#include <iostream>
#include <cstdio>
#define MAX_S 10010
using namespace std;
char str[MAX_S];
int max_depth, pos;
void findDepth(int depth) {
  if (depth > max_depth)
    max_depth = depth;
  if (str[pos] == 'n') {
    // need to call for two children
    ++pos;
    findDepth(depth + 1);
    findDepth(depth + 1);
  } else if (str[pos] == 'l')
    ++pos;
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    pos = max_depth = 0;
    scanf("%s", str);
    findDepth(0);
    printf("%d\n", max_depth);
  }
}
int main() {
  program();
  return 0;
}