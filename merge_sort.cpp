struct {
  int t1, t2;
  int e1, e2;
  int buff1[BUFF(FILL)], buff2[BUFF(FILL)];
} m_buffer;
int getMid(int l, int r) { return l + (r - l) / 2; }
void copyToBuffer(int &s1, int &e1, int &s2, int &e2) {
  m_buffer.e1 = m_buffer.e2 = 0;
  for (int i = s1; i <= e1; i++)
    m_buffer.buff1[m_buffer.e1++] = FILL[i];
  for (int i = s2; i <= e2; i++)
    m_buffer.buff2[m_buffer.e2++] = FILL[i];
}
void fillArrayFromBuffer(int &ptr) {
  m_buffer.t1 = m_buffer.t2 = 0;
  while (m_buffer.t1 < m_buffer.e1 && m_buffer.t2 < m_buffer.e2) {
    if (m_buffer.buff1[m_buffer.t1] <= m_buffer.buff2[m_buffer.t2])
      FILL[ptr++] = m_buffer.buff1[m_buffer.t1++];
    else FILL[ptr++] = m_buffer.buff2[m_buffer.t2++];
  }
  while (m_buffer.t1 < m_buffer.e1)
    FILL[ptr++] = m_buffer.buff1[m_buffer.t1++];
  while (m_buffer.t2 < m_buffer.e2)
    FILL[ptr++] = m_buffer.buff2[m_buffer.t2++];
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