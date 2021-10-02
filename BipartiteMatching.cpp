class Matching {
private:
   int n, m;
public:
   vvi edges;
   vi vis, A, B;
   Matching(int n, int m = -1) : n(n) {
      if (m == -1) m = n;
      edges.resize(n);
      A.resize(n, -1);
      B.resize(m, -1);
   }
   void add_edge(int f, int t) { edges[f].pb(t); }
   bool dfs(int a) {
      vis[a] = true;
      for (int b: edges[a]) {
         if (B[b] == -1 || !vis[B[b]] && dfs(B[b])) {
            A[a] = b;
            B[b] = a;
            return true;
         }
      }
      return false;
   }
   int match() {
      int ret = 0;
      for (int i = 0; i < n; i++) {
         vis = vi(n, false);
         ret += dfs(i);
      }
      return ret;
   }
};
