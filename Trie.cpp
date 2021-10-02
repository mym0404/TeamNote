class trie {
private:
   const static int range = 26;
   const static char first_child = 'a';
public:
   bool output = false;
   trie *go[range];
   trie() { memset(go, 0, sizeof go); }
   ~trie() {
      for (int i = 0; i < range; i++)
         delete go[i];
   }
   void insert(char *s) {
      if (s[0] == '\0') {
         output = true;
         return;
      }
      int idx = s[0] - first_child;
      if (!go[idx]) go[idx] = new trie();
      go[idx]->insert(s + 1);
   }
   bool find(char *s) {
      if (s[0] == '\0') return output;
      int idx = s[0] - first_child;
      if (!go[idx]) return false;
      return go[idx]->find(s + 1);
   }
};
