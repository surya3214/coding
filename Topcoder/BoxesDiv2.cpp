// SRM 622 Div2
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
class BoxesDiv2 {
public:
  int findSize(vector<int> candyCounts) {
    while (candyCounts.size() > 1) {
      sort(candyCounts.begin(), candyCounts.end());
      int size = 1;
      while (size < candyCounts[1])
        size = size * 2; // size corresponds to only one box; candyCounts[1]
      candyCounts.erase(candyCounts.begin());
      candyCounts.erase(candyCounts.begin());
      candyCounts.push_back(size * 2);
    }
    int size = 1;
    while (size < candyCounts[0])
      size *= 2;
    return size;
  }
};
void program() {
}
int main() {
  program();
  return 0;
}