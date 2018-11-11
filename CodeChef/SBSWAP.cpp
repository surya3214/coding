// AC Link Cut, Square Root Decomposition Ayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy!
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX (int) 1e5
#define BLOCKS_MAX 317
#pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
int n;
struct {
  ll pref_sum;
  int nodes_cnt;
} range_info[BUFF(N_MAX * 2)];
struct {
  int start;
  int end;
  ll weight;
  vector<int> edges;
  bool visited;
} nodes_info[BUFF(N_MAX)];
int linearized_tree[2][BUFF(N_MAX * 2)];
bool cur;
int l_ptr;
ll getPrefixSum(int s, int e) {
  return range_info[e].pref_sum - range_info[s - 1].pref_sum;
}
int getNodesCount(int s, int e) {
  return range_info[e].nodes_cnt - range_info[s - 1].nodes_cnt;
}
struct Segment {
  int s, e;
  ll extra;
  Segment() {}
  Segment(int t_s, int t_e, ll t_extra) : s(t_s), e(t_e), extra(t_extra) {}
  ll getSum() {
    return getPrefixSum(s, e) + (extra * getNodesCount(s, e));
  }
};
vector<Segment> m_seg;
void linearize_tree(int u) {
  if (nodes_info[u].visited)
    return;
  nodes_info[u].visited = true;
  ++l_ptr;
  linearized_tree[cur][l_ptr] = u;
  nodes_info[u].start = l_ptr;
  range_info[l_ptr].pref_sum = nodes_info[u].weight;
  range_info[l_ptr].nodes_cnt = 1;
  for (int i = 0; i < nodes_info[u].edges.size(); ++i)
    linearize_tree(nodes_info[u].edges[i]);
  ++l_ptr;
  linearized_tree[cur][l_ptr] = u;
  nodes_info[u].end = l_ptr;
}
void isolate_start(int idx) {
  for (int i = 0; i < m_seg.size(); ++i) {
    if (m_seg[i].s == idx)
      return;
    else if (idx > m_seg[i].s && idx <= m_seg[i].e) {
      int tmp = m_seg[i].e;
      m_seg[i].e = idx - 1;
      m_seg.insert(m_seg.begin() + i + 1, Segment(idx, tmp, m_seg[i].extra));
      return;
    }
  }
}
void isolate_end(int idx) {
  for (int i = 0; i < m_seg.size(); ++i) {
    if (m_seg[i].e == idx)
      return;
    else if (idx >= m_seg[i].s && idx < m_seg[i].e) {
      int tmp = m_seg[i].e;
      m_seg[i].e = idx;
      m_seg.insert(m_seg.begin() + i + 1, Segment(idx + 1, tmp, m_seg[i].extra));
      return;
    }
  }
}
void isolate(int u) {
  isolate_start(nodes_info[u].start);
  isolate_end(nodes_info[u].end);
}
void locate(int u, int& s, int& e) {
  for (int i = 0; i < m_seg.size(); ++i) {
    if (m_seg[i].s == nodes_info[u].start)
      s = i;
    if (m_seg[i].e == nodes_info[u].end) {
      e = i;
      return;
    }
  }
}
void populateRangeInfo() {
  for (int i = 1; i <= (2 * n); ++i) {
    range_info[i].pref_sum += range_info[i - 1].pref_sum;
    range_info[i].nodes_cnt += range_info[i - 1].nodes_cnt;
  }
}
void rebuild() {
  bool prev = cur;
  cur = !cur;
  for (int i = 1; i <= (2 * n); ++i)
    linearized_tree[cur][i] = range_info[i].nodes_cnt = range_info[i].pref_sum = 0;
  for (int u = 1; u <= n; ++u)
    nodes_info[u].visited = false;
  l_ptr = 0;
  int u;
  for (int i = 0; i < m_seg.size(); ++i) {
    for (int j = m_seg[i].s; j <= m_seg[i].e; ++j) {
      u = linearized_tree[prev][j];
      ++l_ptr;
      if (!nodes_info[u].visited) {
        nodes_info[u].visited = true;
        linearized_tree[cur][l_ptr] = u;
        nodes_info[u].start = l_ptr;
        nodes_info[u].weight += m_seg[i].extra;
        range_info[l_ptr].pref_sum = nodes_info[u].weight;
        range_info[l_ptr].nodes_cnt = 1;
      } else {
        linearized_tree[cur][l_ptr] = u;
        nodes_info[u].end = l_ptr;
      }
    }
  }
  populateRangeInfo();
  m_seg.clear();
  m_seg.push_back(Segment(nodes_info[1].start, nodes_info[1].end, 0));
}
Segment buffer[BUFF(N_MAX * 2)];
int b_ptr;
void program() {
  int q, u, v;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &nodes_info[i].weight);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    nodes_info[u].edges.push_back(v);
    nodes_info[v].edges.push_back(u);
  }
  linearize_tree(1);
  populateRangeInfo();
  m_seg.push_back(Segment(nodes_info[1].start, nodes_info[1].end, 0));
  int type, x;
  struct {
    int s, e; // indices on m_seg
  } u_info, v_info;
  ll ret;
  for (int i = 1; i <= q; ++i) {
    if (m_seg.size() >= BLOCKS_MAX)
      rebuild();
    scanf("%d", &type);
    scanf("%d", &u);
    isolate(u);
    switch (type) {
      case 1:
        locate(u, u_info.s, u_info.e);
        ret = 0;
        for (int i = u_info.s; i <= u_info.e; ++i)
          ret += m_seg[i].getSum();
        printf("%lld\n", ret);
        break;
      case 2:
        scanf("%d", &x);
        locate(u, u_info.s, u_info.e);
        for (int i = u_info.s; i <= u_info.e; ++i)
          m_seg[i].extra += x;
        break;
      case 3:
        scanf("%d", &v);
        isolate(v);
        locate(u, u_info.s, u_info.e);
        locate(v, v_info.s, v_info.e);
        if (v_info.s < u_info.s) {
          swap(v_info.s, u_info.s);
          swap(v_info.e, u_info.e);
        }
        if (v_info.s <= u_info.e)
          printf("-1\n");
        else {
          b_ptr = 0;
          for (int i = 0; i <= u_info.s - 1; ++i)
            buffer[b_ptr++] = m_seg[i];
          for (int i = v_info.s; i <= v_info.e; ++i)
            buffer[b_ptr++] = m_seg[i];
          for (int i = u_info.e + 1; i <= v_info.s - 1; ++i)
            buffer[b_ptr++] = m_seg[i];
          for (int i = u_info.s; i <= u_info.e; ++i)
            buffer[b_ptr++] = m_seg[i];
          for (int i = v_info.e + 1; i < m_seg.size(); ++i)
            buffer[b_ptr++] = m_seg[i];
          for (int i = 0; i < b_ptr; ++i)
            m_seg[i] = buffer[i];
        }
        break;
    }
  }
}
int main() {
  program();
  return 0;
}