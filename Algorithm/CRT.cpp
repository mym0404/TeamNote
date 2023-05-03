array<ll, 3> gcdx(ll A, ll B) {
   ll x1 = 1, x2 = 0, y1 = 0, y2 = 1, r1 = A, r2 = B;
   while (r2) {
      ll q = r1 / r2 - ((r1 ^ r2) < 0 && r1 % r2 != 0);
      tie(x1, x2) = mp(x2, x1 - x2 * q);
      tie(y1, y2) = mp(y2, y1 - y2 * q);
      tie(r1, r2) = mp(r2, r1 - r2 * q);
   }
   return {x1, y1, r1};
}
ll crt(const vl &a, const vl &m) {
   ll a1 = a[0], m1 = m[0];
   for (int i = 1; i < sz(m); ++i) {
      ll a2 = a[i], m2 = m[i];
      auto[x, _, g] = gcdx(m1, m2);
      if ((a2 - a1) % g) return -1;
      ll k1 = x * (a2 - a1) / g;
      a1 = a1 + m1 * k1;
      m1 = lcm(m1, m2);
      a1 = md(m1, a1);
   }
   return a1;
}
