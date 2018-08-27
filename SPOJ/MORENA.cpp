// AC Queue
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e6
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
ll seq[2][BUFF(N_MAX)]; // seq[0] starts up; seq[1] starts down
void addToSequence(bool type, ll val) {
  int pos = ++seq[type][0];
  seq[type][pos] = val;
}
void replaceLast(bool type, ll p) { seq[type][seq[type][0]] = p; }
void pushToSequence(bool type, ll p) {
  ll q, r;
  int l;
  l = seq[type][0];
  q = seq[type][l];
  r = seq[type][l - 1];
  bool enter = l & 1;
  if (type) enter = !enter;
  // in seq[0][0], odd positions expect greater value; in seq[1][0], even positions expect lower value
  // it's the opposite for seq[1]
  if (enter) { 
    if (p > q) addToSequence(type, p);
    else if (p < q && p < r && l != 2)
      replaceLast(type, p);
  } else {
    if (p < q) addToSequence(type, p);
    else if (p > q && p > r && l != 2)
      replaceLast(type, p);
  }
}
void removeLast(bool type) { --seq[type][0]; }
void forceFit(ll p) {
  pushToSequence(0, p);
  while (seq[0][0] != 2 && seq[0][seq[0][0]] != p) {
    removeLast(0);
    pushToSequence(0, p);
  }
  pushToSequence(1, p);
  while (seq[1][0] != 2 && seq[1][seq[1][0]] != p) {
    removeLast(1);
    pushToSequence(1, p);
  }
}
void push(ll p) {
  pushToSequence(0, p);
  pushToSequence(1, p);
}
void program() {
  ll x;
  scanf("%d %lld", &n, &x);
  addToSequence(0, x - 1);
  addToSequence(1, x + 1);
  addToSequence(0, x);
  addToSequence(1, x);
  for (int i = 2; i < n; ++i) {
    scanf("%lld", &x);
    push(x);
  }
  scanf("%lld", &x);
  forceFit(x);
  printf("%d\n", max(seq[0][0] - 1, seq[1][0] - 1));
}
int main() {
  program();
  return 0;
}