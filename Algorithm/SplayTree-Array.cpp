struct node {
   node *l = 0, *r = 0, *p = 0;
   int val, sum, cnt = 1, lazy = 0, flip = 0, mx, mn, dummy = 0;
   node(int val) : val(val), sum(val), mx(val), mn(val) {}
};
struct splay_tree {
   const int inf = numeric_limits<int>::max() >> 1;
   node *root = 0;
   vector<node *> ptr;
   void init(const vector<int> &arr) { // 0-based
      int n = sz(arr);
      ptr.resize(n + 1);
      node *x = root = new node(-inf);
      for (int i = 1; i <= n; i++) ptr[i] = x = add_r(x, arr[i - 1]);
      x->r = add_r(x, inf);
      root->dummy = x->r->dummy = 1;
      for (int i = n; i >= 1; i--) update(ptr[i]);
      splay(ptr[(n + 1) / 2]);
   }
   void init(int n, int s = 0) {
      vi a(n);
      iota(all(a), s);
      init(a);
   }
   void shift(int l, int r, int s) { // 1-based, to right
      s = md(r - l + 1, s);
      if (!s) return;
      flip(l, r), flip(l, l + s - 1), flip(l + s, r);
   }
   void flip(int nl, int nr) { // 1-based
      node *x = gather(nl, nr);
      x->flip ^= 1;
   }
   void propagate(node *x) {
      if (x->flip) swap(x->l, x->r);
      x->val += x->lazy;
      if (x->l) {
         if (x->flip) x->l->flip ^= 1;
         x->l->lazy += x->lazy;
         x->l->sum += x->l->cnt * x->lazy;
         x->l->mn += x->lazy;
         x->l->mx += x->lazy;
      }
      if (x->r) {
         if (x->flip) x->r->flip ^= 1;
         x->r->lazy += x->lazy;
         x->r->sum += x->r->cnt * x->lazy;
         x->r->mn += x->lazy;
         x->r->mx += x->lazy;
      }
      x->lazy = x->flip = 0;
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
      propagate(x);
      while (1) {
         while (x->l && x->l->cnt > k) x = x->l, propagate(x);
         if (x->l)k -= x->l->cnt;
         if (!k--)break;
         x = x->r, propagate(x);
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
      propagate(p), propagate(x);
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
   void update(node *x) {
      x->cnt = 1;
      x->sum = x->mn = x->mx = x->val;
      if (x->l) {
         x->cnt += x->l->cnt;
         x->sum += x->l->sum;
         x->mn = min(x->mn, x->l->mn);
         x->mx = max(x->mx, x->l->mx);
      }
      if (x->r) {
         x->cnt += x->r->cnt;
         x->sum += x->r->sum;
         x->mn = min(x->mn, x->r->mn);
         x->mx = max(x->mx, x->r->mx);
      }
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
   void inorder(node *x) {
      propagate(x);
      if (x->l)inorder(x->l);
      if (!x->dummy) cout << x->val << ' ';
      if (x->r)inorder(x->r);
   }
};