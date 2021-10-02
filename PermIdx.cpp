int permutation_idx(const vi &v) {
   int ret = 0;
   rep(i, 0, v.size()) {
      int less = 0;
      rep(j, i + 1, v.size())less += v[j] < v[i];
      ret += less * factorial[v.size() - i - 1];
   }
   return ret;
}
