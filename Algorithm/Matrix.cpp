typedef vi row;
typedef vector<row> mat;
ostream &operator<<(ostream &os, const mat &mat) {
   for (const auto &vec: mat) {
      for (const auto &i: vec) cout << i << " ";
      cout << endl;
   }
   cout << endl;
   return os;
}
mat operator*(const mat &a, const mat &b) {
   int aRow = a.size(), aColumn = a[0].size();
   int bRow = b.size(), bColumn = b[0].size();

   if (aColumn != bRow)
      throw std::length_error("column of a is not equal to row of b");

   mat c(aRow, row(bColumn, 0));

   for (int i = 0; i < aRow; ++i)
      for (int j = 0; j < bColumn; ++j)
         for (int k = 0; k < aColumn; k++)
            c[i][j] = md(c[i][j] + a[i][k] * b[k][j]);

   return c;
}
mat operator*(const mat &a, int b) {
   mat c = a;
   for (int i = 0; i < sz(a); ++i)
      for (int j = 0; j < sz(a[0]); ++j)
         c[i][j] = md(c[i][j] * b);
   return c;
}
mat operator+(const mat &a, const mat &b) {
   int aRow = a.size(), aColumn = a[0].size();
   int bRow = b.size(), bColumn = b[0].size();
   if (aRow != bRow || aColumn != bColumn)
      throw std::length_error("Length Error");
   mat c(aRow, row(bColumn, 0));
   for (int i = 0; i < aRow; ++i)
      for (int j = 0; j < bColumn; ++j)
         c[i][j] = md(c[i][j] + a[i][j] + b[i][j]);
   return c;
}
mat operator+(const mat &a, int b) {
   mat c = a;
   for (int i = 0; i < sz(a); ++i)
      for (int j = 0; j < sz(a[0]); ++j)
         c[i][j] = md(c[i][j] + b);
   return c;
}
mat identity(int n) {
   mat ret(n, row(n));
   for (int i = 0; i < n; i++) ret[i][i] = 1;
   return ret;
}
mat pow_mat(mat a, ll n) {
   mat ret = identity(sz(a));
   while (n) {
      if (n & 1) ret = ret * a;
      a = a * a;
      n >>= 1;
   }
   return ret;
}