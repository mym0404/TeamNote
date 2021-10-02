struct DSU {
   vector<int> p;
   DSU(int n) { p.resize(n, -1); }
   int gp(int n) {
      if (p[n] < 0) return n;
      return gp(p[n]);
   }
   void merge(int a, int b, int to_b = 0) {
      a = gp(a), b = gp(b);
      if (a == b) return;
      if (size(a) < size(b) || to_b) {
         p[b] += p[a];
         p[a] = b;
      } else {
         p[a] += p[b];
         p[b] = a;
      }
   }
   bool is_merged(int a, int b) { return gp(a) == gp(b); }
   int size(int n) { return -p[gp(n)]; }
};
