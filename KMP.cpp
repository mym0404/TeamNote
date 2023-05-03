vi kmp_fail(const string &s) {
   vi fail(sz(s));
   for (int i = 1, j = 0; i < sz(s); i++) {
      while (j > 0 && s[j] != s[i]) j = fail[j - 1];
      if (s[i] == s[j]) fail[i] = ++j;
   }
   return fail;
}
vi kmp(const string &s, const string &f) {
   vi fail = kmp_fail(f), ret;
   for (int i = 0, j = 0; i < sz(s); i++) {
      while (j > 0 && f[j] != s[i]) j = fail[j - 1];
      if (s[i] == f[j]) {
         if (j == sz(f) - 1) ret.pb(i - sz(f) + 1), j = fail[j];
         else ++j;
      }
   }
   return ret;
}