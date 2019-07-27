#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 1e6 + 10;

int n, x;
int a[N];
int maxL, minR;
int up[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> x;

	set<int> s;
	maxL = x, minR = 1;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);

		s.insert(a[i]);

		set<int>::iterator it = s.upper_bound(a[i]);
		if (it != s.end()) {
			int lo = a[i];
			int hi = *it;

			maxL = min(maxL, hi);
			minR = max(minR, lo);

			up[lo + 1] = *s.rbegin();
		}
	}

	ll ans = 0LL;

	for (int l = 1; l <= maxL; l++) {
		if (up[l]) minR = max(minR, up[l]);

		ans += x - max(minR, l) + 1;
	}

	cout << ans << endl;

	return 0;
}