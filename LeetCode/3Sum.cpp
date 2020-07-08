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
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> ret;
    for (int i = nums.size() - 2, sum; i >= 0; --i) {
      // query map for pairs
      for (auto it: pairs[-nums[i]]) {
        vector<int> now = { nums[i], it.first, it.second };
        sort(now.begin(), now.end());
        if (!added[mp(now[0], now[1])]) {
          ret.push_back(now);
          added[mp(now[0], now[1])] = true;
        }
      }
      // construct pairs
      for (int j = i + 1; j <= nums.size() - 1; ++j) {
        sum = nums[i] + nums[j];
        pairs[sum].insert(mp(min(nums[i], nums[j]), max(nums[i], nums[j])));
      }
    }
    return ret;
  }

 private:
  map<pii, bool> added;
  unordered_map<int, set<pii>> pairs;
};