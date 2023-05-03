void print(const vector<string> &v) {
   for (auto &s: v) cout << s << endl;
   cout << endl;
}
template<class T>
void print(const vector<vector<T>> &v) {
   for (int i = 0; i < sz(v); i++) {
      for (int j = 0; j < sz(v[i]); j++)
         cout << setfill(' ') << setw(2) << v[i][j] << " ";
      cout << endl;
   }
   cout << endl;
}
template<class T>
void print(const vector<vector<vector<T>>> &v) {
   for (int i = 0; i < sz(v); i++) {
      for (int j = 0; j < sz(v[i]); j++) {
         cout << "[";
         for (int k = 0; k < sz(v[i][j]); k++) {
            cout << v[i][j][k];
            if (k != sz(v[i][j]) - 1) cout << ",";
         }
         cout << "] ";
      }
      cout << endl;
   }
   cout << endl;
}