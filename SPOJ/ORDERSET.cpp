// AC - BIT, Data Compression - Ayyyyyyyyyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define Q_MAX 200010
#define N_MAX 200010
using namespace std;
int BIT[N_MAX]; // contains info wrt to compressed_idx; in other words, has info about numbers in terms of 1 to N_MAX
int numbers[N_MAX], max_x, max_n;
int compressed_idx[N_MAX], reverse_map[N_MAX];
bool seen[N_MAX];
struct {
  char op;
  int n;
} Query[Q_MAX];
int getMid(int l, int r) { return l + (r - l) / 2; }
int compressedIdxAfterBinarySearch(int val) { // should find the index from numbers and convert to compressed_idx
  int l = 1, r = max_x, mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (numbers[mid] >= val)
      r = mid - 1;
    else l = mid + 1;
  }
  if (r != max_x)
    r++;
  return compressed_idx[r];
}
void insert(int idx, int val) {
  while (idx <= max_n) {
    BIT[idx] += val;
    idx = idx + (idx & -idx);
  }
}
int queryBIT(int idx) {
  int sum = 0;
  while (idx > 0) {
    sum += BIT[idx];
    idx = idx - (idx & -idx);
  }
  return sum;
}
int findKth(int n) {
  int l = 1, r = max_n, mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (queryBIT(mid) >= n)
      r = mid - 1;
    else l = mid + 1;
  }
  if (r != max_x && queryBIT(r + 1) >= n)
    return reverse_map[r + 1];
  return 0;
}
void program() {
  int y, n, k;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf(" %c %d", &Query[i].op, &Query[i].n);
    if (Query[i].op == 'I')
      numbers[++max_x] = Query[i].n;
  }
  sort(numbers + 1, numbers + max_x + 1);
  for (int i = 1; i <= max_x; i++) {
    if (numbers[i] != numbers[i - 1]) {
      compressed_idx[i] = ++max_n;
      reverse_map[max_n] = numbers[i];
    }
  }
  for (int i = 1; i <= n; i++) {
    switch (Query[i].op) {
      case 'I':
        y = compressedIdxAfterBinarySearch(Query[i].n);
        if (!seen[y])
          seen[y] = true, insert(y, 1);
        break;
      case 'D':
        y = compressedIdxAfterBinarySearch(Query[i].n);
        if (reverse_map[y] == Query[i].n && seen[y])
          seen[y] = false, insert(y, -1);
        break;
      case 'K':
        y = findKth(Query[i].n);
        if (y)
          printf("%d\n", y);
        else printf("invalid\n");
        break;
      case 'C':
        y = compressedIdxAfterBinarySearch(Query[i].n);
        printf("%d\n", queryBIT(y - 1));
        break;
    }
  }
}
int main() {
  program();
  return 0;
}