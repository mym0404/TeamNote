typedef complex<double> cpx;
const double PI = acos(-1);
void fft(vector<cpx> &F, bool inv) {
   int N = sz(F);
   for (int i = 1, j = 0; i < N; ++i) {
      int B = N >> 1;
      while (!((j ^= B) & B)) B >>= 1;
      if (i < j) swap(F[i], F[j]);
   }
   for (int i = 1; i < N; i <<= 1) {
      double x = inv ? PI / i : -PI / i;
      cpx W = {cos(x), sin(x)};
      for (int j = 0; j < N; j += i << 1) {
         cpx a = {1, 0};
         for (int k = 0; k < i; ++k) {
            cpx b = F[i + j + k] * a;
            F[i + j + k] = F[j + k] - b;
            F[j + k] += b;
            a *= W;
         }
      }
   }
   if (inv) for (int i = 0; i < N; ++i) F[i] /= N;
}
template<class T>
vector<T> conv(const vector<T> &_a, const vector<T> &_b) {
   vector<cpx> a(all(_a)), b(all(_b));
   int n = 1;
   while (n < sz(a) + 1 || n < sz(b) + 1) n <<= 1;
   n <<= 1;
   a.resize(n), b.resize(n);
   fft(a, 0), fft(b, 0);
   for (int i = 0; i < n; ++i) a[i] *= b[i];
   fft(a, 1);
   vector<T> ret(n);
   for (int i = 0; i < n; ++i) ret[i] = round(a[i].real());
   return ret;
}