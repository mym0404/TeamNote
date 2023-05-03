const int mod = 1e9 + 7;
inline int md(int x) { return md(mod, x); }
inline ll poww(ll a, ll b) {
   ll ret = 1;
   while (b) {
      if (b & 1) {
         ret *= a;
         ret %= mod;
      }
      a *= a;
      if (~mod) a %= mod;
      b >>= 1;
   }
   return ret;
}
vi berlekamp_massey(vi x) {
   vi ls, cur;
   int lf, ld;
   for (int i = 0; i < sz(x); i++) {
      int t = 0;
      for (int j = 0; j < sz(cur); j++) {
         t = md(t + 1ll * x[i - j - 1] * cur[j]);
      }
      if (md(t - x[i]) == 0) continue;
      if (!sz(cur)) {
         cur.resize(i + 1);
         lf = i;
         ld = md(t - x[i]);
         continue;
      }
      int k = md(-(x[i] - t) * poww(ld, mod - 2));
      vi c(i - lf - 1);
      c.pb(k);
      for (auto &j: ls) c.pb(md(-j * k));
      if (sz(c) < sz(cur)) c.resize(sz(cur));
      for (int j = 0; j < sz(cur); j++) {
         c[j] = md(c[j] + cur[j]);
      }
      if (i - lf + sz(ls) >= sz(cur)) {
         tie(ls, lf, ld) = make_tuple(cur, i, md(t - x[i]));
      }
      cur = c;
   }
   for (auto &i: cur) i = md(i);
   reverse(all(cur));
   return cur;
}
vi mul(const vi &a, const vi &b) {
   int n = sz(a), m = sz(b);
   vi ret(n + m - 1);
   for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ret[i + j] = md(ret[i + j] + a[i] * b[j]);
   return ret;
}
vi div(const vi &a, const vi &b) {
   int n = sz(a), m = sz(b);
   vi ret(a);
   for (int i = n - 1; i >= m - 1; i--)
      for (int j = 0; j < m; j++)
         ret[i + j - m + 1] = md(ret[i + j - m + 1] - ret[i] * b[j]);
   ret.resize(m - 1);
   return ret;
}
int kitamasa(int n, const vi &c, const vi &a) {
   if (n < sz(a)) return md(a[n]);
   vi cur{1}, m = c, x = {0, 1};
   for (int &i: m) i *= -1;
   m.pb(1);
   while (n) {
      if (n & 1) cur = div(mul(cur, x), m);
      x = div(mul(x, x), m);
      n >>= 1;
   }
   int ret = 0;
   for (int i = 0; i < sz(c); i++) ret = md(ret + cur[i] * a[i]);
   return ret;
}
int guess(int n, const vi &dp) {
   if (n < sz(dp)) return md(dp[n]);
   vi rec = berlekamp_massey(dp);
   if (!sz(rec)) return -1;
   return kitamasa(n, rec, dp);
}