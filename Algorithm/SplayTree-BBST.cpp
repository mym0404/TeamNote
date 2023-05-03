struct node {
   node *l = 0, *r = 0, *p = 0;
   int val, sum, cnt = 1, flip = 0;
   node(int val) : val(val), sum(val) {}
};
struct splay_tree {
   const int inf = numeric_limits<int>::max() >> 1;
   node *root = 0;

   void insert(int val) {
      node *x = root, **xx = 0;
      if (!x) {
         root = new node(val);
         return;
      }
      while (!xx) {
         if (val == x->val) return;
         if (val < x->val) {
            if (x->l)x = x->l;
            else xx = &x->l;
         } else {
            if (x->r)x = x->r;
            else xx = &x->r;
         }
      }
      node *c = new node(val);
      *xx = c;
      c->p = x;
      splay(c);
   }

   bool find(int val) {
      node *x = root;
      if (!x) return 0;
      while (x) {
         if (val == x->val) break;
         else if (val < x->val) {
            if (!x->l) break;
            x = x->l;
         } else {
            if (!x->r) break;
            x = x->r;
         }
      }
      splay(x);
      return x->val == val;
   }

   void erase(int val) {
      if (!find(val)) return;
      node *x = root;
      if (x->l && x->r) {
         root = x->l;
         root->p = 0;
         node *c = root;
         while (c->r)c = c->r;
         c->r = x->r;
         c->r->p = c;
      } else if (x->l) {
         root = x->l;
         root->p = 0;
      } else if (x->r) {
         root = x->r;
         root->p = 0;
      } else {
         root = 0;
      }
      delete x;
   }

   node *gather(int nl, int nr) {
      kth(nr + 1);
      node *tmp = root;
      kth(nl - 1);
      splay(tmp, root);
      return root->r->l;
   }

   int kth(int k) { // 1-based
      node *x = root;
      while (1) {
         while (x->l && x->l->cnt > k) x = x->l;
         if (x->l)k -= x->l->cnt;
         if (!k--)break;
         x = x->r;
      }
      splay(x);
      return root->val;
   }

   void splay(node *x, node *g = 0) {
      while (x->p != g) {
         node *p = x->p;
         if (p->p == g) {
            rotate(x);
            break;
         }
         node *pp = p->p;
         if ((x == p->l) == (p == pp->l))rotate(p), rotate(x);
         else rotate(x), rotate(x);
      }
      if (!g) root = x;
   }

   void rotate(node *x) {
      node *p = x->p, *c;
      if (!p) return;
      if (x == p->l) {
         p->l = c = x->r;
         x->r = p;
      } else {
         p->r = c = x->l;
         x->l = p;
      }
      x->p = p->p;
      p->p = x;
      if (c) c->p = p;

      if (!x->p)root = x;
      else if (p == x->p->l) x->p->l = x;
      else x->p->r = x;
      update(p), update(x);
   }

   node *add_l(node *x, int val) {
      node *c = new node(val);
      c->p = x;
      return x->l = c;
   }
   node *add_r(node *x, int val) {
      node *c = new node(val);
      c->p = x;
      return x->r = c;
   }

   void update(node *x) {
      x->cnt = 1, x->sum = x->val;
      if (x->l) x->cnt += x->l->cnt, x->sum += x->l->sum;
      if (x->r) x->cnt += x->r->cnt, x->sum += x->r->sum;
   }

   void traverse(node *x) {
      if (!x) return;
      traverse(x->l);
      cout << x->val << endl;
      traverse(x->r);
   }
};