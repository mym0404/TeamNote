vi kmp(const string &s, const string &f) {
   vi fallback(sz(f)), ret;
   int j = 0;
   for (int i = 1; i < sz(f); i++) {
      while (j > 0 && f[j] != f[i]) j = fallback[j - 1];
      if (f[i] == f[j]) fallback[i] = ++j;
   }
   j = 0;
   for (int i = 0; i < sz(s); i++) {
      while (j > 0 && f[j] != s[i]) j = fallback[j - 1];
      if (s[i] == f[j]) {
         if (j == sz(f) - 1) {
            ret.pb(i - sz(f) + 1);
            j = fallback[j];
         } else {
            j++;
         }
      }
   }
   return ret;
}
