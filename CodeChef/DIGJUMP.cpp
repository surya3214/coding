// AC
#include <iostream>
#include <cstdio>
#define N_MAX 100010
#define DIGITS 10
using namespace std;
int indices[DIGITS][N_MAX];
char str[N_MAX];
int ans, front, rear, dest;
bool visited[N_MAX];
bool visited_digit[DIGITS];
struct node {
  int index;
  int hops;
} queue[N_MAX];
void enqueue(int index, int hops) {
  struct node *cur = &queue[rear];
  visited[index] = true;
  cur->index = index;
  cur->hops = hops;
  rear++;
}
void dequeue() {
  front++;
}
bool isEmpty() {
  if (front == rear)
    return true;
  return false;
}
void bfs(int u) {
  enqueue(u, 0);
  struct node *cur;
  int digit, pos;
  while (!isEmpty()) {
    cur = &queue[front];
    dequeue();
    if (cur->index == dest) {
      ans = cur->hops;
      return;
    }
    if (cur->index >= 1 && !visited[cur->index - 1])
      enqueue(cur->index - 1, cur->hops + 1);
    if (cur->index < dest && !visited[cur->index + 1])
      enqueue(cur->index + 1, cur->hops + 1);
    digit = str[cur->index] - '0';
    if (!visited_digit[digit]) {
      for (int i = 1; i <= indices[digit][0]; i++) {
        pos = indices[digit][i];
        if (!visited[pos])
          enqueue(pos, cur->hops + 1);
      }
      visited_digit[digit] = true;
    }
  }
}
void reset() {
  front = rear = 0;
}
void program() {
  scanf("%s", str);
  int digit, pos;
  reset();
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    digit = str[i] - '0';
    pos = ++indices[digit][0];
    indices[digit][pos] = i;
  }
  dest = i - 1;
  bfs(0);
  printf("%d\n", ans);
}
int main() {
  program();
  return 0;
}