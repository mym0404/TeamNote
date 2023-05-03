struct BCC {
   int N, next_dfsn = 0;
   vvi edges, bcc_v;
   vi dfsn, included;
   stack<pi> s;
   vector<vector<pi>> bcc_e;
   BCC(int N) : N(N), edges(N), dfsn(N, -1), included(N) {}
   void add_edge(int u, int v) { edges[u].pb(v), edges[v].pb(u); }
   int dfs(int cur, int p) {
      int ret = dfsn[cur] = next_dfsn++;
      for (int to: edges[cur]) {
         if (to == p) continue;
         if (dfsn[to] < dfsn[cur]) s.push({cur, to});
         if (~dfsn[to]) {
            ret = min(ret, dfsn[to]);
         } else {
            int tmp = dfs(to, cur);
            ret = min(ret, tmp);
            if (tmp >= dfsn[cur]) {
               included[cur]++;
               bcc_v.emplace_back(), bcc_e.emplace_back();
               while (1) {
                  auto [u, v] = s.top();
                  s.pop();
                  bcc_e.back().pb({u, v});
                  bcc_v.back().pb(u), bcc_v.back().pb(v);
                  if (mp(u, v) == mp(cur, to)) break;
               }
               uniq(bcc_v.back());
            }
         }
      }
      return ret;
   }
   void build() {
      for (int i = 0; i < N; i++) if (dfsn[i] == -1) dfs(i, -1); else included[i]++;
   }
};