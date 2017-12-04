// AC
#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
#define N_MAX 200010
#define SEG_TREE_SIZE (int)(ceil(log2(N_MAX)) + 10)
using namespace std;
const int N = 5e5 + 10;
int n;
long long int stocks[N_MAX];
long long int dp2[N_MAX];
long long int dp;
int l[N_MAX], r[N_MAX];
vector<int> safeStocks[N_MAX];
long long int segmentTree[N_MAX * 4];
long long int max(long long int a, long long int b) {
  return a > b ? a : b;
}
int getMid(int l, int r) {
  return l + (r - l) / 2;
}
int getLeftChild(int i) {
  return 2 * i;
}
int getRightChild(int i) {
  return 2 * i + 1;
}
void pushToSegmentTree(int s_start, int s_end, int s_ind, int ind, long long int val) {
  if (s_start > ind || s_end < ind)
    return;
  if (s_start == s_end) {
    segmentTree[s_ind] = val;
    return;
  }
  int s_mid = getMid(s_start, s_end);
  int left_child = getLeftChild(s_ind);
  int right_child = getRightChild(s_ind);
  pushToSegmentTree(s_start, s_mid, left_child, ind, val);
  pushToSegmentTree(s_mid + 1, s_end, right_child, ind, val);
  segmentTree[s_ind] = max(segmentTree[left_child], segmentTree[right_child]);
}
long long int query(int s_start, int s_end, int s_ind, int q_start, int q_end) {
  if (q_end < s_start || s_end < q_start)
    return 0;
  if (q_start <= s_start && s_end <= q_end)
    return segmentTree[s_ind];
  int s_mid = getMid(s_start, s_end);
  return max(query(s_start, s_mid, getLeftChild(s_ind), q_start, q_end), query(s_mid + 1, s_end, getRightChild(s_ind), q_start, q_end));
}
void program() {
  int safe_no;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld", &stocks[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &l[i]);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &r[i]);
    safe_no = i + r[i] + 1;
    if (safe_no <= n)
      safeStocks[safe_no].push_back(i);
  }
  int ind;
  for (int i = 1; i <= n; i++) {
    for (int ind:safeStocks[i])
      pushToSegmentTree(1, n, 1, ind, dp2[ind]);
    ind = i - l[i] - 1;
    dp2[i] = ((ind <= 0) ? 0 : query(1, n, 1, 1, ind)) + stocks[i];
    dp = max(dp, dp2[i]);
    safeStocks[i].clear();
  }
  printf("%lld\n", dp);
}
int main() {
  // freopen("StockPortfolio_input.txt", "r", stdin);
  program();
  return 0;
}