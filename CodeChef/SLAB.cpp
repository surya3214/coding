// WA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
int in;
int slabs[] = { 0, 250000, 500000, 750000, 1000000, 1250000, 1500000, 9999999 };
float tax[] = { 0, 0, .05, .1, .15, .2, .25, .3 };
int precomputed[7] = { 0, 0 };
void ready() {
  for (int i = 2; i < 7; ++i)
    precomputed[i] = precomputed[i - 1] + (slabs[i] - slabs[i - 1]) * tax[i];
}
void program() {
  cin >> in;
  int idx;
  for (idx = 0; slabs[idx] < in; ++idx);
  int total_tax = (in - slabs[idx - 1]) * tax[idx] + precomputed[idx - 1];
  cout << in - total_tax << endl;
}
int main() {
  ios::sync_with_stdio(0);
	cin.tie(0);
  ready();
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int tcase;
  cin >> tcase;
  while (tcase--)
    program();
  return 0;
}