struct line {
   mutable ll m, k, p;
   bool operator<(const line &o) const { return m < o.m; }
   bool operator<(ll x) const { return p < x; }
};
struct CHT : multiset<line, less<>> {
   //(for doubles, use inf = 1/.0, div(a,b) = a/b)
   const static ll inf = LLONG_MAX;
   ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
   bool isect(iterator x, iterator y) {
      if (y == end()) return x->p = inf, 0;
      if (x->m == y->m) x->p = x->k > y->k ? inf : -inf;
      else x->p = div(y->k - x->k, x->m - y->m);
      return x->p >= y->p;
   }
   void add(ll m, ll k) { //add y = mx + k
      auto z = insert({m, k}), y = z++, x = y;
      while (isect(y, z)) z = erase(z);
      if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
      while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
   }
   ll query(ll x) {
      auto l = *lower_bound(x);
      return l.m * x + l.k;
   }
} cht;
