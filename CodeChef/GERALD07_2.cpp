// New Ryan
// Create @ 18:14 03-10 2014
// Comment - 

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include <queue>
#include <map>
#include <set>

using namespace std;

// Self Template Code BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define all(x) (x).begin(), (x).end()
#define clz(x) memset (x, 0, sizeof(x))
#define read(x) freopen (x, "r", stdin)
#define wrte(x) freopen (x, "w", stdout)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pll;
typedef pair<double, double> pdd;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

const int MAXN = 200000 + 10;

struct edge_node {
	int u, v;

	void input() {
		scanf ("%d%d", &u, &v);
		--u, --v;
	}
};

struct query_node {
	int l, r;
	int block_id, id;

	static int block_size;

	static void set_block_size(int bsize) {
		block_size = bsize;
	}

	void input(int _id) {
		id = _id;
		scanf ("%d%d", &l, &r);
		--l; --r;
		block_id = l / block_size;
	}

	bool operator<(const query_node& rhs) const {
		return block_id == rhs.block_id? r < rhs.r : block_id < rhs.block_id;
	}
};

int query_node::block_size = -1;

struct disjoint_set {
	int p[MAXN], n_com;

	int get_com_num() {
		return n_com;
	}

	void clear(int n) {
		n_com = n;
		rep (i, n) {
			p[i] = i;
		}
	}

	int find(int x) {
		return x == p[x]? x : p[x] = find(p[x]);
	}

	bool join(int x, int y) {
//		printf (" ds join %d %d\n", x, y);
		x = find(x); y = find(y);
		if (x != y) {
			p[x] = y;
			n_com -= 1;
		}
	}

	bool join(const edge_node& enode) {
		return join(enode.u, enode.v);
	}
};

struct shadow_disjoint_set {
	int p[MAXN], tms[MAXN], cur_tms;
	disjoint_set* shadow_ds;

	shadow_disjoint_set(disjoint_set* ds) {
		shadow_ds = ds;
	}

	void set_cur_tms(int _ct) {
		cur_tms = _ct;
	}

	void clear() {
		memset (tms, -1, sizeof(tms));
	}

	int find(int x) {
		if (tms[x] != cur_tms) {
			tms[x] = cur_tms;
			p[x] = shadow_ds->p[x];
		}
		return x == p[x]? x : p[x] = find(p[x]);
	}

	bool join(int x, int y) {
//		printf ("sds join %d %d ", x, y);
		x = find(x); y = find(y);
		if (x != y) {
			p[x] = y;
			return true;
		}
		return false;
	}

	bool join(const edge_node& enode) {
		return join(enode.u, enode.v);
	}
};

edge_node edge[MAXN];
query_node query[MAXN];

disjoint_set ds;
shadow_disjoint_set sds(&ds);

int n, m, q, ans[MAXN];
int block_size, pre_bID, cur_end;

int answer_query(int l, int r, int bID) {
//	printf ("query %d %d %d\n", l, r, bID);
	if (bID != pre_bID) {
		pre_bID = bID;
		cur_end = (bID + 1) * block_size;
		ds.clear(n); 
	}

	for (; cur_end <= r; ++cur_end) {
		ds.join(edge[cur_end]);
	}

	int res = ds.get_com_num();
	int r_lim = min((bID + 1) * block_size - 1, r);
	repf (i, l, r_lim) {
		res -= sds.join(edge[i]);
	}
	return res;
}

void init() {
	scanf ("%d%d%d", &n, &m, &q);

	rep (i, m) {
		edge[i].input();
	}

	block_size = (int)sqrt(1.0 * m);
	query_node::set_block_size(block_size);

	rep (i, q) {
		query[i].input(i);
	}
}

void solve() {
	sort (query, query + q);

	sds.clear();
	pre_bID = cur_end = -1;
	rep (i, q) {
		sds.set_cur_tms(i);
		ans[query[i].id] = answer_query(query[i].l, query[i].r, query[i].block_id);
	}
	rep (i, q) {
		printf ("%d\n", ans[i]);
	}
}

int main() {
	repcase {
		init(); solve();
	}
	return 0;
}