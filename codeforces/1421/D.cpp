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
		ll x, y;
		scanf("%lld %lld", &x, &y);

		ll c[7];
		for (int i = 1; i <= 6; i++) scanf("%lld", &c[i]);

		ll left_up, right_down, both_up, both_down;

		both_up = c[1];
		both_down = c[4];

		if (x >= y) {
			left_up = c[6];
			right_down = c[5];
			both_up = min(both_up, left_up + c[2]);
			both_down = min(both_down, right_down + c[3]);
		} else {
			swap(x, y);
			left_up = c[2];
			right_down = c[3];
			both_up = min(both_up, left_up + c[6]);
			both_down = min(both_down, right_down + c[5]);
		}

		ll ans = LLONG_MAX;

		ll diff = x - y;
		ans = min(ans, diff * left_up + (y < 0 ? - y * both_down : y * both_up));
		ans = min(ans, diff * right_down + (x < 0 ? - x * both_down : x * both_up));
		if (x > 0 && x < diff) ans = min(ans, x * left_up + (diff - x) * right_down);
		if (y < 0 && y > -diff) ans = min(ans, -y * right_down + (diff + y) * left_up);

		printf("%lld\n", ans);
	}

	return 0;
}