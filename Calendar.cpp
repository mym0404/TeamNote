struct calendar {
   int sy;
   calendar(int sy = 1600) : sy(sy) {}
   int idx(int y, int m, int d) {
      return (y - sy) * 365 + count_leap(sy, y - 1) + count_days_month(1, m - 1, leap(y)) + d - 1;
   }
   array<int, 3> ymd(int i) {
      array<int, 3> ret;
      ret[0] = sy + i / 365.2422;
      while (idx(ret[0], 1, 1) - 1 >= i)ret[0]--;
      while (idx(ret[0] + 1, 1, 1) <= i)ret[0]++;
      i -= (ret[0] - sy) * 365 + count_leap(sy, ret[0] - 1);
      ret[1] = max(1, i / 31);
      while (count_days_month(1, ret[1], leap(ret[0])) <= i) ret[1]++;
      i -= count_days_month(1, ret[1] - 1, leap(ret[0]));
      ret[2] = i + 1;
      return ret;
   }
   int advance_month(int i) {
      auto[y, m, d] = ymd(i);
      int nm = m % 12 + 1;
      if (month_cnt[m] <= month_cnt[nm]) return m == 12 ? idx(y + 1, 1, d) : idx(y, m + 1, d);
      else return -1;
   }

   static constexpr int month_cnt[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
      month_psum[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
   static int count_days_month(int m1, int m2, bool is_leap) {
      if (m1 > m2) return 0;
      return month_psum[m2] - month_psum[m1 - 1] + (is_leap && m1 <= 2 && 2 <= m2);
   }
   static int count_leap(int y1, int y2) {
      if (y1 > y2) return 0;
      return y2 / 4 - (y1 - 1) / 4 - (y2 / 100 - (y1 - 1) / 100) + y2 / 400 - (y1 - 1) / 400;
   }
   static bool leap(int y) {
      if (y % 100 == 0) return y % 400 == 0;
      return y % 4 == 0;
   }
   static int day_of_week(int y, int m, int d) {
      if (m < 3) y--;
      m = (m + 9) % 12 + 1;
      int _c = y / 100, _y = y % 100;
      return ((d + int(2.6 * m - 0.2) - 2 * _c + _y + _c / 4 + _y / 4) % 7 + 7) % 7;
   }
};
