// NA
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
const int N_MAX = 3e4;
const int DIGIT_MAX = 10;
class Solution {
 public:
  string minInteger(string num, int k) {
    _k = k;
    _sz = num.size();
    for (int i = 0, d; i < _sz; ++i) {
      d = num[i] - '0';
      digits[d].push_back(i + 1);
    }
    construct();
    return ret;
  }

 private:
  void construct() {
    for (int pos = 1, cost, rep; pos <= _sz; ++pos) {
      for (int d = 0; d < DIGIT_MAX; ++d) {
        if (!digits[d].size())
          continue;
        rep = getCorrectPosition(digits[d][0]);
        cost = abs(rep - pos);
        if (cost <= _k) {
          ret.push_back(d + '0');
          _k -= cost;
          addToBIT(rep - 1);
          digits[d].erase(digits[d].begin());
          break;
        }
      }
    }
  }

  int queryBIT(int pos) {
    if (!pos)
      return 0;
    int ret = 0;
    while (pos <= _sz) {
      ret += _bit[pos];
      pos += (pos & -pos);
    }
    return ret;
  }

  int getCorrectPosition(int x) {
    return x + queryBIT(_sz) - queryBIT(x - 1);
  }

  void addToBIT(int pos) {
    while (pos > 0) {
      ++_bit[pos];
      pos -= (pos & -pos);
    }
  }

  string ret;
  int _bit[BUFF(N_MAX)];
  int _k, _sz;
  vector<int> digits[BUFF(DIGIT_MAX)];
};

int main() {
  Solution x;
  string num = "9438957234785635408";
  int k = 23;
  cout << x.minInteger(num, k) << endl;
  return 0;
}
