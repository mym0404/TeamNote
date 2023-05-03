vector<ll> p(11, 1);
// count num occurrence in [1, n] of specific place
ll cnt(ll n, ll place, ll num) {
   if (p[1] & 1) for (int k = 1; k < sz(p); k++) p[k] = p[k - 1] * 10;
   ll cycle = n / p[place + 1];
   ll ret = cycle * p[place];
   ll place_digit = n / p[place] % 10;
   if (!num && !ret) return 0; // if leading zero
   if (place_digit > num) ret += p[place];
   else if (place_digit == num) ret += n % p[place] + 1;
   if (num == 0) ret -= p[place];
   return ret;
}