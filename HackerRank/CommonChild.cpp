// NA
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define ALPHA_CHARS_MAX 26
#define LEN_MAX 5000
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
char s1[BUFF(LEN_MAX)], s2[BUFF(LEN_MAX)];
int s1_len, s2_len;
struct C {
  int idx;
  bool type;
  char x;
} chars[BUFF(2 * LEN_MAX)];
int c_ptr;
int converted_s2[BUFF(LEN_MAX)];
int len_so_far[BUFF(LEN_MAX)];
int getIndexFromChar(char x) { return x - 'A' + 1; }
bool m_comparator(C a, C b) {
  if (a.idx != b.idx)
    return a.idx < b.idx;
  return a.type < b.type;
}
void insertIntoChars(int idx, bool type, char x) {
  ++c_ptr;
  chars[c_ptr].idx = idx;
  chars[c_ptr].type = type;
  chars[c_ptr].x = x;
}
void convertS2() {
  int l = 1, r, x = 0;
  while (l <= c_ptr) {
    if (chars[l].type) {
      while (l + 1 <= c_ptr && chars[l + 1].type)
        ++l;
      ++l;
    } else {
      r = l + 1;
      while (r <= c_ptr && !chars[r].type)
        ++r;
      if (chars[l].x == chars[r].x) {
        while (!chars[l].type && chars[r].type && chars[l].x == chars[r].x) {
          ++x;
          converted_s2[chars[r].idx] = x;
          ++l; ++r;
        }
      } else {
        l = r + 1;
        continue;
      }
    }
  }
}
int findMax(int l) {
  int cnt = 0;
  while (l <= LEN_MAX) {
    cnt = max(cnt, len_so_far[l]);
    ++l;
  }
  return cnt;
}
int compute() {
  int ans = 0;
  for (int i = s2_len - 1; i >= 0; --i) {
    if (!converted_s2[i]) continue;
    len_so_far[converted_s2[i]] = 1 + findMax(converted_s2[i] + 1);
    ans = max(ans, len_so_far[converted_s2[i]]);
  }
  return ans;
}
void program() {
  int x, cnt;
  scanf("%s %s", s1, s2);
  for (s1_len = 0; s1[s1_len]; ++s1_len) {
    x = getIndexFromChar(s1[s1_len]);
    insertIntoChars(s1_len, 0, s1[s1_len]);
  }
  for (s2_len = 0; s2[s2_len]; ++s2_len) {
    x = getIndexFromChar(s2[s2_len]);
    insertIntoChars(s2_len, 1, s2[s2_len]);
  }
  sort(chars + 1, chars + 1 + c_ptr, m_comparator);
  convertS2();
  printf("%d\n", compute());
}
int main() {
  program();
  return 0;
}