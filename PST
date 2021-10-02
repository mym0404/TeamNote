template<class T>
struct persistent_seg_tree {
   int N;
   struct Node { int l = -1, r = -1; T v = 0; };
   vi root; // entry point of i th index (1-based)
   vector<Node> tree;
   persistent_seg_tree(int N) : N(N) {
      tree.pb({}); // root;
      root.pb(0);
   }
   int add(int i, T v) {
      int new_root = sz(tree);
      tree.pb({});
      make_tree(root.back(), new_root, 0, N - 1, i, v);
      root.pb(new_root);
      return new_root;
   }
   T query(int root_idx, int l, int r) { return query(root_idx, 0, N - 1, l, r); }
private:
   void make_tree(int prev, int cur, int nl, int nr, int i, T v) {
      if (nl == nr) {
         tree[cur].v += v;
         return;
      }
      if (tree[prev].l == -1) {
         int l = sz(tree), r = l + 1;
         tree[prev].l = l, tree[prev].r = r;
         tree.pb({});
         tree.pb({});
      }
      int m = (nl + nr) >> 1;
      if (i <= m) {
         tree[cur].l = sz(tree);
         tree.pb(tree[tree[prev].l]);
         tree[cur].r = tree[prev].r;
         make_tree(tree[prev].l, tree[cur].l, nl, m, i, v);
      } else {
         tree[cur].r = sz(tree);
         tree.pb(tree[tree[prev].r]);
         tree[cur].l = tree[prev].l;
         make_tree(tree[prev].r, tree[cur].r, m + 1, nr, i, v);
      }
      tree[cur].v = tree[tree[cur].l].v + tree[tree[cur].r].v;
   }
   T query(int n, int nl, int nr, int l, int r) {
      if (nl > r || nr < l || n == -1) return 0;
      if (nl >= l && nr <= r) return tree[n].v;
      int m = (nl + nr) >> 1;
      return query(tree[n].l, nl, m, l, r) + query(tree[n].r, m + 1, nr, l, r);
   }
};
