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
         if (edges[cur][0].to == p || subsize[e.to] > subsize[edges[cur][0].to])swap(edges[cur][0], e);
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
   int lca(int a, int b) {
      for (; head[a] ^ head[b]; a = par[head[a]])
         if (depth[head[a]] < depth[head[b]]) swap(a, b);
      return depth[a] < depth[b] ? a : b;
   }
};