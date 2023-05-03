array<ll, 3> gcdx(ll A, ll B) {
   ll x1 = 1, x2 = 0, y1 = 0, y2 = 1, r1 = A, r2 = B;
   while (r2) {
      ll q = r1 / r2 - ((r1 ^ r2) < 0 && r1 % r2);
      tie(x1, x2) = mp(x2, x1 - x2 * q);
      tie(y1, y2) = mp(y2, y1 - y2 * q);
      tie(r1, r2) = mp(r2, r1 - r2 * q);
   }
   return {x1, y1, r1};
}