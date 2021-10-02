struct _random {
   mt19937 gen;
   _random() : gen((unsigned) chrono::steady_clock::now().time_since_epoch().count()) {}
   template<class T = int>
   T nextInt(T l = 0, T r = 32767) { return uniform_int_distribution<T>(l, r)(gen); }
   double nextDouble(double l = 0, double r = 1) { return uniform_real_distribution<double>(l, r)(gen); }
} rd;
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
   inline ll poww(ll a, ll b, ll mod) {
      __int128_t ret = 1;
      while (b) {
         if (b & 1) ret = mul(ret, a, mod);
         a = mul(a, a, mod);
         b >>= 1;
      }
      return ret;
   }
   inline ll mul(ll x, ll y, ll mod) { return (__int128_t) x * y % mod; }
} miller;

struct _pollard : public _miller, _random {
   void fn(ll n, vl &ret) {
      if (n == 1) return;
      if (!(n & 1)) {
         ret.pb(2);
         fn(n >> 1, ret);
         return;
      }
      if (primell(n)) {
         ret.pb(n);
         return;
      }
      ll g = 1, j, k, a = nextInt<ll>(1, 20);
      j = k = nextInt<ll>(2, n - 1);
      auto f = [&](ll x) { return (mul(x, x, n) + a) % n; };
      while (g == 1) j = f(j), k = f(f(k)), g = gcd(j - k, n);
      fn(g, ret), fn(n / g, ret);
   }
   vector<pair<ll, int>> factorize(ll n) {
      vl v;
      vector<pair<ll, int>> ret;
      fn(n, v);
      sort(all(v));
      for (int i = 1, cnt = 1; i <= sz(v); i++, cnt++)
         if (i == sz(v) || v[i] != v[i - 1]) ret.pb({v[i - 1], cnt}), cnt = 0;
      return ret;
   }
} pollard;
