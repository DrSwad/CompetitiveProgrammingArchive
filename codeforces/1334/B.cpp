#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		ll x;
		scanf("%d %lld", &n, &x);

		vector<ll> a(n);
		for (int i = 0; i < n; i++) scanf("%lld", &a[i]);

		sort(a.begin(), a.end(), greater<ll>());

		int i;
		ll sum = 0LL;
		for (i = 0; i < n; i++) {
			if (sum + a[i] < x * (i + 1)) break;
			sum += a[i];
		}

		printf("%d\n", i);
	}

	return 0;
}