struct _miller {
   bool primei(ll n) {
      if (n <= 1) return 0;
      for (auto &a: {2, 7, 61}) {
         if (n == a) return 1;
         if (!primable(n, a)) return 0;
      }
      return 1;
   }
   bool primell(ll n) {
      for (auto &a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
         if (n == a) return 1;
         if (n > 40 && !primable(n, a)) return 0;
      }
      if (n <= 40) return 0;
      return 1;
   }
private:
   inline ll poww(ll a, ll b, ll mod) {
      __int128_t ret = 1;
      while (b) {
         if (b & 1) ret = mul(ret, a, mod);
         a = mul(a, a, mod);
         b >>= 1;
      }
      return ret;
   }
   bool primable(ll n, ll a) {
      if (!(n % a))return 0;
      ll d = (n - 1) >> 1;
      while (1) {
         ll tmp = poww(a, d, n);
         if (tmp == n - 1) return 1;
         if (d & 1) return (tmp == 1 || tmp == n - 1);
         d >>= 1;
      }
   }
protected:
   inline ll mul(ll x, ll y, ll mod) { return (__int128_t) x * y % mod; }
} miller;
