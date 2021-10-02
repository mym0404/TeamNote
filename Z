vi z_algorithm(const string &s) {
   vi Z(sz(s));
   for (int i = 1, L, R = -1; i < sz(s); i++) {
      if (i > R) {
         L = R = i;
         while (R < sz(s) && s[R] == s[R - i])R++;
         Z[i] = R - L;
         R--;
      } else {
         int K = i - L;
         if (i + Z[K] <= R) Z[i] = Z[K];
         else {
            L = i;
            while (R < sz(s) && s[R] == s[R - i]) R++;
            Z[i] = R - L;
            R--;
         }
      }
   }
   return Z;
}
