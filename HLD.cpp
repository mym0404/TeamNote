template<class T>
struct seg_lazy {
public:
   const T INF = numeric_limits<T>::max() >> 1;
   struct node {
      T sum = 0, min = 0, max = 0, lazy = 0;
      node(T v) : sum(v), min(v), max(v) {}
      node(T sum, T min, T max) : sum(sum), min(min), max(max) {}
   };
   const node identity{0, INF, -INF};
   seg_lazy(int N) : N(N) {
      int tree_size = 1 << ((int) ceil(log2(N)) + 1);
      tree = vector<node>(tree_size, node(0));
   }
   void update(int l, int r, T v) { update(1, 0, N - 1, l, r, v); }
   node query(int l, int r) { return query(1, 0, N - 1, l, r); };
private:
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
};
template<class T>
struct HLD {
   struct Edge { T to, cost; };
   int N, next_dfsn = 0, for_edge, any_cost = 0;
   vi subsize, par, depth, head, in, out;
   vector<vector<Edge>> edges;
   seg_lazy<T> seg;
   HLD(int N, int for_edge = 1)
      : N(N), for_edge(for_edge), par(N), subsize(N), depth(N), edges(N), head(N), in(N), out(N),
        seg(seg_lazy<T>(N)) {}
   void add_edge(int u, int v, T cost = 0) {
      edges[u].pb({v, cost});
      if (cost)any_cost = 1;
   }
   void init(int root = 0) {
      dfs1(root, -1);
      dfs2(root, -1);
      for (int cur = 0; cur < N && any_cost; cur++)
         for (const Edge &e: edges[cur])
            if (par[e.to] == cur)
               update_node(e.to, e.cost);
   }
   void dfs1(int cur, int p) {
      subsize[cur] = 1;
      for (Edge &e: edges[cur]) {
         if (e.to == p) continue;
         depth[e.to] = depth[cur] + 1;
         dfs1(e.to, cur);
         subsize[cur] += subsize[e.to];
         if (subsize[e.to] > subsize[edges[cur][0].to])swap(edges[cur][0], e);
      }
   }
   void dfs2(int cur, int p) {
      par[cur] = p;
      in[cur] = next_dfsn++;
      for (const Edge &e: edges[cur]) {
         if (e.to == par[cur]) continue;
         head[e.to] = (e.to == edges[cur][0].to) ? head[cur] : e.to;
         dfs2(e.to, cur);
      }
      out[cur] = next_dfsn - 1;
   }
   void update_node(int i, T v) { seg.update(in[i], in[i], v); }
   void update_path(int a, int b, T v) {
      for (; head[a] ^ head[b]; a = par[head[a]]) {
         if (depth[head[a]] < depth[head[b]]) swap(a, b);
         seg.update(in[head[a]], in[a], v);
      }
      if (depth[a] > depth[b]) swap(a, b);
      seg.update(in[a] + for_edge, in[b], v);
   }
   T query_sum(int a, int b) {
      T ret = 0;
      for (; head[a] ^ head[b]; a = par[head[a]]) {
         if (depth[head[a]] < depth[head[b]]) swap(a, b);
         ret += seg.query(in[head[a]], in[a]).sum;
      }
      if (depth[a] > depth[b]) swap(a, b);
      return ret + seg.query(in[a] + for_edge, in[b]).sum;
   }
   T query_max(int a, int b) {
      T ret = 0;
      for (; head[a] ^ head[b]; a = par[head[a]]) {
         if (depth[head[a]] < depth[head[b]]) swap(a, b);
         ret = max(ret, seg.query(in[head[a]], in[a]).max);
      }
      if (depth[a] > depth[b]) swap(a, b);
      return ret = max(ret, seg.query(in[a] + for_edge, in[b]).max);
   }
   T query_min(int a, int b) {
      T ret = 1e9;
      for (; head[a] ^ head[b]; a = par[head[a]]) {
         if (depth[head[a]] < depth[head[b]]) swap(a, b);
         ret = min(ret, seg.query(in[head[a]], in[a]).min);
      }
      if (depth[a] > depth[b]) swap(a, b);
      return ret = min(ret, seg.query(in[a] + for_edge, in[b]).min);
   }
   int lca(int a, int b) {
      for (; head[a] ^ head[b]; a = par[head[a]])
         if (depth[head[a]] < depth[head[b]]) swap(a, b);
      return depth[a] < depth[b] ? a : b;
   }
};
