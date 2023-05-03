struct bipartite {
   int N, M;
   vvi edges;
   vi vis, A, B;
   bipartite(int N, int M = -1) : N(N), M(~M ? M : N) {
      edges.resize(N);
      A.resize(N, -1), B.resize(M, -1), vis.resize(N);
   }
   void add_edge(int f, int t) { edges[f].pb(t); }
   bool dfs(int a) {
      vis[a] = 1;
      for (int b: edges[a]) {
         if (B[b] == -1 || !vis[B[b]] && dfs(B[b])) {
            A[a] = b, B[b] = a;
            return 1;
         }
      }
      return 0;
   }
   int match() {
      int ret = 0;
      for (int i = 0; i < N; i++)
         fill(all(vis), 0), ret += dfs(i);
      return ret;
   }
};