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
const int LOGN = 22;


int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		scanf("%d", &n);

		vector<ll> a(n), b(n);
		for (int i = 0; i < n; i++) scanf("%lld %lld", &a[i], &b[i]);

		vector<vector<pair<int, ll>>> jump(LOGN, vector<pair<int, ll>>(n));

		jump[0][0].y = a[0];
		for (jump[0][0].x = 1; jump[0][0].x < n; jump[0][0].x++) {
			if (a[jump[0][0].x] > b[jump[0][0].x - 1]) break;
		}

		for (int i = n - 1; i > 0; i--) {
			jump[0][i].y = a[i];
			if (a[(i + 1) % n] > b[i]) jump[0][i].x = 1;
			else {
				jump[0][i].x = min(n, 1 + jump[0][(i + 1) % n].x);
			}
		}

		for (int len = 1; len < LOGN; len++) {
			for (int i = 0; i < n; i++) {
				if (jump[len - 1][i].x >= n) {
					jump[len][i] = jump[len - 1][i];
				}
				else {
					int nxt = (i + jump[len - 1][i].x) % n;
					jump[len][i].x = min(n, jump[len - 1][i].x +
									 jump[len - 1][nxt].x);
					jump[len][i].y = jump[len - 1][i].y +
									 jump[len - 1][nxt].y -
									 b[(nxt - 1 + n) % n];
				}
			}
		}

		ll ans = LLONG_MAX;

		for (int i = 0; i < n; i++) {
			ll curr = b[(i - 1 + n) % n];
			int moved = 0, jump_len = LOGN - 1;

			while (moved + jump[0][(i + moved) % n].x < n) {
				while (moved + jump[jump_len][(i + moved) % n].x >= n) jump_len--;

				curr += jump[jump_len][(i + moved) % n].y - b[(i + moved - 1 + n) % n];
				moved += jump[jump_len][(i + moved) % n].x;
			}

			curr += jump[0][(i + moved) % n].y - b[(i + moved - 1 + n) % n];
			ans = min(ans, curr);
		}

		printf("%lld\n", ans);
	}

	return 0;
}