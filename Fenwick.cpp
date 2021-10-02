template<class T>
struct fenwick {
   int n;
   vector<T> tree;
   fenwick(int n) : n(n) { tree.resize(n + 1); }
   T sum(int i) {
      T ret = 0;
      for (; i; i -= i & -i) ret += tree[i];
      return ret;
   }
   void update(int i, T x) { for (i++; i <= n; i += i & -i) tree[i] += x; }
   T query(int l, int r) { return l > r ? 0 : sum(r + 1) - sum(l); }
};
template<class T>
struct fenwick_point {
   fenwick<T> f;
   fenwick_point(int n) : f(fenwick<T>(n + 1)) {}
   void update(int l, int r, T x) { f.update(l, x), f.update(r + 1, -x); }
   T query(int i) { return f.query(0, i); }
};
template<class T>
struct fenwick_range {
   fenwick<T> d, c;
   fenwick_range(int n) : d(fenwick<T>(n + 1)), c(fenwick<T>(n + 1)) {}
   void update(int l, int r, T x) {
      d.update(l, x), d.update(r + 1, -x), c.update(l, (1 - l) * x), c.update(r + 1, r * x);
   }
   T query(int l, int r) {
      l--;
      return d.query(0, r) * r + c.query(0, r) - (l >= 0 ? d.query(0, l) * l + c.query(0, l) : 0);
   }
};
