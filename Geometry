// region GEOMETRY
typedef pair<double, double> pd;
#define x first
#define y second
const double PI = M_PI;
const double RAD = 180 / PI;
double rad_deg(double rad) { return rad * RAD; }
double deg_rad(double deg) { return deg / RAD; }
template<class T>
double tri_area(pair<T, T> a, pair<T, T> b, pair<T, T> c) {
   return 0.5 * abs((a.x * b.y + b.x * c.y + c.x * a.y - b.x * a.y - c.x * b.y - a.x * c.y));
}
template<class T>
int ccw(pair<T, T> a, pair<T, T> b, pair<T, T> c) {
   double ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
   if (ret > 0) return 1;
   else if (ret == 0) return 0;
   else return -1;
}
template<class T>
bool overlap_line(pair<T, T> a, pair<T, T> b, pair<T, T> c, pair<T, T> d) {
   if (a > b) swap(a, b);
   if (c > d) swap(c, d);
   int ccw1 = ccw(a, b, c), ccw2 = ccw(a, b, d), ccw3 = ccw(c, d, a), ccw4 = ccw(c, d, b);
   if (ccw1 == 0 && ccw2 == 0) return a <= d && b >= c;
   return ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0;
}
template<class T>
bool overlap_ve(pair<T, T> a, pair<T, T> b, pair<T, T> c) {
   if (a > b) swap(a, b);
   if (!ccw(a, b, c)) return c >= a && c <= b;
   return false;
}
template<class T>
double dist_v(pair<T, T> a, pair<T, T> b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
template<class T>
double dist_ve_orthogonal(pair<T, T> a, pair<T, T> b, pair<T, T> c) {
   if (a == c || b == c) return 0;
   if (a == b) return dist_v(a, c);
   return 2.0 * tri_area(a, b, c) / dist_v(a, b);
}
template<class T>
vector<pair<T, T>> graham(const vector<pair<T, T>> &_p) {
   if (sz(_p) <= 1) return _p;
   vector<pair<T, T>> p = _p, ret;
   sort(all(p));
   sort(p.begin() + 1, p.end(), [&](const pair<T, T> &a, const pair<T, T> &b) {
      int s = ccw(p[0], a, b);
      if (s == 0) return a < b;
      return s > 0;
   });
   stack<pair<T, T>> s;
   s.push(p[0]), s.push(p[1]);
   for (int i = 2; i < sz(p); i++) {
      while (sz(s) >= 2) {
         pair<T, T> b = s.top();
         s.pop();
         pair<T, T> a = s.top();
         if (ccw(a, b, p[i]) > 0) {
            s.push(b);
            break;
         }
      }
      s.push(p[i]);
   }
   while (sz(s)) {
      ret.pb(s.top());
      s.pop();
   }
   reverse(all(ret));
   return ret;
}
template<class T>
tuple<double, int, int> rotating_callipers(const vector<pair<T, T>> &hull) {
   if (sz(hull) == 2) return {dist_v(hull[0], hull[1]), 0, 1};
   int a = 0, b = 1, c = 1, d = 2, i1, i2;
   double mx = -1;
   while (1) {
      pair<T, T> A = hull[a], B = hull[b], C = hull[c], D = hull[d];
      if (dist_v(A, C) > mx) {
         mx = dist_v(A, C);
         i1 = a;
         i2 = c;
      }
      if (ccw(A, B, {D.x - C.x + B.x, D.y - C.y + B.y}) >= 0) {
         c = (c + 1) % sz(hull);
         d = (d + 1) % sz(hull);
      } else {
         a = (a + 1) % sz(hull);
         b = (b + 1) % sz(hull);
         if (a == 0) break;
      }
   }
   return {mx, i1, i2};
}
template<class T>
bool hull_in_v(const vector<pair<T, T>> &hull, pl p) { // check counter-clockwise hull
   if (sz(hull) == 1) return hull[0] == p;
   if (sz(hull) == 2) return overlap_ve(hull[0], hull[1], p);
   for (int i = 0; i < sz(hull); i++) {
      int s = ccw(hull[i], hull[(i + 1) % sz(hull)], p);
      if (s == 0 && overlap_ve(hull[i], hull[(i + 1) % sz(hull)], p)) return true;
      if (s == -1) return false;
   }
   return true;
}
template<class T>
bool hull_in_hull(const vector<pair<T, T>> &outer, const vector<pair<T, T>> &inner) {
   for (auto i: inner) if (!hull_in_v(outer, i)) return false;
   return true;
}
template<class T>
pd intersect_point(pd a, pd b, pd c, pd d) {
   if (!overlap_line(a, b, c, d)) return {-1e9, -1e9};
   if (c.x == d.x) {
      swap(a, c);
      swap(b, d);
   }
   if (a.x == b.x) { // 직선 1은 기울기가 무한
      return {a.x, (c.y - d.y) / (c.x - d.x) * (a.x - c.x) + c.y};
   } else {
      double m1 = (a.y - b.y) / (a.x - b.x), m2 = (c.y - d.y) / (c.x - d.x);
      double x = (m1 * a.x - m2 * c.x - a.y + c.y) / (m1 - m2), y = m1 * (x - a.x) + a.y;
      return {x, y};
   }
}
// endregion$END$
