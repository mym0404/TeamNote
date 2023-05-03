struct LCA {
   int N, LOG = 0;
   vvi p, edges;
   vi level;
   LCA(int N) : N(N), edges(N), level(N, -1) {
      for (; (1 << LOG) <= N; LOG++);
      p = vvi(N, vi(LOG, -1));
   }
   void add_edge(int i, int j) { edges[i].pb(j); }
   void dfs(int cur, int l) {
      level[cur] = l;
      for (int to: edges[cur])
         if (level[to] == -1) p[to][0] = cur, dfs(to, l + 1);
   }
   void build(int root = 0) {
      dfs(root, 0);
      for (int k = 1; k < LOG; k++)
         for (int i = 0; i < N; i++)
            if (~p[i][k - 1]) p[i][k] = p[p[i][k - 1]][k - 1];
   }
   int find(int i, int j) {
      if (level[i] < level[j]) swap(i, j);
      for (int diff = level[i] - level[j], k = 0; diff; diff >>= 1, k++)
         if (diff & 1) i = p[i][k];
      if (i == j) return i;
      for (int k = LOG - 1; k >= 0; k--)
         if (p[i][k] != p[j][k])
            i = p[i][k], j = p[j][k];
      return p[i][0];
   }
   int dist(int i, int j) {
      int l = find(i, j);
      return level[i] + level[j] - 2 * level[l];
   }
};