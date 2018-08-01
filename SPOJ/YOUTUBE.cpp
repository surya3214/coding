//
#include <bits/stdc++.h>
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 100000
#define K_MAX 100000
using namespace std;
typedef long long int ll;
int n, m, clips;
int starts_at[BUFF(N_MAX)];
int next_clip[BUFF(K_MAX)];
bool visited[BUFF(K_MAX)];
struct {
  struct N *front;
  int length;
} loops[BUFF(K_MAX)];
int clips_ptr[BUFF(K_MAX)];
void process(int i) {
  if (visited[i]) return;
}
void program() {
  scanf("%d %d %d", &n, &clips, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &starts_at[i]);
  for (int i = 1; i <= clips; ++i)
    scanf("%d", &next_clip[i]);
  for (int i = 1; i <= clips; ++i)
    process(i);
  --m;
  for (int i = 1; i <= n; ++i)
    printf("%d ", findMth(starts_at[i]));
}
int main() {
  program();
  return 0;
}