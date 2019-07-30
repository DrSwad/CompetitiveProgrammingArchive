#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<ll, ll> ii;
 
#define x first
#define y second
 
const int N = 2e5 + 10;
const ll MAX_X = 1e13;
 
int n, k;
ll a[N], b[N];
vector<ii> Ends[N];
 
bool check(ll x) {
	for (int i = 0; i <= k; i++) Ends[i].clear();

	for (int i = 1; i <= n; i++) {
		Ends[min(a[i] / b[i], (ll)k)].push_back({a[i] % b[i], b[i]});
	}

	int c = 0;
 
	for (int d = 0; d <= k - 2; d++) {
		c++;
		
		for (ii p : Ends[d]) {
			ll rem = p.x;
			ll _b = p.y;
	 
			while (rem < _b) {
				if (c == 0) return false;

				rem += x;
				c--;
			}
	 
			Ends[min(d + rem / _b, (ll)k)].push_back({rem % _b, _b});
		}
	}
 
	return true;
}
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> k;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);
 
	ll L = 0, R = MAX_X;
	while (L != R) {
		ll mid = (L + R) / 2;
		if (check(mid)) R = mid;
		else L = mid + 1;
	}
 
	if (check(L)) cout << L << endl;
	else cout << -1 << endl;
 
	return 0;
}