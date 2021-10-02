const int MAX = 1e6;
vector<int> primes, spf(MAX + 1, -1), mu(MAX + 1);
void sieve() {
   mu[1] = 1;
   for (int i = 2; i <= MAX; i++) {
      if (spf[i] == -1) {
         primes.pb(i);
         spf[i] = i;
         mu[i] = -1;
      }
      for (int p: primes) {
         if (i * p > MAX) break;
         spf[i * p] = p;
         if (!(i % p)) {
            mu[i * p] = 0;
            break;
         }
         mu[i * p] = mu[i] * mu[p];
      }
   }
}
