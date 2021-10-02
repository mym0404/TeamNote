struct LCA {
   int N, LOG;
   vvi p, edges;
   vi level;
   LCA(int N, int LOG = 18) : N(N), LOG(LOG) {
      p = vvi(N, vi(LOG + 1, -1));
      edges = vvi(N);
      level = vi(N, -1);
   }
   void add_edge(int i, int j) { edges[i].pb(j); }
   void dfs(int cur, int l) {
      level[cur] = l;
      for (int to: edges[cur])
         if (level[to] == -1) p[to][0] = cur, dfs(to, l + 1);
   }
   void pre_calc(int root) {
      dfs(root, 0);
      for (int k = 1; k <= LOG; k++)
         for (int i = 0; i < N; i++)
            if (~p[i][k - 1]) p[i][k] = p[p[i][k - 1]][k - 1];
   }
   int find(int i, int j) {
      if (level[i] < level[j]) swap(i, j);
      for (int diff = level[i] - level[j], k = 0; diff; diff >>= 1, k++)
         if (diff & 1) i = p[i][k];
      if (i == j) return i;
      for (int k = LOG; k >= 0; k--)
         if (p[i][k] != p[j][k])
            i = p[i][k], j = p[j][k];
      return p[i][0];
   }
};
