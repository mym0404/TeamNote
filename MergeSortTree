template<class T>
struct merge_sort {
   int size;
   vector<vector<T>> tree;

   merge_sort(int n) {
      size = 1 << int(ceil(log2(n)) + 1);
      tree.resize(size);
   }
   void add(int i, T v) {
      tree[i + size / 2].pb(v);
   }
   void build() {
      for (int i = size / 2 - 1; i >= 1; i--) {
         auto &c = tree[i], &l = tree[i * 2], &r = tree[i * 2 + 1];
         c.resize(sz(l) + sz(r));
         for (int p = 0, a = 0, b = 0; p < sz(c); p++) {
            if (b == sz(r) || (a < sz(l) && l[a] < r[b])) c[p] = l[a++];
            else c[p] = r[b++];
         }
      }
   }
   T query(int n, int nl, int nr, int l, int r, int k) {
      if (nl > r || nr < l) return 0;
      if (nl >= l && nr <= r) return ubi(tree[n], k);
      return query(n * 2, nl, (nl + nr) / 2, l, r, k) + query(n * 2 + 1, (nl + nr) / 2 + 1, nr, l, r, k);
   }
   T query(int l, int r, int k) {
      return query(1, 0, size / 2 - 1, l, r, k);
   }
};
