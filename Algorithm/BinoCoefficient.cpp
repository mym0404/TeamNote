const int MAX = 1'000'000;
const ll mod = 1e9 + 7;
vl fac(MAX + 1, 1LL), inv(MAX + 1);
array<ll, 3> gcdx(ll A, ll B) {
   ll x1 = 1, x2 = 0, y1 = 0, y2 = 1, r1 = A, r2 = B;
   while (r2) {
      ll q = r1 / r2;
      if (r1 - r2 * q < 0) q--;
      tie(x1, x2) = mp(x2, x1 - x2 * q);
      tie(y1, y2) = mp(y2, y1 - y2 * q);
      tie(r1, r2) = mp(r2, r1 - r2 * q);
   }
   return {x1, y1, r1};
}
void pre_calc() {
   for (int i = 2; i <= MAX; i++) fac[i] = md(mod, fac[i - 1] * i);
   inv[MAX] = gcdx(fac[MAX], mod)[0];
   for (int i = MAX - 1; i >= 0; i--) inv[i] = md(mod, inv[i + 1] * (i + 1));
}
ll bino(int i, int j) {
   if (j > i) return 0LL;
   return md(mod, md(mod, fac[i] * inv[j]) * inv[i - j]);
}