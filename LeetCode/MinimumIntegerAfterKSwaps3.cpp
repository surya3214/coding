// AC #Hard, #BIT, #Implementation
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
const int DIGIT_MAX = 10;
const int LEN_MAX = 3e4;
void config() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
int BIT[BUFF(LEN_MAX)];
int _k, _n;
vector<int> digits[BUFF(DIGIT_MAX)];
class Solution {
  string ans;
  int getDigit(char x) { return x - '0'; }
  char getChar(int x) { return x + '0'; }
  void addToBIT(int x) {
    while (x) {
      ++BIT[x];
      x -= (x & -x);
    }
  }
  int queryBIT(int x) {
    int ret = 0;
    while (x <= _n) {
      ret += BIT[x];
      x += (x & -x);
    }
    return ret;
  }
  void process() {
    for (int i = 0, pos, cost; i < _n; ++i) {
      for (int d = 0; d < DIGIT_MAX; ++d) {
        if (digits[d].size()) {
          pos = digits[d][0];
          pos += queryBIT(pos);
          cost = pos - (i + 1);
          if (cost <= _k) {
            _k -= cost;
            ans += getChar(d);
            addToBIT(digits[d][0]);
            digits[d].erase(digits[d].begin());
            break;
          }
        }
      }
    }
  }
  void reset() {
    for (int i = 0; i < DIGIT_MAX; ++i)
      digits[i].clear();
    memset(BIT, 0, sizeof(BIT));
    ans.clear();
  }
public:
  string minInteger(string num, int k) {
    config();
    reset();
    _k = k;
    _n = num.size();
    for (int i = 0; i < num.size(); ++i)
      digits[getDigit(num[i])].push_back(i + 1);
    process();
    return ans;
  }
};
int main() {
  Solution ob;
  string a = "100";
  int b = 1;
  cout << ob.minInteger(a, b) << endl;
  return 0;
}