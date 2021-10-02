pair<vi, vi> sa_lcp(const string &s) {
   int n = sz(s), d;
   vi sa(n), group(n), lcp(n);
   for (int i = 0; i < n; i++) {
      sa[i] = i;
      group[i] = s[i];
   }
   auto cmp = [&](int i, int j) {
      if (group[i] != group[j]) return group[i] < group[j];
      i += d, j += d;
      if (i < n && j < n) return group[i] < group[j];
      return i > j;
   };
   for (d = 1;; d <<= 1) {
      sort(all(sa), cmp);
      vi tmp(n);
      for (int i = 1; i < n; i++) tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
      for (int i = 0; i < n; i++) group[sa[i]] = tmp[i];
      if (tmp[n - 1] == n - 1) break;
   }
   for (int str_i = 0, m = 0; str_i < n; str_i++, m = max(0, m - 1)) {
      int sa_i = group[str_i];
      if (sa_i == n - 1) continue;
      int str_j = sa[sa_i + 1];
      while (s[str_i + m] == s[str_j + m]) m++;
      lcp[sa_i] = m;
   }
   return {sa, lcp};
}
