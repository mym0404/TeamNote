string transform(const string &s) {
   string ret = "$";
   for (int i = 0; i < sz(s); i++, ret += '$') ret += s[i];
   return ret;
}
vi manacher(const string &s) {
   int n = sz(s), p = 0;
   vi ret(n);

   for (int i = 1; i < n; i++) {
      int r = p + ret[p];
      if (r >= i) ret[i] = min(r - i, ret[2 * p - i]);
      while (i - ret[i] - 1 >= 0 && s[i - ret[i] - 1] == s[i + ret[i] + 1])
         ret[i]++;
      if (i + ret[i] >= r) p = i;
   }

   return ret;
}