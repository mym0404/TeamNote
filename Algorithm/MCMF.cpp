struct Edge {
   int from, to, c, f = 0, spare, cost;
   Edge *rev;
   Edge(int from, int to, int c, int cost) : from(from), to(to), c(c), cost(cost) {
      spare = c;
   }
   Edge(int from, int to, int c, int cost, Edge *rev) : Edge(from, to, c, cost) {
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
class MCMF {
private:
   int n, source, sink;
public:
   vector<ve> edges;
   MCMF(int n, int source, int sink) : n(n), source(source), sink(sink) {
      edges.resize(n);
   }
   void add_edge(int i, int j, int c, int c_rev, int cost) {
      Edge *e = new Edge(i, j, c, cost);
      Edge *e_rev = new Edge(j, i, c_rev, -cost, e);
      edges[i].pb(e);
      edges[j].pb(e_rev);
   }
   pi flow() {
      int max_flow = 0;
      ll cost_sum = 0;
      while (1) {
         vi from(n, -1), in_q(n, false), d(n, INF);
         ve path(n, 0);
         queue<int> q;
         q.push(source);
         in_q[source] = true;
         d[source] = 0;
         while (sz(q)) { // SPFA
            int cur = q.front();
            q.pop();
            in_q[cur] = false;
            for (Edge *e: edges[cur]) {
               if (e->spare > 0 && d[e->to] > d[cur] + e->cost) {
                  d[e->to] = d[cur] + e->cost;
                  from[e->to] = cur;
                  path[e->to] = e;

                  if (!in_q[e->to]) {
                     q.push(e->to);
                     in_q[e->to] = true;
                  }
               }
            }
         }
         if (from[sink] == -1)
            break;
         int min_flow = INF;
         for (int i = sink; i != source; i = from[i])
            min_flow = min(min_flow, path[i]->spare);
         for (int i = sink; i != source; i = from[i]) {
            path[i]->add_flow(min_flow);
            cost_sum += min_flow * path[i]->cost;
         }
         max_flow += min_flow;
      }
      return {max_flow, cost_sum};
   }
};