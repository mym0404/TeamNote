#ifndef CPP__DEBUG_H
#define CPP__DEBUG_H
template<size_t S>
string to_string(const bitset<S> &x) { return x.to_string(); }
string to_string(const string &x) { return '"' + x + '"'; }
string to_string(char x) { return string{'\'', x, '\''}; }
string to_string(bool x) { return x ? "true" : "false"; }
template<class H, class T>
string to_string(const pair<H, T> &x) { return "(" + to_string(x.fi) + ", " + to_string(x.se) + ")"; }
template<class T>
string to_string(T x) {
   string ret = "[";
   for (const auto &i: x) ret += to_string(i) + ", ";
   if (sz(ret) > 1) ret = ret.substr(0, sz(ret) - 2);
   return ret += "]";
}
string to_string(const char *x) { return {x}; }
string to_string() { return ""; }
template<class H, class... T>
string to_string(H h, T... t) { return to_string(h) + ", " + to_string(t...); }
#define debug(...) sizeof( (char[]){#__VA_ARGS__} ) == 1 ? cerr << "--------------------\n" \
: cerr << "[" << #__VA_ARGS__ << "]: " << to_string(__VA_ARGS__) << '\n'
#endif //CPP__DEBUG_H
