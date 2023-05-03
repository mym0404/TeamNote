struct Node { int l = -1, r = -1, v = 0; };
struct PST {
   vi version;
   int N;
   vector<Node> tree;

   PST(int n) : N(n) {
      tree.pb({});
      version.pb(0);
   }
   int update(int i, int v) {
      int prev_root = version.back();
      int root = sz(tree);
      tree.pb({}), version.pb(root);
      update(prev_root, root, 0, N - 1, i, v);
      return sz(version) - 1;
   }
   int query(int version_idx, int l, int r) {
      return query(version[version_idx], 0, N - 1, l, r);
   }
private:
   void update(int prev, int cur, int nl, int nr, int i, int v) {
      if (cur == -1 || nr < i || nl > i) return;
      if (nl == nr) {
         tree[cur].v += v;
         return;
      }

      // For convenience, makes previous tree always has node in this place
      if (tree[prev].l == -1) {
         tree[prev].l = sz(tree);
         tree[prev].r = sz(tree) + 1;
         tree.pb({}), tree.pb({});
      }

      int m = nl + (nr - nl) / 2;
      if (i <= m) {
         int new_child = sz(tree);
         tree.pb(tree[tree[prev].l]);
         tree[cur].l = new_child;
         tree[cur].r = tree[prev].r;
         update(tree[prev].l, tree[cur].l, nl, m, i, v);
      } else {
         int new_child = sz(tree);
         tree.pb(tree[tree[prev].r]);
         tree[cur].l = tree[prev].l;
         tree[cur].r = new_child;
         update(tree[prev].r, tree[cur].r, m + 1, nr, i, v);
      }

      tree[cur].v = (~tree[cur].l ? tree[tree[cur].l].v : 0) + (~tree[cur].r ? tree[tree[cur].r].v : 0);
   }
   int query(int n, int nl, int nr, int l, int r) {
      if (n == -1 || nr < l || nl > r) return 0;
      if (nl >= l && nr <= r) return tree[n].v;
      int m = nl + (nr - nl) / 2;
      return query(tree[n].l, nl, m, l, r) + query(tree[n].r, m + 1, nr, l, r);
   }
};