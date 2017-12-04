// AC
#include <iostream>
#include <cstdio>
#define K_MAX 1010
using namespace std;
int n, m, k;
long long int ans, tracks_occupancy;
struct {
  long long int r, c1, c2;
} tracks[K_MAX];
void swap(int i, int j) {
  if (i != j) {
    int tr, tc1, tc2;
    tr = tracks[i].r;
    tc1 = tracks[i].c1;
    tc2 = tracks[i].c2;
    tracks[i].r = tracks[j].r;
    tracks[i].c1 = tracks[j].c1;
    tracks[i].c2 = tracks[j].c2;
    tracks[j].r = tr;
    tracks[j].c1 = tc1;
    tracks[j].c2 = tc2;
  }  
}
int partition(int l, int r) {
  int pivot = r;
  int small_index = l;
  for (int i = l; i < r; i++) {
    if (tracks[i].r < tracks[pivot].r) {
      swap(i, small_index);
      small_index++;
    } else if (tracks[i].r == tracks[pivot].r) {
      if (tracks[i].c1 < tracks[pivot].c1) {
        swap(i, small_index);
        small_index++;
      } else if (tracks[i].c1 == tracks[pivot].c1) {
        if (tracks[i].c2 <= tracks[pivot].c2) {
          swap(i, small_index);
          small_index++;
        }
      }
    }
  }
  swap(small_index, pivot);
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
  // finds and returns the index where overlap ends
  int r = l;
  long long int c_end = tracks[l].c2;
  while (r <= k && tracks[l].r == tracks[r].r && tracks[r].c1 <= c_end) {
    c_end = max(c_end, tracks[r].c2);
    r++;
  }
  tracks_occupancy += c_end - tracks[l].c1 + 1;
  return r - 1;
}
void findTracksOccupancy() {
  for (int i = 1; i <= k; i++)
   i = next_index(i);
}
void program() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= k; i++)
    scanf("%lld %lld %lld", &tracks[i].r, &tracks[i].c1, &tracks[i].c2);
  quick_sort(1, k);
  // for (int i = 1; i <= k; i++)
  //   printf("%d %d %d\n", tracks[i].r, tracks[i].c1, tracks[i].c2);
  findTracksOccupancy();
  ans = (long long) n * m;
  ans -= tracks_occupancy;
  printf("%lld\n", ans);
}
int main() {
  program();
  return 0;
}