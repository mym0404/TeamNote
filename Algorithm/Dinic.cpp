struct Edge {
   int from, to, c, f = 0, spare;
   Edge *rev;
   Edge(int from, int to, int c) : from(from), to(to), c(c) {
      spare = c;
   }
   Edge(int from, int to, int c, Edge *rev) : Edge(from, to, c) {
      this->rev = rev;
      rev->rev = this;
   }
   void add_capacity(int capacity, int capacity_rev = 0) {
      c += capacity;
      spare += capacity;
      if (capacity_rev != 0)
         rev->add_capacity(capacity_rev, 0);
   }
   void add_flow(int v) {
      f += v;
      rev->f -= v;
      spare -= v;
      rev->spare += v;
   }
};
typedef vector<Edge *> ve;
const int INF = 2e9;
struct dinic {
   int n, source, sink;
   vector<ve> edges;
   dinic(int n, int source, int sink) : n(n), source(source), sink(sink) {
      edges.resize(n);
   }
   void add_edge(int i, int j, int c, int c_rev = 0) {
      Edge *e = new Edge(i, j, c);
      Edge *e_rev = new Edge(j, i, c_rev, e);
      edges[i].pb(e);
      edges[j].pb(e_rev);
   }

   int flow() {
      int ret = 0;
      vi level(n), work(n);

      function<bool()> bfs = [&]() {
         fill(all(level), -1);
         queue<int> q;
         q.push(source);
         level[source] = 0;
         while (sz(q)) {
            int cur = q.front();
            q.pop();
            for (Edge *e: edges[cur]) {
               if (level[e->to] == -1 && e->spare > 0) {
                  level[e->to] = level[cur] + 1;
                  q.push(e->to);
               }
            }
         }
         return level[sink] != -1;
      };

      function<int(int, int)> dfs = [&](int cur, int flow) -> int {
         if (cur == sink)
            return flow;
         for (int &i = work[cur]; i < sz(edges[cur]); i++) {
            Edge *e = edges[cur][i];
            if (level[e->to] == level[cur] + 1 && e->spare > 0) {
               int df = dfs(e->to, min(e->spare, flow));
               if (df > 0) {
                  e->add_flow(df);
                  return df;
               }
            }
         }
         return 0;
      };
      while (bfs()) {
         fill(all(work), 0);
         while (1) {
            int df = dfs(source, INF);
            if (df == 0)
               break;
            ret += df;
         }
      }

      return ret;
   }
};