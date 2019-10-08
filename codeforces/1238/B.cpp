#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;

int n, r;
vector<int> a;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	while (q--) {
		scanf("%d %d", &n, &r);
		a.clear();
		a.reserve(n);
		for (int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			a.push_back(x);
		}

		sort(a.begin(), a.end());
		a.resize(unique(a.begin(), a.end()) - a.begin());

		int tot = a.size();
		ll ans = tot;

		for (int i = 0; i < tot; i++) {
			int nxt = tot - 1 - i;
			ans = min(ans, nxt + (max(0LL, a[i] - nxt * 1LL * r) + r - 1) / r);
		}

		printf("%lld\n", ans);
	}

	return 0;
}