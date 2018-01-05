// AC - Index Compression, Offline - Ayyyyyyyyyyyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define N_MAX 1000010
#define M_MAX 1000010
using namespace std;
int n, cur_rank, numbers_idx, cur_time;
struct N {
  int val, rank;
} numbers[N_MAX + M_MAX];
struct {
  char op;
  int val;
} Query[M_MAX];
int getMid(int l, int r) { return l + (r - l) / 2; }
void insertIntoNumbers(int val) {
  ++numbers_idx;
  numbers[numbers_idx].val = val;
  numbers[numbers_idx].rank = ++cur_rank;
}
bool comparator(N a, N b) { 
  if (a.val == b.val)
    return a.rank < b.rank;
  return a.val < b.val;
}
int binarySearch(int val) {
  int l = 1, r = numbers_idx, mid;
  while (l <= r) {
    mid = getMid(l, r);
    if (numbers[mid].val < val || (numbers[mid].val == val && numbers[mid].rank == 0)) // mid is invalid
      l = mid + 1;
    else r = mid - 1; // mid is valid
  }
  if (r != numbers_idx) r++;
  return r;
}
void program() {
  int m, tmp, y;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &tmp);
    insertIntoNumbers(tmp);
  }
  for (int i = 1; i <= m; i++) {
    scanf(" %c %d", &Query[i].op, &Query[i].val);
    if (Query[i].op == 'I')
      insertIntoNumbers(Query[i].val);
  }
  sort(numbers + 1, numbers + numbers_idx + 1, comparator);
  cur_rank = n;
  for (int i = 1; i <= m; i++) {
    switch(Query[i].op) {
      case 'S':
        y = binarySearch(Query[i].val);
        if (numbers[y].val == Query[i].val && numbers[y].rank != 0 && numbers[y].rank <= cur_rank)
          printf("%d\n", numbers[y].rank);
        else printf("NONE\n");
        break;
      case 'I':
        printf("%d\n", ++cur_rank);
        break;
      case 'D':
        y = binarySearch(Query[i].val);
        if (numbers[y].val == Query[i].val && numbers[y].rank != 0 && numbers[y].rank <= cur_rank) {
          printf("%d\n", numbers[y].rank);
          numbers[y].rank = 0;
        } else printf("NONE\n");
        break;
    }
  }
}
int main() {
  program();
  return 0;
}