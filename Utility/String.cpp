// region string function
vector<string> split(string raw, string delimiter = " ") {
   vector<string> ret;
   size_t pos = 0;
   while ((pos = raw.find(delimiter)) != std::string::npos) {
      ret.pb(raw.substr(0, pos));
      raw.erase(0, pos + delimiter.length());
   }
   ret.pb(raw);
   return ret;
}
template<class T>
vector<T> spliti(string raw, string delimiter = " ") {
   const auto &parsed = split(raw, delimiter);
   vector<T> ret(sz(parsed));
   transform(all(parsed), begin(ret), [](const auto &_) { return stoll(_); });
   return ret;
}
string replace(const string &s, const string &from, const string &to) {
   string ret;
   for (int i = 0; i < sz(s); i++) {
      if (sz(s) - i >= sz(from) && s.substr(i, sz(from)) == from) ret += to, i += sz(from) - 1;
      else ret += s[i];
   }
   return ret;
}
string re_replace(const string &s, const string &from, const string &to) {
   return regex_replace(s, regex(from), to);
}
// can be slow
string re_find(const string &s, const string &t) {
   smatch match;
   assert(regex_search(s, match, regex(t)));
   return match[0];
}
// endregion