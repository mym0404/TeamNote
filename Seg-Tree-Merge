template<class T>
struct seg_tree_merge {
   int N;
   struct node { T all, ml, mr, mx; };
   const T INF = numeric_limits<T>::max() >> 1;
   vector<node> tree;
   seg_tree_merge(int N) : N(N) {
      int tree_size = 1 << ((int) ceil(log2(N)) + 1);
      tree.resize(tree_size);
   }
   node merge(node l, node r) {
      node ret;
      ret.all = l.all + r.all;
      ret.ml = max(l.ml, l.all + r.ml);
      ret.mr = max(r.mr, r.all + l.mr);
      ret.mx = max({l.mx, r.mx, l.mr + r.ml});
      return ret;
   }
   void update(int n, int nl, int nr, int i, T v) {
      if (nl > i || nr < i) return;
      if (nl == nr) {
         tree[n] = {v, v, v, v};
         return;
      }
      int m = (nl + nr) >> 1;
      update(n * 2, nl, m, i, v);
      update(n * 2 + 1, m + 1, nr, i, v);
      tree[n] = merge(tree[n * 2], tree[n * 2 + 1]);
   }
   void update(int i, T v) { update(1, 0, N - 1, i, v); };
   node query(int n, int nl, int nr, int l, int r) {
      if (nl > r || nr < l) return {-INF, -INF, -INF, -INF};
      if (nl >= l && nr <= r) return tree[n];
      int m = (nl + nr) >> 1;
      return merge(query(n * 2, nl, m, l, r), query(n * 2 + 1, m + 1, nr, l, r));
   }
   node query(int l, int r) { return query(1, 0, N - 1, l, r); };
};
