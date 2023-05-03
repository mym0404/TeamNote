template<class T>
struct seg_tree {
private:
   const T INF = numeric_limits<T>::max() >> 1;
   struct node {
      T sum = 0, min = 0, max = 0;
      node(T v) : sum(v), min(v), max(v) {}
      node(T sum, T min, T max) : sum(sum), min(min), max(max) {}
   };
   const node identity{0, INF, -INF};
   int N;
   vector<node> tree;
   node merge(node l, node r) {
      node ret = {l.sum + r.sum, min(l.min, r.min), max(l.max, r.max)};
      return ret;
   }
   void update(int n, int nl, int nr, int i, T v) {
      if (nl > i || nr < i) return;
      if (nl == nr) {
         tree[n] = node(v); // diff or assign?
         return;
      }
      int m = (nl + nr) >> 1;
      update(n * 2, nl, m, i, v);
      update(n * 2 + 1, m + 1, nr, i, v);
      tree[n] = merge(tree[n * 2], tree[n * 2 + 1]);
   }
   node query(int n, int nl, int nr, int l, int r) {
      if (nl > r || nr < l) return identity;
      if (nl >= l && nr <= r) return tree[n];
      int m = (nl + nr) >> 1;
      return merge(query(n * 2, nl, m, l, r), query(n * 2 + 1, m + 1, nr, l, r));
   }
public:
   seg_tree(int N) : N(N) {
      int tree_size = 1 << ((int) ceil(log2(N)) + 1);
      tree = vector<node>(tree_size, identity);
   }
   void update(int i, T v) { update(1, 0, N - 1, i, v); }
   node query(int l, int r) { return query(1, 0, N - 1, l, r); };
};