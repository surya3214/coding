//
#include <iostream>
#include <cstdio>
#define N_MAX 2010
#define NONE -1
#define BLUE 1
#define RED 0
using namespace std;
int t, bugs, interactions;
int assigned[N_MAX];
void reset() {
  for (int i = 0; i <= bugs; i++)
    assigned[i] = NONE;
}
bool assign(int u, int v) {
  if (assigned[u] == NONE && assigned[v] == NONE) {
    assigned[u] = BLUE;
    assigned[v] = RED;
    return true;
  } else if (assigned[u] == NONE) {
    assigned[u] = !assigned[v];
    return true;
  } else if (assigned[v] == NONE) {
    assigned[v] = !assigned[u];
    return true;
  } else if (assigned[u] == assigned[v])
    return false;
    else if (assigned[u] != assigned[v])
    return true;
}
void program() {
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    int u, v;
    bool valid = true;
    scanf("%d %d", &bugs, &interactions);
    reset();
    for (int i = 0; i < interactions; i++) {
      scanf("%d %d", &u, &v);
      if (!assign(u, v))
        valid = false;
    }
    printf("Scenario #%d:\n", i);
    if (valid)
      printf("No suspicious bugs found!\n");
    else printf("Suspicious bugs found!\n");
  }
}
int main() {
  program();
  return 0;
}