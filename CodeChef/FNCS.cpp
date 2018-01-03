//
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define N_MAX 100010
using namespace std;
typedef long long int ll;
int n, block_size, cur_blk;
int numbers[N_MAX];
int f_maps[N_MAX];
struct F {
  int l, r, idx;
} functions[N_MAX];
bool comparator(F a, F b) {
  if (a.l / block_size != b.l / block_size)
    return a.l / block_size <= b.l / block_size;
  return a.r <= b.r;
}
void updateFMaps() {
  for (int i = 1; i <= n; i++)
    f_maps[functions[i].idx] = i;
}
void program() {
  scanf("%d", &n);
  block_size = sqrt(n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &numbers[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d %d", functions[i].l, functions[i].r);
    functions[i].idx = i;
  }
  sort(functions + 1, functions + 1 + n, comparator);
  updateFMaps();
}
int main() {
  program();
  return 0;
}