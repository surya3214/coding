// CF 887 B AC
#include <iostream>
#include <cstdio>
#define DIGITS 10
#define MAX_POSSIBLE 999
#define ALL_CUBES 7
#define NO_CUBES 0
using namespace std;
int seen_in[DIGITS];
bool makeUsingCubes(int n, int in_cubes) {
  // sees if n can be made using cubes encode-marked in in_cubes
  if (n < 10)
    return seen_in[n] & in_cubes;
  else {
    int digit;
    for (int i = 1; i <= ALL_CUBES; i = i << 1) {
      // i will have 001, 010, 100 values
      digit = n % 10;
      if ((in_cubes & i) && (seen_in[digit] & i)) {
        // digit is found in ith cube; find the rest in other cubes
        if (makeUsingCubes(n / 10, in_cubes ^ i))
          return true;
      }
    }
  }
  return false;
}
int findMaxNatural() {
  for (int i = 1; i <= MAX_POSSIBLE; i++)
    if (!makeUsingCubes(i, ALL_CUBES))
      return i - 1;
  return MAX_POSSIBLE;
}
void program() {
  int n, digit;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
      scanf("%d", &digit);
      seen_in[digit] = seen_in[digit] | 1 << i;
    }
  }
  printf("%d\n", findMaxNatural());
}
int main() {
  program();
  return 0;
}