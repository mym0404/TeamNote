struct aho {
   const static int range = 26, offset = 'a';
   int output = 0;
   aho *go[range], *fail;
   aho() { memset(go, 0, sizeof go), fail = 0; }
   ~aho() { for (int i = 0; i < range; i++) delete go[i]; }
   void insert(char *s) {
      if (s[0] == '\0') {
         output = 1;
         return;
      }
      int c = s[0] - offset;
      if (!go[c]) go[c] = new aho();
      go[c]->insert(s + 1);
   }
   void construct() {
      aho *root = this;
      queue<aho *> q;
      q.push(root);
      while (sz(q)) {
         aho *cur = q.front();
         q.pop();
         for (int c = 0; c < range; c++) {
            aho *to = cur->go[c];
            if (!to) continue;
            if (cur == root) {
               to->fail = root;
            } else {
               aho *tmp = cur->fail;
               while (tmp != root && !tmp->go[c]) tmp = tmp->fail;
               if (tmp->go[c]) tmp = tmp->go[c];
               to->fail = tmp;
               if (to->fail->output) to->output = 1;
            }
            q.push(to);
         }
      }
   }
   bool find(const string &s) {
      aho *root = this, *cur = root;
      for (auto _c: s) {
         int c = _c - offset;
         while (cur != root && !cur->go[c]) cur = cur->fail;
         if (cur->go[c]) cur = cur->go[c];
         if (cur->output) return true;
      }
      return false;
   }
};
