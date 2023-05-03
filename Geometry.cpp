#define x first
#define y second
const double PI = M_PI;
const double RAD = 180 / PI;
double rad_deg(double rad) { return rad * RAD; }
double deg_rad(double deg) { return deg / RAD; }
typedef pair<double, double> pd;
pd operator+(const pd &a, const pd &b) { return {a.x + b.x, a.y + b.y}; }
pd operator-(const pd &a, const pd &b) { return {a.x - b.x, a.y - b.y}; }
pd operator-(const pd &a) { return {-a.x, -a.y}; }
pd operator*(double a, const pd &b) { return {a * b.x, a * b.y}; }
double operator*(const pd &a, const pd &b) { return a.x * b.x + a.y * b.y; }
double operator/(const pd &a, const pd &b) { return a.x * b.y - a.y * b.x; }
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
bool intersect(pair<T, T> a, pair<T, T> b, pair<T, T> c, pair<T, T> d) {
   if (a > b) swap(a, b);
   if (c > d) swap(c, d);
   int ccw1 = ccw(a, b, c), ccw2 = ccw(a, b, d), ccw3 = ccw(c, d, a), ccw4 = ccw(c, d, b);
   if (ccw1 == 0 && ccw2 == 0) return a <= d && b >= c;
   return ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0;
}
template<class T>
bool intersect_ve(pair<T, T> a, pair<T, T> b, pair<T, T> c) {
   if (a > b) swap(a, b);
   if (!ccw(a, b, c)) return c >= a && c <= b;
   return false;
}
template<class T>
double dist(pair<T, T> a, pair<T, T> b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
template<class T>
double dist_ve_orthogonal(pair<T, T> a, pair<T, T> b, pair<T, T> c) {
   if (a == c || b == c) return 0;
   if (a == b) return dist(a, c);
   return 2.0 * tri_area(a, b, c) / dist(a, b);
}
template<class T>
vector<pair<T, T>> graham(const vector<pair<T, T>> &_p) {
   if (sz(_p) <= 1) return _p;
   vector<pair<T, T>> p = _p;
   sort(all(p));
   sort(p.begin() + 1, p.end(), [&](const pair<T, T> &a, const pair<T, T> &b) {
      int c = ccw(p[0], a, b);
      if (!c) return a < b;
      return c > 0;
   });
   vector<pair<T, T>> ret{p[0], p[1]};
   for (int i = 2; i < sz(p); i++) {
      while (sz(ret) >= 2) {
         auto a = ret[sz(ret) - 2], b = ret[sz(ret) - 1];
         if (ccw(a, b, p[i]) > 0) break;
         ret.pop_back();
      }
      ret.pb(p[i]);
   }
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
bool hull_in_v(const vector<pair<T, T>> &hull, pair<T, T> p) { // check counter-clockwise hull
   if (sz(hull) == 1) return hull[0] == p;
   if (sz(hull) == 2) return intersect_ve(hull[0], hull[1], p);
   for (int i = 0; i < sz(hull); i++) {
      int s = ccw(hull[i], hull[(i + 1) % sz(hull)], p);
      if (s == 0 && intersect_ve(hull[i], hull[(i + 1) % sz(hull)], p)) return true;
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
   if (!intersect(a, b, c, d)) return {-1e9, -1e9};
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
template<class T>
double polygon_area(const vector<pair<T, T>> &polygon) {
   double ret = 0;
   for (int i = 0; i < sz(polygon); i++) {
      int j = (i + 1) % sz(polygon);
      ret += polygon[i].x * polygon[j].y - polygon[i].y * polygon[j].x;
   }
   return abs(ret) / 2;
}
template<class T>
bool polygon_in_v(const vector<pair<T, T>> &poly, const pair<T, T> &p) {
   int meet = 0;
   for (int i = 0; i < sz(poly); i++) {
      pair<T, T> a = poly[i], b = poly[(i + 1) % sz(poly)];
      if (intersect_ve(a, b, p)) return 1;
      if (a.y == b.y) continue;
      if (a.y > b.y) swap(a, b);
      double x = a.x + double(p.y - a.y) / (b.y - a.y) * (b.x - a.x);
      if (x >= p.x && a.y <= p.y && b.y >= p.y) {
         if (a.y == p.y || b.y == p.y) meet += (a.y < p.y);
         else meet++;
      }
   }
   return meet & 1;
}
template<class T>
pd center(const pair<T, T> &a, const pair<T, T> &b) {
   return {(a.x + b.x) * 0.5, (a.y + b.y) * 0.5};
}
template<class T>
pd center_outer(const pair<T, T> &a, const pair<T, T> &b, const pair<T, T> &c) {
   pd aa = b - a, bb = c - a;
   double c1 = aa * aa * 0.5, c2 = bb * bb * 0.5;
   double d = aa / bb;
   double x = a.x + (c1 * bb.y - c2 * aa.y) / d;
   double y = a.y + (c2 * aa.x - c1 * bb.x) / d;
   return {x, y};
}