template<class T>
struct seg_tree_01 {
   int N;
   vector<T> tree;
   vi len;
   seg_tree_01(int N) : N(N) {
      int tree_size = 1 << ((int) ceil(log2(N)) + 1);
      tree.resize(tree_size);
      len.resize(tree_size);
   }
   void update(int n, int nl, int nr, int l, int r, T v) {
      if (nr < l || nl > r) return;
      if (nl >= l && nr <= r) {
         tree[n] += v;
      }
      if (nl < nr) {
         int m = (nl + nr) >> 1;
         update(n * 2, nl, m, l, r, v);
         update(n * 2 + 1, m + 1, nr, l, r, v);
      }
      if (tree[n] > 0) len[n] = nr - nl + 1;
      else if (nl == nr) len[n] = 0;
      else len[n] = len[n * 2] + len[n * 2 + 1];
   }
   T query(int n, int nl, int nr, int l, int r) {
      if (nl > r || nr < l) return 0;
      if (nl >= l && nr <= r) return len[n];
      int m = (nl + nr) >> 1;
      return query(n * 2, nl, m, l, r) + query(n * 2 + 1, m + 1, nr, l, r);
   }
   T query(int l, int r) { return query(1, 0, N - 1, l, r); }
   void update(int l, int r, T v) { update(1, 0, N - 1, l, r, v); }
};