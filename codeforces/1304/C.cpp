#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	while (q--) {
		ll n, m;
		cin >> n >> m;

		bool possible = true;

		ll L = m, R = m, T = 0;
		for (int i = 1; i <= n; i++) {
			ll l, r, t;
			cin >> t >> l >> r;

			ll diff = t - T;
			R += diff;
			L -= diff;
			L = max(L, l);
			R = min(R, r);
			if (R < L) possible = false;

			T = t;
		}

		if (possible) cout << "YES\n";
		else cout << "NO\n";
	}

	return 0;
}