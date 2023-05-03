template<class T>
void rot(vector<vector<T>> &b, bool cw = 0) {
   int r = sz(b), c = sz(b[0]);
   auto t = vector<vector<T>>(c, vector<T>(r));
   for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
         t[!cw ? j : c - 1 - j][!cw ? r - 1 - i : i] = b[i][j];
   b = t;
}
template<class T>
void rot_partial(vector<vector<T>> &b, int y1, int x1, int y2, int x2, bool cw = 0) {
   int r = y2 - y1 + 1, c = x2 - x1 + 1;
   assert(r == c);
   auto t = vector<vector<T>>(r, vector<T>(c));
   for (int i = 0; i < r; i++)
      for (int j = 0; j < c; j++)
         t[!cw ? j : c - 1 - j][!cw ? r - 1 - i : i] = b[y1 + i][x1 + j];
   for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) b[i + y1][j + x1] = t[i][j];
}
template<class T>
void rotate_col(vector<vector<T>> &b, int x, int m, int rev = 0) {
   vector<T> tmp(sz(b));
   for (int i = 0; i < sz(b); i++) tmp[i] = b[i][x];
   for (int i = 0; i < sz(b); i++) b[i][x] = tmp[md(sz(b), rev ? i - m : i + m)];
}
template<class T>
void rotate_row(vector<vector<T>> &b, int y, int m, int rev = 0) {
   if (!rev) rotate(b[y].begin(), b[y].begin() + m % sz(b[y]), b[y].end());
   else rotate(b[y].begin(), b[y].begin() + (sz(b[y]) - m % sz(b[y])), b[y].end());
}