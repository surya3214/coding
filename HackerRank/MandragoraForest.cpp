// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
using namespace std;
int health[BUFF(N_MAX)];
struct {
  int buff1[BUFF(N_MAX / 2)], buff2[BUFF(N_MAX / 2)];
  int e1, e2;
  int t1, t2;
} buffer;
long sum[BUFF(N_MAX)];
long ans;
int n;
int getMid(int l, int r) { return l + (r - l) / 2; }
void copyToBuffer(int &s1, int &e1, int &s2, int &e2) {
  buffer.e1 = buffer.e2 = 0;
  for (int i = s1; i <= e1; i++)
    buffer.buff1[buffer.e1++] = health[i];
  for (int i = s2; i <= e2; i++)
    buffer.buff2[buffer.e2++] = health[i];
}
void fillArrayfromBuffer(int p) {
  buffer.t1 = buffer.t2 = 0;
  while (buffer.t1 < buffer.e1 && buffer.t2 < buffer.e2) {
    if (buffer.buff1[buffer.t1] <= buffer.buff2[buffer.t2])
      health[p++] = buffer.buff1[buffer.t1++];
    else health[p++] = buffer.buff2[buffer.t2++];
  }
  while (buffer.t1 < buffer.e1)
    health[p++] = buffer.buff1[buffer.t1++];
  while (buffer.t2 < buffer.e2)
    health[p++] = buffer.buff2[buffer.t2++];
}
void merge(int s1, int e1, int e2) {
  int s2 = e1 + 1;
  copyToBuffer(s1, e1, s2, e2);
  fillArrayfromBuffer(s1);
}
void merge_sort(int l, int r) {
  if (l < r) {
    int mid = getMid(l, r);
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
  }
}
void program() {
  int tcase;
  scanf("%d", &tcase);
  while (tcase--) {
    scanf("%d", &n);
    ans = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &health[i]);
    merge_sort(1, n);
    for (int i = 1; i <= n; i++)
      sum[i] = sum[i - 1] + health[i];
    for (int i = n - 1; i >= 0; i--)
      ans = max(ans, (i + 1) * (sum[n] - sum[i]));
    printf("%ld\n", ans);
  }
}
int main() {
  program();
  return 0;
}