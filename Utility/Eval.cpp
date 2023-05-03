template<class T>
struct _eval {
   string ops = "+-*/%()";
   bool is_op(char c) { return ops.find(c) != string::npos; }
   bool is_op(string c) { return sz(c) == 1 && is_op(c[0]); }
   T run_op(T a, T b, char op) {
      if (op == '+') return a + b;
      else if (op == '-') return a - b;
      else if (op == '*') return a * b;
      else if (op == '/') return a / b;
      else return a % b;
   }
   T run_op(T a, T b, string op) { return run_op(a, b, op[0]); }
   int op_priority(string op) {
      if (op == "*" || op == "/" || op == "%") return 3;
      else if (op == "+" || op == "-") return 2;
      else return 1;
   }
   T calc_infix(const string &s) { return calc_postfix(to_postfix(s)); }
   T calc_postfix(const vector<string> &s) {
      vector<T> t;
      for (auto &c: s) {
         if (is_op(c)) {
            T val = run_op(t[sz(t) - 2], t[sz(t) - 1], c[0]);
            t.pop_back(), t.pop_back(), t.push_back(val);
         } else {
            // Warning: long long conversion will cause crash on bigint usage
            t.push_back(stoll(c));
         }
      }
      return t[0];
   }
   vector<string> to_postfix(const vector<string> &s) {
      vector<string> ret, op;
      for (auto &c: s) {
         if (is_op(c)) {
            if (c == "(") op.push_back("(");
            else if (c == ")") {
               while (sz(op) && op.back() != "(") ret.pb(op.back()), op.pop_back();
               op.pop_back();
            } else {
               while (sz(op) && op_priority(op.back()) >= op_priority(c)) ret.pb(op.back()), op.pop_back();
               op.push_back(c);
            }
         } else {
            ret.pb(c);
         }
      }
      while (sz(op)) ret.pb(op.back()), op.pop_back();
      return ret;
   }
   vector<string> to_postfix(const string &s) { return to_postfix(parse(s)); }
   vector<string> parse(const string &s) {
      vector<string> ret;
      string tmp;
      for (int i = 0; i < sz(s); i++) {
         if (is_op(s[i])) ret.pb(string(1, s[i]));
         else if (i == sz(s) - 1 || is_op(s[i + 1])) ret.pb(tmp + s[i]), tmp = "";
         else tmp += s[i];
      }
      if (sz(ret) && ret[0] == "-") { // leading negative operator
         ret[1] = "-" + ret[1];
         ret.erase(ret.begin());
      }
      return ret;
   }
   string to_raw(const vector<string> &s) {
      string ret;
      for (auto &c: s) ret += c;
      return ret;
   }
};
_eval<ll> eval;