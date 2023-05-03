struct DSU {
   vector<int> p;
   DSU(int n) : p(n, -1) {}
   int gp(int n) {
      if (p[n] < 0) return n;
      return p[n] = gp(p[n]);
   }
   void merge(int a, int b, int to_b = 0) {
      a = gp(a), b = gp(b);
      if (a == b) return;
      if (!to_b && size(a) > size(b)) swap(a, b);
      p[b] += p[a];
      p[a] = b;
   }
   bool is_merged(int a, int b) { return gp(a) == gp(b); }
   int size(int n) { return -p[gp(n)]; }
};