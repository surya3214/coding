// AC
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define mp make_pair
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
vector<pair<int, vector<int>>> dig_cnt;
void prepare() {
  for (unsigned int b = 0, sq = 0; sq <= INT_MAX; ++b, sq = b * b) {
    vector<int> dgts(10);
    bool first = true;
    while (first || sq) {
      ++dgts[sq % 10];
      sq /= 10;
      first = false;
    }
    dig_cnt.push_back(make_pair(b * b, dgts));
  }
}
class CountDig
{
public:
  static int nbDig(int n, int d) {
    static bool prepared = false;
    if (!prepared) {
      prepare();
      prepared = true;
    }
    int ret = 0;
    unsigned int last = n;
    last *= last;
    for (auto x: dig_cnt) {
      if ((unsigned int) x.first > last)
        break;
      ret += x.second[d];
    }
    return ret;
  }
};
void program() {
  cout << CountDig::nbDig(10, 1) << endl;
  cout << CountDig::nbDig(25, 1) << endl;
  cout << CountDig::nbDig(5750, 0) << endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  program();
  return 0;
}
