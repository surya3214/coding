// AC
#include <iostream>
#include <cstdio>
#define N_MAX 65
#define CHAR_MAX 12
using namespace std;
bool found;
char input[N_MAX];
char ans[N_MAX];
struct node {
  bool ends;
  struct node *letters[CHAR_MAX];
} *trie;
struct node *insertNode(struct node *t, int idx) {
  if (t)
    if (input[idx] == '\0' || t->ends)
      found = true;
  if (!t) {
    t = new struct node;
    t->ends = false;
    for (int i = 0; i < CHAR_MAX; i++)
      t->letters[i] = NULL;
  }
  if (input[idx] != '\0')
    t->letters[input[idx] - 'a'] = insertNode(t->letters[input[idx] - 'a'], idx + 1);
  else t->ends = true;
  return t;
}
void program() {
  int n;
  scanf("%d", &n);
  trie = NULL;
  while (n--) {
    scanf("%s", input);
    if (!found) {
      trie = insertNode(trie, 0);
      if (found) {
        int i = 0;
        do {
          ans[i] = input[i];
          i++;
        } while(input[i] != '\0');
      }
    }
  }
  if (!found)
    printf("GOOD SET\n");
  else {
    printf("BAD SET\n");
    printf("%s\n", ans);
  }
}
int main() {
  program();
  return 0;
}