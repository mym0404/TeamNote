template<class T>
struct seg_lazy {
private:
   const T INF = numeric_limits<T>::max() >> 1;
   struct node {
      T sum = 0, min = 0, max = 0, lazy = 0;
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
   void propagate(int n, int nl, int nr) {
      if (!tree[n].lazy) return;
      tree[n].sum += (nr - nl + 1) * tree[n].lazy;
      tree[n].max += tree[n].lazy;
      tree[n].min += tree[n].lazy;
      if (nl != nr) {
         tree[n * 2].lazy += tree[n].lazy;
         tree[n * 2 + 1].lazy += tree[n].lazy;
      }
      tree[n].lazy = 0;
   }
   void update(int n, int nl, int nr, int l, int r, T v) {
      propagate(n, nl, nr);
      if (nl > r || nr < l) return;
      if (nl >= l && nr <= r) {
         tree[n].lazy += v;
         propagate(n, nl, nr);
         return;
      }
      int m = (nl + nr) >> 1;
      update(n * 2, nl, m, l, r, v);
      update(n * 2 + 1, m + 1, nr, l, r, v);
      tree[n] = merge(tree[n * 2], tree[n * 2 + 1]);
   }
   node query(int n, int nl, int nr, int l, int r) {
      propagate(n, nl, nr);
      if (nl > r || nr < l) return identity;
      if (nl >= l && nr <= r) return tree[n];
      int m = (nl + nr) >> 1;
      return merge(query(n * 2, nl, m, l, r), query(n * 2 + 1, m + 1, nr, l, r));
   }
public:
   seg_lazy(int N) : N(N) {
      int tree_size = 1 << ((int) ceil(log2(N)) + 1);
      tree = vector<node>(tree_size, node(0));
   }
   void update(int l, int r, T v) { update(1, 0, N - 1, l, r, v); }
   node query(int l, int r) { return query(1, 0, N - 1, l, r); };
};
