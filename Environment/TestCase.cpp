//region
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
#define fastio ios_base::sync_with_stdio(0);cin.tie(NULL);
#define endl "\n"
#define pb push_back
#define all(X) (X).begin(), (X).end()
#define sz(X) (int)(X).size()
#define fi first
#define se second
#define fv(X) for(auto&_:(X))cin>>_
#define fv1(X) for(int _=1;_<sz(X);_++)cin>>(X)[_]
#define fv2(X) for(auto&__:(X))fv(__)
#define lbi(X, n) int(lower_bound(all(X), n) - begin(X))
#define ubi(X, n) int(upper_bound(all(X), n) - begin(X))
#define maxi(X) max_element(all(X)) - begin(X)
#define maxe(X) *max_element(all(X))
#define mini(X) min_element(all(X)) - begin(X)
#define mine(X) *min_element(all(X))
#define acc(X) accumulate(all(X), 0LL)
#define cntt(X, x) count(all(X),x)
#define mp(a, b) make_pair((a),(b))
#define has(X, x) (find(all((X)),x)!=(X).end())
#define hass(X, x) ((X).find(x) != (X).end())
#define hasstr(X, x) (!!strstr(&(X)[0],&(x)[0]))
#define uniq(X) sort(all(X)),(X).resize(unique(all((X))) - (X).begin())
inline ll md(ll m, ll x) { return (x %= m) < 0 ? x + m : x; }
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 1
#endif
// endregion$1$

void solve() {
    $END$
}

signed main() {
    fastio
    int tt;
    cin >> tt;
    for (int t = 1; t <= tt; t++) {
        //cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}