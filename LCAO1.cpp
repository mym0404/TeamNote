struct LCA_O1 {
   int N, LOG = 0, dfsn = 0;
   vvi edges;
   vi level, in, e, lg2, pw2;
   vector<vector<pi>> sparse;
   LCA_O1(int N)
      : N(N), level(N), in(N, -1), e(N * 2 - 1), edges(N), lg2(N * 2, -1) {
      for (; (1 << LOG) <= N; LOG++);
      LOG++;
      sparse.resize(N * 2 - 1, vector<pi>(LOG));
      pw2.resize(LOG, 1);
   }
   void add_edge(int i, int j) { edges[i].pb(j); }
   void dfs(int cur, int l) {
      level[cur] = l;
      e[dfsn] = cur;
      in[cur] = dfsn++;
      for (int to: edges[cur]) {
         if (in[to] == -1) {
            dfs(to, l + 1);
            e[dfsn++] = cur;
         }
      }
   }
   void build(int root = 0) {
      for (int i = 1, k = 0; i < N * 2; i <<= 1, k++) lg2[i] = k;
      for (int i = 2; i < N * 2; i++) if (lg2[i] == -1)lg2[i] = lg2[i - 1];
      for (int i = 1; i < LOG; i++) pw2[i] = pw2[i - 1] << 1;
      dfs(root, 0);
      for (int i = 0; i < N * 2 - 1; i++) sparse[i][0] = {level[e[i]], e[i]};
      for (int k = 1; k < LOG; k++) {
         for (int i = 0; i + pw2[k - 1] < N * 2 - 1; i++) {
            int j = i + pw2[k - 1];
            sparse[i][k] = min(sparse[i][k - 1], sparse[j][k - 1]);
         }
      }
   }
   int find(int a, int b) {
      int l = min(in[a], in[b]), r = max(in[a], in[b]), k = lg2[r - l + 1];
      r -= pw2[k] - 1;
      return min(sparse[l][k], sparse[r][k]).se;
   }
   int dist(int a, int b) {
      int l = find(a, b);
      return level[a] + level[b] - level[l] * 2;
   }
};