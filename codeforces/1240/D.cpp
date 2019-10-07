#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 3e5 + 10;

int q;
int n;
int a[N];
int nxt[N];
map<int, int> nxtX[N];
int dp[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> q;
	while (q--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

		nxtX[n][a[n]] = n;

		for (int i = n - 1; i >= 1; i--) {
			if (nxtX[i + 1].find(a[i]) != nxtX[i + 1].end()) {
				nxt[i] = nxtX[i + 1][a[i]] + 1;
				swap(nxtX[i], nxtX[nxt[i]]);
			}
			nxtX[i][a[i]] = i;
		}

		ll ans = 0LL;

		for (int i = n; i >= 1; i--) {
			if (nxt[i] > 0) dp[i] = 1 + dp[nxt[i]];
			ans += dp[i];
		}

		printf("%lld\n", ans);

		for (int i = 1; i <= n + 1; i++) {
			nxt[i] = 0;
			nxtX[i].clear();
			dp[i] = 0;
		}
	}

	return 0;
}