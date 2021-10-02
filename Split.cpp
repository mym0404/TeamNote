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
