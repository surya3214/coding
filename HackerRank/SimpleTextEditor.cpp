// AC Stack, Square Root Decomposition Ayyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define Q_MAX (int) 1e6
#define LEN_MAX (int) (2 * 1e6)
#define BLOCKS_MAX 1415
#define BLOCKS_SIZE 1415
#pragma GCC optimize "O0" // -> Any optimization is producing longer runtime and wrong results
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
struct {
  int blk_l, blk_r;
  int valid_count;
  int dirty;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(LEN_MAX, (blk_id * block_size)); }
void getBlockParameters(int x, int &blk_id, int &blk_l, int &blk_r) {
  blk_id = getBlockNumber(x);
  blk_l = blocks[blk_id].blk_l;
  blk_r = blocks[blk_id].blk_r;
}
int validity[BUFF(LEN_MAX)];
char str[BUFF(LEN_MAX)];
int s_top;
char buffer[BUFF(LEN_MAX)];
struct {
  bool type;
  int l, r;
} m_stack[BUFF(Q_MAX)];
int top;
int k;
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].dirty != 0) {
    blocks[blk_id].valid_count = 0;
    for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i) {
      validity[i] += blocks[blk_id].dirty;
      if (validity[i] == 1)
        ++blocks[blk_id].valid_count;
    }
    blocks[blk_id].dirty = 0;
  }
}
void updateBlocks(int l, int r, int val) {
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    getBlockParameters(l, blk_id, blk_l, blk_r);
    if (l == blk_l && blk_r <= r) {
      blocks[blk_id].dirty += val;
      l = blk_r + 1;
    } else {
      sanitizeBlock(blk_id);
      int t_r = min(blk_r, r);
      for (int i = l; i <= t_r; ++i) {
        if (validity[i] == 1 && val == -1)
          --blocks[blk_id].valid_count;
        else if (validity[i] == 0 && val == 1)
          ++blocks[blk_id].valid_count;
        validity[i] += val;
      }
      l = t_r + 1;
    }
  }
}
void addToStack(int l, int r, bool type) {
  ++top;
  m_stack[top].type = type;
  m_stack[top].l = l;
  m_stack[top].r = r;
}
void addString() {
  int l, r;
  l = s_top + 1;
  for (int i = 0; buffer[i]; ++i)
    str[++s_top] = buffer[i];
  r = s_top;
  updateBlocks(l, r, 1);
  addToStack(l, r, 1);
}
int removeKFromBlock(int blk_id) {
  if (blocks[blk_id].dirty >= 0) {
    if (blocks[blk_id].dirty)
      sanitizeBlock(blk_id);
    if (k > blocks[blk_id].valid_count)
      k -= blocks[blk_id].valid_count;
    else if (k <= blocks[blk_id].valid_count)
      return true;
  }
  return false;
}
int getKValidChars() {
  int r;
  int ret = 0;
  int blk_id, blk_l, blk_r;
  while (r >= 1 && !ret) {
    getBlockParameters(r, blk_id, blk_l, blk_r);
    if (removeKFromBlock(blk_id)) {
      for (int i = blk_r; i >= blk_l; --i) {
        if (validity[i] == 1) {
          --k;
          if (!k) {
            ret = i;
            break;
          }
        }
      }
    }
    r = blk_l - 1;
  }
  return ret;
}
void printKth() {
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    if (removeKFromBlock(blk_id)) {
      for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i) {
        if (validity[i] == 1) {
          --k;
          if (!k) {
            printf("%c\n", str[i]);
            return;
          }
        }
      }
    }
  }
}
void undo() {
  int val = (!(m_stack[top].type)) ? 1 : -1;
  updateBlocks(m_stack[top].l, m_stack[top].r, val);
  --top;
}
void deleteKChars() {
  int l, r;
  r = s_top;
  l = getKValidChars();
  updateBlocks(l, r, -1);
  addToStack(l, r, 0);
}
void program() {
  int q, type;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &type);
    if (type == 1) {
      scanf(" %s", buffer);
      addString();
    } else if (type == 2) {
      scanf("%d", &k);
      deleteKChars();
    } else if (type == 3) {
      scanf("%d", &k);
      printKth();
    } else undo();
  }
}
void init() {
  block_size = BLOCKS_SIZE;
  block_count = BLOCKS_MAX;
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
  }
}
int main() {
  init();
  program();
  return 0;
}