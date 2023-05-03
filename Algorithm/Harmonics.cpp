template<class T>
vector<array<T, 3>> harmonics(T mn, T mx) {
   vector<array<T, 3>> ret;
   for (T l = mn, r; l <= mx; l = r + 1) {
      T v = mx / l;
      r = mx / v;
      ret.pb({l, r, v});
   }
   return ret;
}