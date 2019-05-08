// AC Easy
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define TO 31
#define PAST 32
#define CLOCK 33
#define MIN 34
#define MINS 35
// #pragma GCC optimize "O4"
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
void printNumber(int x) {
  switch (x) {
    case 1: printf("one "); break;
    case 2: printf("two "); break;
    case 3: printf("three "); break;
    case 4: printf("four "); break;
    case 5: printf("five "); break;
    case 6: printf("six "); break;
    case 7: printf("seven "); break;
    case 8: printf("eight "); break;
    case 9: printf("nine "); break;
    case 10: printf("ten "); break;
    case 11: printf("eleven "); break;
    case 12: printf("twelve "); break;
    case 13: printf("thirteen "); break;
    case 14: printf("fourteen "); break;
    case 15: printf("quarter "); break;
    case 16: printf("sixteen "); break;
    case 17: printf("seventeen "); break;
    case 18: printf("eighteen "); break;
    case 19: printf("nineteen "); break;
    case 20: printf("twenty "); break;
    case 21: printf("twenty one "); break;
    case 22: printf("twenty two "); break;
    case 23: printf("twenty three "); break;
    case 24: printf("twenty four "); break;
    case 25: printf("twenty five "); break;
    case 26: printf("twenty six "); break;
    case 27: printf("twenty seven "); break;
    case 28: printf("twenty eight "); break;
    case 29: printf("twenty nine "); break;
    case 30: printf("half "); break;
    case TO: printf("to "); break;
    case PAST: printf("past "); break;
    case CLOCK: printf("o' clock "); break;
    case MIN: printf("minute "); break;
    case MINS: printf("minutes "); break;
  }
}
void program() {
  int h, m;
  scanf("%d %d", &h, &m);
  if (!m) {
    printNumber(h);
    printNumber(CLOCK);
  } else {
    if (m <= 30) {
      printNumber(m);
      if (m == 1)
        printNumber(MIN);
      else if (m != 15 && m != 30)
        printNumber(MINS);
      printNumber(PAST);
      printNumber(h);
    } else {
      m = 60 - m;
      ++h;
      if (h > 12)
        h -= 12;
      printNumber(m);
      if (m == 1)
        printNumber(MIN);
      else if (m != 15)
        printNumber(MINS);
      printNumber(TO);
      printNumber(h);
    }
  }
}
int main() {
  program();
  return 0;
}