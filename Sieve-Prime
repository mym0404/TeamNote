const int MAX = 1e6;
vector<int> primes, spf(MAX + 1, -1);
void sieve() {
   for (int i = 2; i <= MAX; i++) {
      if (spf[i] == -1) {
         primes.pb(i);
         spf[i] = i;
      }
      for (int p: primes) {
         if (i * p > MAX) break;
         spf[i * p] = p;
         if (!(i % p)) break;
      }
   }
}
inline bool prime(int x) {
   if (x < 2 || x > MAX) return 0;
   if (sz(primes)) return spf[x] == x;
   for (int i = 2; i * i <= x; i++) if (!(x % i))return 0;
   return 1;
}
inline vector<pi> factorize(int x) {
   vector<pi> ret;
   while (x > 1) {
      int p = spf[x], c = 0;
      while (spf[x] == p)c++, x /= spf[x];
      ret.pb({p, c});
   }
   return ret;
}
