#define i128 __int128_t
std::istream &operator>>(std::istream &input, i128 &v) {
   long long _v;
   input >> _v, v = _v;
   return input;
}
std::ostream &operator<<(std::ostream &dest, i128 v) {
   std::ostream::sentry s(dest);
   if (s) {
      __uint128_t tmp = v < 0 ? -v : v;
      char buffer[128];
      char *d = std::end(buffer);
      do {
         --d;
         *d = "0123456789"[tmp % 10];
         tmp /= 10;
      } while (tmp != 0);
      if (v < 0) {
         --d;
         *d = '-';
      }
      int len = std::end(buffer) - d;
      if (dest.rdbuf()->sputn(d, len) != len) dest.setstate(std::ios_base::badbit);
   }
   return dest;
}