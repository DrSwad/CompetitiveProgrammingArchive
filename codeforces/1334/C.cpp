#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(3e5) + 10;


int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("bfout", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		scanf("%d", &n);

		vector<ll> a(n), b(n);
		for (int i = 0; i < n; i++) scanf("%lld %lld", &a[i], &b[i]);

		ll ans = 0LL, mini = LLONG_MAX;
		for (int i = 0; i < n; i++) {
			ans += max(0LL, a[i] - b[(i - 1 + n) % n]);
			a[i] = min(a[i], b[(i - 1 + n) % n]);
			mini = min(mini, a[i]);
		}
		ans += mini;

		printf("%lld\n", ans);
	}

	return 0;
}