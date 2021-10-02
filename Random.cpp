struct _random {
   mt19937 gen;
   _random() : gen((unsigned) chrono::steady_clock::now().time_since_epoch().count()) {}
   template<class T = int>
   T nextInt(T l = 0, T r = 32767) { return uniform_int_distribution<T>(l, r)(gen); }
   double nextDouble(double l = 0, double r = 1) { return uniform_real_distribution<double>(l, r)(gen); }
} rd;
