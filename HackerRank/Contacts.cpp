// AC
#include <iostream>
#include <cstdio>
#define STR_LEN_MAX 30
#define MAX_CHAR 27
using namespace std;
char input[STR_LEN_MAX];
struct node {
  int count;
  struct node *letters[MAX_CHAR];
} *trie;
struct node *insertNode(struct node *t, int idx) {
  if (!t) {
    t = new struct node;
    t->count = 0;
    for (int i = 0; i < MAX_CHAR; i++)
      t->letters[i] = NULL;
  }
  t->count++;
  if (input[idx] != '\0')
    t->letters[input[idx] - 'a'] = insertNode(t->letters[input[idx] - 'a'], idx + 1); 
  return t;
}
int find(struct node *t, int idx) {
  if (!t)
    return 0;
  if (input[idx] == '\0')
    return t->count;
  return find(t->letters[input[idx] - 'a'], idx + 1);
}
void program() {
  int n;
  scanf("%d", &n);
  trie = NULL;
  char operation[5];
  while (n--) {
    scanf("%s %s", operation, input);
    if (operation[0] == 'a')
      trie = insertNode(trie, 0);
    else if (operation[0] == 'f') {
      printf("%d\n", find(trie, 0));
    }
  }
}
int main() {
  program();
  return 0;
}