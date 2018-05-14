struct {
  int t1, t2;
  int e1, e2;
  int buff1[BUFF(FILL)], buff2[BUFF(FILL)];
} buffer;
int getMid(int l, int r) { return l + (r - l) / 2; }
void copyToBuffer(int &s1, int &e1, int &s2, int &e2) {
  buffer.e1 = buffer.e2 = 0;
  for (int i = s1; i <= e1; i++)
    buffer.buff1[buffer.e1++] = FILL[i];
  for (int i = s2; i <= e2; i++)
    buffer.buff2[buffer.e2++] = FILL[i];
}
void fillArrayFromBuffer(int &ptr) {
  buffer.t1 = buffer.t2 = 0;
  while (buffer.t1 < buffer.e1 && buffer.t2 < buffer.e2) {
    if (buffer.buff1[buffer.t1] <= buffer.buff2[buffer.t2])
      FILL[ptr++] = buffer.buff1[buffer.t1++];
    else FILL[ptr++] = buffer.buff2[buffer.t2++];
  }
  while (buffer.t1 < buffer.e1)
    FILL[ptr++] = buffer.buff1[buffer.t1++];
  while (buffer.t2 < buffer.e2)
    FILL[ptr++] = buffer.buff2[buffer.t2++];
}
void merge(int s1, int e1, int e2) {
  int s2 = e1 + 1;
  copyToBuffer(s1, e1, s2, e2);
  fillArrayFromBuffer(s1);
}
void merge_sort(int l, int r) {
  if (l < r) {
    int mid = getMid(l, r);
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
  }
}