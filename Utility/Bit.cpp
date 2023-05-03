int bcnt(ll x) { return __builtin_popcountll(x); }
int rz(ll x) { return __builtin_ctzll(x); }
int lz(ll x) { return __builtin_clzll(x); }
int msb(ll x) { return 63 - lz(x); }