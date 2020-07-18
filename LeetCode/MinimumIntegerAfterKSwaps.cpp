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
void configure() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
class Solution {
public:
  string minInteger(string num, int k) {
    configure();
    _k = k;
    process(num);
    return ret;
  }
private:
  int getDigit(char x) { return x - '0'; }
  char getChar(int x) { return x + '0'; }
  int getActualPosition(int idx) { return idx + offset[idx]; }
  void addOffset(int l, int r) {
    for (int i = l; i <= r; ++i)
      ++offset[i];
  }
  void process(string s) {
    for (int i = 0, x; i < s.size(); ++i) {
      x = getDigit(s[i]);
      digits[x].push(i);
    }
    for (int pos = 0, p, cost; pos < s.size(); ++pos) {
      for (int j = 0; j < DIGIT_MAX; ++j) {
        if (!digits[j].size())
          continue;
        p = getActualPosition(digits[j].front());
        cost = abs(p - pos);
        if (cost <= _k) {
          _k -= cost;
          ret.push_back(getChar(j));
          addOffset(0, p - 1);
          digits[j].pop();
          break;
        }
      }
    }
  }
  int _k;
  queue<int> digits[BUFF(DIGIT_MAX)];
  string ret;
  int offset[BUFF(N_MAX)] = { 0 };
};
int main() {
  Solution x;
  string num = "9876"; // "9438957234785635408";
  int k = 5; // 23;
  cout << x.minInteger(num, k) << endl;
  return 0;
}
