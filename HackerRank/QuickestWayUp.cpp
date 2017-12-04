// AC
#include <iostream>
#include <cstdio>
#define INF 1E9
#define N_MAX 110
#define BOUNDARY 100
#define MAX_SNACKS 17
#define MAX_LADDERS 17
using namespace std;
bool snakes_in[N_MAX];
bool ladders_in[N_MAX];
int dist[N_MAX];
int ladders_count, snakes_count, front, rear;
struct {
  int start, end;
} ladders[MAX_LADDERS], snakes[MAX_SNACKS];
struct node {
  int pos, moves;
} queue[N_MAX];
void enqueue(int pos, int moves) {
  if (pos <= BOUNDARY && dist[pos] > moves) {
    dist[pos] = moves;
    queue[rear].pos = pos;
    queue[rear].moves = moves;
    rear++;
  }
}
void dequeue() {
  front++;
}
bool isEmpty() {
  if (front == rear)
    return true;
  return false;
}
void reset() {
  front = rear = 0;
  for (int i = 0; i < N_MAX; i++)
    dist[i] = INF, snakes_in[i] = ladders_in[i] = false;
}
void bfs() {
  enqueue(1, 0);
  struct node *t;
  while (!isEmpty()) {
    t = &queue[front];
    dequeue();
    if (t->pos == BOUNDARY)
      return;
    if (snakes_in[t->pos]) {
      for (int i = 0; i < snakes_count; i++) {
        if (snakes[i].start == t->pos) {
          enqueue(snakes[i].end, t->moves);
          break;
        }
      }
    } else if (ladders_in[t->pos]) {
      for (int i = 0; i < ladders_count; i++) {
        if (ladders[i].start == t->pos) {
          enqueue(ladders[i].end, t->moves);
          break;
        }
      }
    } else {
      for (int i = 1; i <= 6; i++)
        enqueue(t->pos + i, t->moves + 1);
    }
  }
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    reset();
    scanf("%d", &ladders_count);
    for (int i = 0; i < ladders_count; i++) {
      scanf("%d %d", &ladders[i].start, &ladders[i].end);
      ladders_in[ladders[i].start] = true;
    }
    scanf("%d", &snakes_count);
    for (int i = 0; i < snakes_count; i++) {
      scanf("%d %d", &snakes[i].start, &snakes[i].end);
      snakes_in[snakes[i].start] = true;
    }
    bfs();
    if (dist[BOUNDARY] == INF)
      printf("-1\n");
    else printf("%d\n", dist[BOUNDARY]);
  }
}
int main() {
  program();
  return 0;
}