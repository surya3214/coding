// AC
#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;
long long int best;
struct node {
  long long int value;
  struct node *left, *right;
} *root;
struct node *insertNode(struct node *t, long long int value) {
  if (!t) {
    t = new struct node;
    t->value = value;
    t->left = t->right = NULL;
  } else {
    if (value <= t->value)
      t->left = insertNode(t->left, value);
    else t->right = insertNode(t->right, value);
  }
  return t;
}
void display(struct node *t) {
  if (t) {
    display(t->left);
    // printf("%d\n", t->value);
    display(t->right);
  }
}
void findClosest(struct node *t, long long int value) {
  if (t) {
    if (t->value > value) {
      best = min(best, t->value - value);
      findClosest(t->left, value);
    } else findClosest(t->right, value);
  }
}
void program() {
  root = NULL;
  best = LONG_LONG_MAX;
  long long int p;
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &p);
    if (i > 1)
      findClosest(root, p);
    root = insertNode(root, p);
  }
  // display(root);
  printf("%lld\n", best);
}
int main() {
  freopen("MinimumLoss_input.txt", "r", stdin);
  program();
  return 0;
}