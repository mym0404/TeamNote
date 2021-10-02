class SCC {
public:
   vvi edges, scc, scc_edges;
   vi sn, dfsn, fin, entry;
   int N, next_dfsn = 0, next_sccn = 0;
   SCC(int N) : N(N) {
      edges.resize(N);
      sn.resize(N);
      dfsn.resize(N, -1);
      fin.resize(N, 0);
   }
   void add_edge(int from, int to) { edges[from].pb(to); }
   void find() {
      for (int i = 0; i < N; i++)
         if (dfsn[i] == -1)
            dfs(i);
   }
   void find_scc_edges() {
      scc_edges.resize(next_sccn);
      entry.resize(next_sccn);
      for (int i = 0; i < N; i++)
         for (int j: edges[i])
            if (sn[i] != sn[j]) {
               scc_edges[sn[i]].pb(sn[j]);
               entry[sn[j]]++;
            }
   }
   void add_or(int x, int y) {
      add_edge(x ^ 1, y);
      add_edge(y ^ 1, x);
   }
   void add_xor(int x, int y) {
      add_or(x, y);
      add_or(x ^ 1, y ^ 1);
   }
   void add_onezero(int x, int y, int z) {
      add_or(x ^ 1, y ^ 1);
      add_or(y ^ 1, z ^ 1);
      add_or(z ^ 1, x ^ 1);
   }
   vi two_sat() {
      for (int i = 0; i < N; i++) if (sn[i] == sn[i ^ 1]) return {-1};
      vi ans(N >> 1, -1);
      for (int i = next_sccn - 1; i >= 0; i--)
         for (int n: scc[i])
            if (ans[n >> 1] == -1)
               ans[n >> 1] = !(n & 1);
      return ans;
   }
private:
   stack<int> s;
   int dfs(int cur) {
      dfsn[cur] = next_dfsn++;
      s.push(cur);
      int low = dfsn[cur];
      for (int to: edges[cur]) {
         if (!fin[to]) {
            if (dfsn[to] == -1) low = min(low, dfs(to));
            else low = min(low, dfsn[to]);
         }
      }
      if (low == dfsn[cur]) {
         vi tmp;
         while (1) {
            int popped = s.top();
            s.pop();
            fin[popped] = true;
            sn[popped] = next_sccn;
            tmp.pb(popped);
            if (popped == cur) break;
         }
         next_sccn++;
         scc.pb(tmp);
      }
      return low;
   }
};
