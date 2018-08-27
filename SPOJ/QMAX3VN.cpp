// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define BLOCKS_MAX 317
#define BLOCKS_SIZE 317
#define N_MAX 100000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  bool inited;
  int val;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, blk_id * block_size); }
int heights[BUFF(N_MAX)];
int n;
void addToBlocks(int blk_id, int h) {
  if (!blocks[blk_id].inited) {
    blocks[blk_id].val = h;
    blocks[blk_id].inited = true;
  } else blocks[blk_id].val = max(blocks[blk_id].val, h);
}
void addHeight(int h, int p) {
  heights[p] = h;
  addToBlocks(getBlockNumber(p), h);
}
int findMax(int l, int r) {
  while (l <= r) {
    
  }
}
void program() {
  char op, l, r;
  scanf("%d", &n);
  block_size = BLOCKS_SIZE;
  for (int i = 1; i <= n; ++i) {
    scanf("%c %d %d", &op, &l, &r);
    if (op == 'A')
      addHeight(l, r);
    else printf("%d\n", findMax(l, r));
  }
}
int main() {
  program();
  return 0;
}