string transform(const string &s) {
   string ret = "$";
   for (int i = 0; i < sz(s); i++, ret += '$') ret += s[i];
   return ret;
}
vi manacher(const string &s) {
   vi ret(sz(s));
   for (int i = 0, r = -1, p = -1; i < sz(s); i++) {
      if (r < i) ret[i] = 0;
      else ret[i] = min(r - i, ret[2 * p - i]);
      while (i - ret[i] - 1 >= 0 && i + ret[i] + 1 < sz(s)) {
         if (s[i - ret[i] - 1] == s[i + ret[i] + 1]) ret[i]++;
         else break;
      }
      if (i + ret[i] > r) {
         r = i + ret[i];
         p = i;
      }
   }
   return ret;
}
