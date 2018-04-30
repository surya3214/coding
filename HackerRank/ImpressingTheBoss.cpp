// AC
#define BUFFER 5
#define BUFF(x) x + BUFFER
#define N_MAX 20
int sales[BUFF(N_MAX)];
int n;
bool isPossible(int pos, int last, bool taken) {
  if (pos == n)
    return true;
  bool ret = false;
  if (!taken)
    ret = ret || isPossible(pos + 1, last, true);
  if (sales[pos] >= last)
    ret = ret || isPossible(pos + 1, sales[pos], taken);
  return ret;
}
string canModify(vector<int> a) {
  n = 0;
  for (vector<int>::iterator it = a.begin(); it != a.end(); it++)
    sales[n++] = *it;
  if (isPossible(0, 0, false))
    return "YES";
  return "NO";
}