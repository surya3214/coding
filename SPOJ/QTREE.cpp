// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ROOT 1
#define N_MAX (int) 1e4
#define BLOCKS_MAX 100
#define MAX_POWERS_OF_TWO 14 // 2^14 >= N_MAX
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n, chain_id;
struct {
  int start, end;
} chains[BUFF(N_MAX)];
int linear_chain_cost[BUFF(N_MAX)]; // blockify this; contains costs
int l_ptr;
struct {
  int blk_l, blk_r;
  int max_weight;
  bool dirty;
} blocks[BUFF(BLOCKS_MAX)];
int block_size, block_count;
int getBlockNumber(int x) { return (x - 1) / block_size + 1; }
int getBlockLeft(int blk_id) { return (blk_id - 1) * block_size + 1; }
int getBlockRight(int blk_id) { return min(N_MAX, block_size * blk_id); }
struct E {
  int u, v, weight;
  int chain_pos;
} edges[BUFF(N_MAX)];
int e_ptr;
struct {
  int depth;
  int chain_info;
  int chain_head;
  int chain_pos;
  int sub_size;
  vector<int> edges;
  int parent_at[BUFF(MAX_POWERS_OF_TWO)];
} nodes_info[BUFF(N_MAX)];
void reset() {
  e_ptr = l_ptr = 0;
  for (int i = 1; i <= N_MAX; ++i) {
    chains[i].start = chains[i].end = 0;
    nodes_info[i].chain_head = nodes_info[i].chain_info = nodes_info[i].sub_size = 0;
    nodes_info[i].edges.clear();
    for (int j = 0; j <= MAX_POWERS_OF_TWO; ++j)
      nodes_info[i].parent_at[j] = 0;
  }
}
void addToEdges(int u, int v, int w) {
  ++e_ptr;
  edges[e_ptr].u = u;
  edges[e_ptr].v = v;
  edges[e_ptr].weight = w;
}
void computeForBlock(int blk_id) {
  blocks[blk_id].max_weight = 0;
  for (int i = blocks[blk_id].blk_l; i <= blocks[blk_id].blk_r; ++i)
    blocks[blk_id].max_weight = max(blocks[blk_id].max_weight, linear_chain_cost[i]);
}
void buildBlocks() {
  block_size = ceil(sqrt(l_ptr));
  block_count = getBlockNumber(l_ptr);
  for (int blk_id = 1; blk_id <= block_count; ++blk_id) {
    blocks[blk_id].blk_l = getBlockLeft(blk_id);
    blocks[blk_id].blk_r = getBlockRight(blk_id);
    blocks[blk_id].dirty = false;
    computeForBlock(blk_id);
  }
}
void dfs(int u, int parent, int depth) { // computes each node's parent, depth, sub_size
  int v, e;
  nodes_info[u].parent_at[0] = parent;
  nodes_info[u].depth = depth;
  nodes_info[u].sub_size = 1;
  for (int i = 0; i < nodes_info[u].edges.size(); ++i) {
    e = nodes_info[u].edges[i];
    if (edges[e].u == u)
      v = edges[e].v;
    else v = edges[e].u;
    if (v == nodes_info[u].parent_at[0])
      continue;
    dfs(v, u, depth + 1);
    nodes_info[u].sub_size += nodes_info[v].sub_size;
  }
}
void hld(int u, int chain, int chain_head, int to_cost, int e_id) {
  int v, e;
  ++l_ptr;
  linear_chain_cost[l_ptr] = to_cost;
  edges[e_id].chain_pos = l_ptr;
  nodes_info[u].chain_pos = l_ptr;
  if (!chains[chain].start)
    chains[chain].start = l_ptr;
  nodes_info[u].chain_head = chain_head;
  nodes_info[u].chain_info = chain;
  struct {
    int size;
    int v;
    int cost;
    int e_id;
  } special_child;
  special_child.size = 0;
  special_child.v = -1;
  for (int i = 0; i < nodes_info[u].edges.size(); ++i) {
    e = nodes_info[u].edges[i];
    if (edges[e].u == u)
      v = edges[e].v;
    else v = edges[e].u;
    if (v == nodes_info[u].parent_at[0])
      continue;
    if (nodes_info[v].sub_size > special_child.size) {
      special_child.v = v;
      special_child.cost = edges[e].weight;
      special_child.size = nodes_info[v].sub_size;
      special_child.e_id = e;
    }
  }
  if (special_child.v != -1)
    hld(special_child.v, chain, chain_head, special_child.cost, special_child.e_id);
  if (u == chain_head)
    chains[chain].end = l_ptr;
  for (int i = 0; i < nodes_info[u].edges.size(); ++i) {
    e = nodes_info[u].edges[i];
    if (edges[e].u == u)
      v = edges[e].v;
    else v = edges[e].u;
    if (v == nodes_info[u].parent_at[0] || v == special_child.v)
      continue;
    hld(v, ++chain_id, v, edges[e].weight, e); // starts a new chain from v
  }
}
void change(int e_id, int w) {
  int pos = edges[e_id].chain_pos;
  linear_chain_cost[pos] = w;
  blocks[getBlockNumber(pos)].dirty = true;
}
int LCA(int u, int v) {
  if (nodes_info[v].depth < nodes_info[u].depth)
    swap(u, v);
  int diff = nodes_info[v].depth - nodes_info[u].depth;
  for (int i = 0; i <= MAX_POWERS_OF_TWO; ++i) {
    if ((diff >> i) & 1)
      v = nodes_info[v].parent_at[i];
  }
  if (u == v)
    return u;
  for (int i = MAX_POWERS_OF_TWO; i >= 0; --i) {
    if (nodes_info[u].parent_at[i] != nodes_info[v].parent_at[i]) {
      u = nodes_info[u].parent_at[i];
      v = nodes_info[v].parent_at[i];
    }
  }
  return nodes_info[u].parent_at[0];
}
void sanitizeBlock(int blk_id) {
  if (blocks[blk_id].dirty) {
    computeForBlock(blk_id);
    blocks[blk_id].dirty = false;
  }
}
int findMaxInBlocks(int l, int r) {
  int ret = 0;
  int blk_id, blk_l, blk_r;
  while (l <= r) {
    blk_id = getBlockNumber(l);
    blk_l = blocks[blk_id].blk_l;
    blk_r = blocks[blk_id].blk_r;
    sanitizeBlock(blk_id);
    if (l == blk_l && blk_r <= r) {
      ret = max(ret, blocks[blk_id].max_weight);
      l = blk_r + 1;
    } else {
      int t_r = min(blk_r, r);
      for (int i = l; i <= t_r; ++i)
        ret = max(ret, linear_chain_cost[i]);
      l = t_r + 1;
    }
  }
  return ret;
}
int findMaxInChains(int u, int v) { // u is lower than or on the same depth as v
  if (u == v) return 0;
  int uchain, vchain, ret;
  ret = 0;
  vchain = nodes_info[v].chain_info;
  while (1) {
    uchain = nodes_info[u].chain_info;
    if (uchain == vchain) {
      ret = max(ret, findMaxInBlocks(nodes_info[v].chain_pos + 1, nodes_info[u].chain_pos));
      break;
    }
    ret = max(ret, findMaxInBlocks(nodes_info[u].chain_head + 1, nodes_info[u].chain_pos));
    u = nodes_info[u].chain_head;
    u = nodes_info[u].parent_at[0];
  }
  return ret;
}
int findMaxinPath(int u, int v) {
  int lca = LCA(u, v);
  int ret = findMaxInChains(u, lca);
  ret = max(ret, findMaxInChains(v, lca));
  return ret;
}
void compressPaths() {
  int p;
  for (int h = 1; h <= MAX_POWERS_OF_TWO; ++h) {
    for (int i = 1; i <= n; ++i) {
      p = nodes_info[i].parent_at[i - 1];
      if (p)
        nodes_info[i].parent_at[i] = nodes_info[p].parent_at[i - 1];
    }
  }
}
void program() {
  int tcase, u, v, weight;
  char query[10];
  scanf("%d", &tcase);
  for (int t = 1; t <= tcase; ++t) {
    reset();
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
      scanf("%d %d %d", &u, &v, &weight);
      addToEdges(u, v, weight);
      nodes_info[u].edges.push_back(e_ptr);
      nodes_info[v].edges.push_back(e_ptr);
    }
    dfs(ROOT, 0, 0);
    hld(ROOT, ++chain_id, ROOT, 0, 0); // start a new chain starting from ROOT
    buildBlocks();
    compressPaths();
    while (1) {
      scanf(" %s", query);
      if (query[0] == 'D')
        break;
      else {
        scanf("%d %d", &u, &v);
        if (query[0] == 'C')
          change(u, v);
        else {
          int ret = findMaxinPath(u, v);
          printf("%d\n", ret);
        }
      }
    }
  }
}
int main() {
  program();
  return 0;
}