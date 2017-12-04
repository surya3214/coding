// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
using namespace std;
int n, k, ans;
int houses[N_MAX];
void swap(int i, int j) {
  if (i != j) {
    int temp = houses[i];
    houses[i] = houses[j];
    houses[j] = temp;
  }
}
int partition(int l, int r) {
  int pivot = houses[r];
  int small_index = l;
  for (int i = l; i < r; i++) {
    if (houses[i] <= pivot) {
      swap(small_index, i);
      small_index++;
    }
  }
  swap(small_index, r);
  return small_index;
}
void quick_sort(int l, int r) {
  if (l < r) {
    int pivot = partition(l, r);
    quick_sort(l, pivot - 1);
    quick_sort(pivot + 1, r);
  }
}
int next_index(int l) {
  int house_transmission_in = houses[l] + k;
  int i = l + 1;
  while (i <= n && houses[i] <= house_transmission_in)
    i++;
  int house_transmission_until = houses[i - 1] + k;
  while (i <= n && houses[i] <= house_transmission_until)
    i++;
  return i - 1;
}
void compute() {
  for (int i = 1; i <= n; i++) {
    // this index doesn't have coverage yet
    ans++;
    i = next_index(i);
  }
}
void program() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", &houses[i]);
  quick_sort(1, n);
  compute();
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}