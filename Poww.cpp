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
