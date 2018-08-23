// AC
#include <stdio.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define STR_MAX 
#define L_MAX (int) 1e6
#define true 1
#define false 0
// #pragma GCC optimize "O4"
typedef int bool;
typedef long long int ll;
typedef unsigned long long int ull;
char str[BUFF(STR_MAX)];
struct L {
  struct L *left, *right;
  int val;
} *l, *r, l_nodes_pool[BUFF(L_MAX)];
int l_pool_ptr;
bool type;
int val;
void reverse() { if (l && l != r) type = !type; }
int removeFront() {
  int ret = l->val;
  if (l == r) l = r = NULL, type = false;
  else {
    l = l->right;
    l->left = NULL;
  }
  return ret;
}
int removeBack() {
  int ret = r->val;
  if (l == r) l = r = NULL, type = false;
  else {
    r = r->left;
    r->right = NULL;
  }
  return ret;
}
int removeFromQ(bool t) {
  int ret;
  if (t) { // 'f'ront
    if (type) ret = removeBack();
    else ret = removeFront();
  } else { // 'b'ack
    if (type) ret = removeFront();
    else ret = removeBack();
  }
  return ret;
}
struct L *getLNodesFromPool() { return &l_nodes_pool[l_pool_ptr++]; }
void pushFront() {
  struct L *t = getLNodesFromPool();
  t->val = val;
  t->left = t->right = NULL;
  if (!l) l = r = t;
  else {
    t->right = l;
    l->left = t;
    l = t;
  }
}
void pushBack() {
  struct L *t = getLNodesFromPool();
  t->val = val;
  t->left = t->right = NULL;
  if (!r) l = r = t;
  else {
    r->right = t;
    t->left = r;
    r = t;
  }
}
void pushToQ(bool t) {
  if (t) { // 'p'ush_back
    if (type) pushFront();
    else pushBack();
  } else { // 't'oFront
    if (type) pushBack();
    else pushFront();
  }
}
void program() {
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%s", str);
    if (str[0] == 'r')
      reverse();
    else if (str[0] == 'f' || str[0] == 'b') {
      if (!l) printf("No job for Ada?\n");
      else {
        val = removeFromQ(str[0] == 'f');
        printf("%d\n", val);
      }
    } else {
      scanf("%d", &val);
      pushToQ(str[0] == 'p');
    }
  }
}
int main() {
  program();
  return 0;
}