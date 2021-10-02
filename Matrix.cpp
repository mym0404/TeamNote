typedef vvl matrix;
ostream &operator<<(ostream &os, const matrix &mat) {
   for (auto vec: mat) {
      for (auto i: vec) {
         cout << i << " ";
      }
      cout << endl;
   }
   return os;
}
matrix operator*(const matrix &a, const matrix &b) {
   int aRow = a.size();
   int aColumn = a[0].size();
   int bRow = b.size();
   int bColumn = b[0].size();

   if (aColumn != bRow)
      throw std::length_error("column of a is not equal to row of b");

   matrix c(aRow, vl(bColumn, 0));

   for (int i = 0; i < aRow; ++i) {
      for (int j = 0; j < bColumn; ++j) {
         for (int k = 0; k < aColumn; k++) {
            c[i][j] += a[i][k] * b[k][j];
//            c[i][j] %= mod;
         }
      }
   }

   return c;
}
matrix identity(ll n) {
   matrix ret(n, vl(n));
   for (int i = 0; i < n; i++) ret[i][i] = 1;
   return ret;
}
matrix pow_mat(matrix a, ll n) {
   matrix ret = identity(sz(a));
   while (n) {
      if (n & 1) ret = ret * a;
      a = a * a;
      n >>= 1;
   }
   return ret;
}

