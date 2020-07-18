// AC #Medium
#include <bits/stdc++.h>
using namespace std;
struct N {
  N() { deps = added = 0; next.clear(); }
  int deps;
  vector<int> next;
  bool added;
};
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    N courses[numCourses];
    for (auto cur: prerequisites) {
      // cur[0] only after cur[1]
      ++courses[cur[0]].deps;
      courses[cur[1]].next.push_back(cur[0]);
    }
    queue<int> q;
    vector<int> ret;
    for (int i = 0; i < numCourses; ++i) {
      if (!courses[i].deps && !courses[i].added) {
        ret.push_back(i);
        q.push(i);
        courses[i].added = true;
      }
    }
    while (!q.empty()) {
      int t = q.front();
      for (auto nxt: courses[t].next) {
        --courses[nxt].deps;
        if (!courses[nxt].deps && !courses[nxt].added) {
          ret.push_back(nxt);
          q.push(nxt);
          courses[nxt].added = true;
        }
      }
      q.pop();
    }
    if (ret.size() != numCourses)
      ret.clear();
    return ret;
  }
};