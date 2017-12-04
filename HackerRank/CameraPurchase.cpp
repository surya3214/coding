//
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define MAX_BRANDS 5
#define MAX_COMBINATIONS 32
using namespace std;
int price[N_MAX], brands[N_MAX];
int n, q;
struct node {
  int count;
  int sorted[N_MAX];
} cameras_sorted[MAX_COMBINATIONS];
void insert(int comb, int price) {
  int *cnt = &cameras_sorted[comb].count;
  cameras_sorted[comb].sorted[*cnt] = price;
  (*cnt)++;
}
void swap(int comb, int i, int j) {
  if (i != j) {
    int tmp = cameras_sorted[comb].sorted[i];
    cameras_sorted[comb].sorted[i] = cameras_sorted[comb].sorted[j];
    cameras_sorted[comb].sorted[j] = tmp;
  }
}
int partition(int comb, int l, int r) {
  int pivot = cameras_sorted[comb].sorted[r];
  int small_index = l;
  for (int i = l; i < r; i++) {
    if (cameras_sorted[comb].sorted[i] <= pivot) {
      swap(comb, i, small_index);
      small_index++;
    }
  }
  swap(comb, small_index, r);
  return small_index;
}
void quick_sort(int comb, int l, int r) {
  if (l < r) {
    int pivot = partition(comb, l, r);
    quick_sort(comb, l, pivot - 1);
    quick_sort(comb, pivot + 1, r);
  }
}
void merge_sort(int comb_1, int comb_2) {
  int res_comb = comb_1 | comb_2;
  if (res_comb < MAX_COMBINATIONS) {
    cameras_sorted[res_comb].count = cameras_sorted[comb_1].count + cameras_sorted[comb_2].count;
    // comb1 and comb2 are already sorted
    int pt_1 = 0, pt_2 = 0, pt_3 = 0;
    while (pt_1 < cameras_sorted[comb_1].count && pt_2 < cameras_sorted[comb_2].count) {
      if (cameras_sorted[comb_1].sorted[pt_1] <= cameras_sorted[comb_2].sorted[pt_2])
        cameras_sorted[res_comb].sorted[pt_3++] = cameras_sorted[comb_1].sorted[pt_1++]; // add from comb_1 to comb_3
      else cameras_sorted[res_comb].sorted[pt_3++] = cameras_sorted[comb_2].sorted[pt_2++]; // add from comb_2 to res_comb
    }
    while (pt_1 < cameras_sorted[comb_1].count)
      cameras_sorted[res_comb].sorted[pt_3++] = cameras_sorted[comb_1].sorted[pt_1++];
    while (pt_2 < cameras_sorted[comb_2].count)
      cameras_sorted[res_comb].sorted[pt_3++] = cameras_sorted[comb_2].sorted[pt_2++];
  }
}
void combine(int total_set_bits_required, int set_bits_so_far, int comb, int idx) {
  if (idx > MAX_BRANDS || set_bits_so_far >= total_set_bits_required)
    return;
  // either you set this idx or not
  combine(total_set_bits_required, set_bits_so_far, comb, idx + 1); // don't set
  if (total_set_bits_required - set_bits_so_far == 1) {
    // this is the last required brand
    merge_sort(comb, (1 << idx));
  } else combine(total_set_bits_required, set_bits_so_far + 1, comb | (1 << idx), idx + 1);
}
void build() {
  // sorts all cameras belonging to one brand
  for (int i = 0; i < MAX_BRANDS; i++)
    quick_sort(1 << i, 0, cameras_sorted[1 << i].count - 1);
  // needs sorting in all permutations now
  for (int set_bits = 2; set_bits <= MAX_BRANDS; set_bits++)
    combine(set_bits, 0, 0, 0);
}
void program() {
  int choices, tmp, tmp2, cust_k;
  scanf("%d", &n);
  for (int i = 0; i < MAX_COMBINATIONS; i++)
    cameras_sorted[i].count = 0;
  for (int i = 0; i < n; i++)
    scanf("%d", &brands[i]);
  for (int i = 0; i < n; i++) {
    scanf("%d", &price[i]);
    insert(1 << (brands[i] - 1), price[i]);
  }
  build();
  scanf("%d", &q);
  while (q--) {
    scanf("%d", &tmp);
    choices = 0;
    while (tmp--) {
      scanf("%d", &tmp2);
      choices = choices | (1 << (tmp2 - 1));
    }
    scanf("%d", &cust_k);
    if (cameras_sorted[choices].count >= cust_k)
      printf("%d\n", cameras_sorted[choices].sorted[cust_k - 1]);
    else printf("-1\n");
  }
}
int main() {
  // freopen("CameraPurchase_input.txt", "r", stdin);
  program();
  return 0;
}