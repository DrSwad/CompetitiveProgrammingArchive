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
		ll a, b, c, d;
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		ll x, y, x1, y1, x2, y2;
		scanf("%lld %lld %lld %lld %lld %lld", &x, &y, &x1, &y1, &x2, &y2);

		if (x1 == x2 && (a != 0 || b != 0)) puts("NO");
		else if (y1 == y2 && (c != 0 || d != 0)) puts("NO");
		else {
			if ((b - a > x2 - x) || (a - b > x - x1) || (d - c > y2 - y) || (c - d > y - y1)) puts("NO");
			else puts("YES");
		}
	}

	return 0;
}