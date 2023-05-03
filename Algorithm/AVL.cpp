template<class T>
struct node {
   node *l = 0, *r = 0, *p = 0;
   T val;
   int h = 1;
   node(T val) : val(val) {}
};
template<class T>
struct avl_tree {
   node<T> *root = 0;
   void insert(T val) { return root = insert(root, val); }
   bool have(T val) { return find(val) != 0; }
   node<T> *find(T val) {
      node<T> *cur = root;
      while (1) {
         if (!cur) return 0;
         if (cur->val == val) return cur;
         if (val < cur->val) cur = cur->l;
         else cur = cur->r;
      }
   }
   void traverse() { inorder(root); }
   void inorder(node<T> *cur) {
      if (cur == 0) return;
      inorder(cur->l);
      cout << cur->val << endl;
      inorder(cur->r);
   }
   node<T> *insert(node<T> *cur, T val) {
      if (!root) return root = new node(val);
      if (val == cur->val) return cur;
      else if (val < cur->val) {
         if (!cur->l) add_lchild(cur, val);
         else cur->l = insert(cur->l, val);
      } else {
         if (!cur->r) add_rchild(cur, val);
         else cur->r = insert(cur->r, val);
      }
      cur->h = max(height(cur->l), height(cur->r)) + 1;
      return cur = rebalance(cur);
   }
   node<T> *rebalance(node<T> *cur) {
      int bf = balance_factor(cur);
      if (bf > 1 && balance_factor(cur->l) > 0) cur = ll(cur);
      else if (bf > 1) cur = lr(cur);
      else if (bf < -1 && balance_factor(cur->r) < 0) cur = rr(cur);
      else if (bf < -1) cur = rl(cur);
      return cur;
   }
   node<T> *lr(node<T> *cur) {
      cur->l = rr(cur->l);
      return ll(cur);
   }
   node<T> *rl(node<T> *cur) {
      cur->r = ll(cur->r);
      return rr(cur);
   }
   node<T> *ll(node<T> *cur) {
      node<T> *l = cur->l;
      l->p = cur->p;
      cur->l = l->r;
      cur->p = l;
      l->r = cur;
      cur->h = max(height(cur->l), height(cur->r)) + 1;
      l->h = max(height(l->l), height(l->r)) + 1;
      return l;
   }
   node<T> *rr(node<T> *cur) {
      node<T> *r = cur->r;
      r->p = cur->p;
      cur->r = r->l;
      cur->p = r;
      r->l = cur;
      cur->h = max(height(cur->l), height(cur->r)) + 1;
      r->h = max(height(r->l), height(r->r)) + 1;
      return r;
   }
   int height(node<T> *cur) { return !cur ? 0 : cur->h; }
   int balance_factor(node<T> *cur) { return height(cur->l) - height(cur->r); }
   void add_lchild(node<T> *cur, T val) {
      cur->l = new node(val);
      cur->l->p = cur;
   }
   void add_rchild(node<T> *cur, T val) {
      cur->r = new node(val);
      cur->r->p = cur;
   }
};