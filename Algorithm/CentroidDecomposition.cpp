struct centroid {
   int N;
   vi tree_size, vis, par;
   vvi _edges, edges;
   centroid(int N) : N(N), tree_size(N), vis(N), _edges(N), edges(N), par(N) {}
   void add_edge(int u, int v) { _edges[u].pb(v); }
   int get_size(int cur, int p) {
      tree_size[cur] = 1;
      for (int to: _edges[cur])if (to != p && !vis[to])tree_size[cur] += get_size(to, cur);
      return tree_size[cur];
   }
   int get_centroid(int cur, int p, int cap) {
      for (int to: _edges[cur]) if (to != p && !vis[to] && tree_size[to] * 2 > cap) return get_centroid(to, cur, cap);
      return cur;
   }
   int build_tree(int cur, int p = -1) {
      cur = get_centroid(cur, -1, get_size(cur, -1));
      par[cur] = p, vis[cur] = 1;
      for (int to: _edges[cur])if (!vis[to]) to = build_tree(to, cur), edges[cur].pb(to), edges[to].pb(cur);
      return cur;
   }
};