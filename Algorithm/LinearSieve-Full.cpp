const int MAX = 1e6;
vector<int> primes, spf(MAX + 1, -1), pk(MAX + 1), mu(MAX + 1), tau(MAX + 1), sigma(MAX + 1), phi(MAX + 1);
inline ll poww(ll a, ll b, ll mod = -1) {
   ll ret = 1;
   while (b) {
      if (b & 1) {
         ret *= a;
         if (~mod) ret %= mod;
      }
      a *= a;
      if (~mod) a %= mod;
      b >>= 1;
   }
   return ret;
}
void sieve() {
   mu[1] = tau[1] = sigma[1] = phi[1] = 1;
   for (int i = 2; i <= MAX; i++) {
      if (spf[i] == -1) {
         primes.pb(i);
         spf[i] = i;
         pk[i] = 1;
         mu[i] = -1;
         tau[i] = 2;
         sigma[i] = i + 1;
         phi[i] = i - 1;
      }
      for (int p: primes) {
         if (i * p > MAX) break;
         spf[i * p] = p;
         if (!(i % p)) {
            pk[i * p] = pk[i] + 1;
            mu[i * p] = 0;
            tau[i * p] = tau[i] / pk[i * p] * (pk[i * p] + 1);
            sigma[i * p] = sigma[i] * (p - 1) / (poww(p, pk[i * p]) - 1) * (poww(p, pk[i * p] + 1) - 1) / (p - 1);
            phi[i * p] = phi[i] * p;
            break;
         }
         pk[i * p] = 1;
         mu[i * p] = mu[i] * mu[p];
         tau[i * p] = tau[i] * tau[p];
         sigma[i * p] = sigma[i] * sigma[p];
         phi[i * p] = phi[i] * phi[p];
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