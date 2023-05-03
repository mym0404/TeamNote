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
      if (capacity_rev != 0) rev->add_capacity(capacity_rev, 0);
   }
   void add_flow(int v) {
      f += v, rev->f -= v;
      spare -= v, rev->spare += v;
   }
};
typedef vector<Edge *> ve;
const int INF = 2e9;
class MaxFlow {
private:
   int n, source, sink;
public:
   vector<ve> edges;
   MaxFlow(int n, int source, int sink) : n(n), source(source), sink(sink) {
      edges.resize(n);
   }
   void add_edge(int i, int j, int c, int c_rev = 0) {
      Edge *e = new Edge(i, j, c), *e_rev = new Edge(j, i, c_rev, e);
      edges[i].pb(e), edges[j].pb(e_rev);
   }
   int flow() {
      int ret = 0;
      while (1) {
         vi from(n, -1);
         ve path(n, 0);
         queue<int> q;
         q.push(source);
         while (sz(q)) {
            int cur = q.front();
            q.pop();
            for (Edge *e: edges[cur]) {
               if (from[e->to] == -1 && e->spare > 0) {
                  from[e->to] = cur;
                  path[e->to] = e;
                  q.push(e->to);
               }
            }
         }
         if (from[sink] == -1) break;
         int min_flow = INF;
         for (int i = sink; i != source; i = from[i]) min_flow = min(min_flow, path[i]->spare);
         for (int i = sink; i != source; i = from[i]) path[i]->add_flow(min_flow);
         ret += min_flow;
      }
      return ret;
   }
};