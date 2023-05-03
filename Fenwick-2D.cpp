class fenwick_2d {
public:
   int Y, X;
   vvi tree;
   fenwick_2d(int Y, int X) : Y(Y), X(X) {
      tree.resize(Y, vi(X));
   }
   void update(int y, int x, int diff) {
      while (y <= Y) {
         int _x = x;
         while (_x <= X) {
            tree[y][_x] += diff;
            _x += _x & -_x;
         }
         y += y & -y;
      }
   }
   int sum(int y, int x) {
      if (y <= 0 || x <= 0) return 0;
      int ret = 0;
      while (y) {
         int _x = x;
         while (_x) {
            ret += tree[y][_x];
            _x -= _x & -_x;
         }
         y -= y & -y;
      }
      return ret;
   }
   int query(int y1, int x1, int y2, int x2) {
      return sum(y2, x2) - sum(y1 - 1, x2) - sum(y2, x1 - 1) + sum(y1 - 1, x1 - 1);
   }
};