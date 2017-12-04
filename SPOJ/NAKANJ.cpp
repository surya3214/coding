//
#include <iostream>
#include <cstdio>
#define MAX_QUEUE 70
#define MOVES 8
#define SIZE 8
using namespace std;
char start[3], dest[3];
int sx, sy, dx, dy, ans, front, rear;
int movex[] = {-2, -2, 2, 2, -1, -1, 1, 1};
int movey[] = {-1, 1, -1, 1, -2, 2, -2, 2};
bool visited[SIZE][SIZE];
struct node {
  int x, y, moves;
} queue[MAX_QUEUE];
void reset() {
  ans = 0;
  front = rear = 0;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      visited[i][j] = false;
}
bool isEmpty() {
  if (front == rear)
    return true;
  return false;
}
void enqueue(int x, int y, int moves) {
  visited[x][y] = true;
  struct node *cur = &queue[rear];
  cur->x = x;
  cur->y = y;
  cur->moves = moves;
  rear++;
}
void dequeue() {
  front++;
}
bool isBoundedUnvisited(int x, int y) {
  if (x > 0 && x <= SIZE && y > 0 && y <= SIZE &&
      !visited[x][y])
      return true;
  return false;
}
void findMinMoves() {
  if (isBoundedUnvisited(sx, sy))
    enqueue(sx, sy, 0);
  struct node *cur;
  int nx, ny;
  while (!isEmpty()) {
    cur = &queue[front];
    dequeue();
    if (cur->x == dx && cur->y == dy) {
      ans = cur->moves;
      return;
    }
    // validate and insert all 8 moves
    for (int i = 0; i < MOVES; i++) {
      nx = cur->x + movex[i];
      ny = cur->y + movey[i];
      if (isBoundedUnvisited(nx, ny))
        enqueue(nx, ny, cur->moves + 1);
    }
  }
}
void program() {
  int t;
  scanf("%d", &t);
  while (t--) {
    reset();
    scanf("%s %s", start, dest);
    sy = start[0] - 'a' + 1;
    sx = start[1] - '0';
    dy = dest[0] - 'a' + 1;
    dx = dest[1] - '0';
    findMinMoves();
    printf("%d\n", ans);
  }
}
int main() {
  program();
  return 0;
}