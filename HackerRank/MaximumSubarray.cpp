// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define NEG_INF -100000
using namespace std;
int n, subarray_sum, subsequence_sum;
int numbers[N_MAX];
void program() {
  int t, max_ending_here;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    subsequence_sum = NEG_INF;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &numbers[i]);
      if (subsequence_sum == NEG_INF)
        subsequence_sum = numbers[i];
       else if (subsequence_sum < 0) {
        if (numbers[i] >= 0)
          subsequence_sum = numbers[i];
        else subsequence_sum = max(subsequence_sum, numbers[i]);
      } else subsequence_sum = max(subsequence_sum, subsequence_sum + numbers[i]);
    }
    max_ending_here = 0;
    subarray_sum = numbers[1];
    for (int i = 1; i <= n; i++) {
      max_ending_here += numbers[i];
      subarray_sum = max(subarray_sum, max_ending_here);
      if (max_ending_here < 0)
        max_ending_here = 0;
    }
    printf("%d %d\n", subarray_sum, subsequence_sum);
  }
}
int main() {
  program();
  return 0;
}