#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(2e3) + 10;
const int M = int(5e3) + 10;

int n, m;
int aggr[N];
int cost[N];
int gain[N + M];
ll dp[M + N][N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &m);
	for (int i = n; i >= 1; i--) scanf("%d", &aggr[i]);
	for (int i = n; i >= 1; i--) scanf("%d", &cost[i]);
	for (int i = 1; i <= n + m; i++) scanf("%d", &gain[i]);

	memset(dp, 0x80, sizeof dp);
	for (int a = 1; a <= n + m; a++) dp[a][0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int pile = n; pile >= 1; pile--) {
			dp[aggr[i]][pile] = max(dp[aggr[i]][pile], dp[aggr[i]][pile - 1] + gain[aggr[i]] - cost[i]);
		}
		for (int a = aggr[i], pile = n; a < n + m; a++, pile /= 2) {
			for (int _pile = 0; _pile <= pile; _pile++) {
				dp[a + 1][_pile / 2] = max(dp[a + 1][_pile / 2], dp[a][_pile] + gain[a + 1] * (_pile / 2));
			}
		}
	}

	printf("%lld\n", dp[n + m][0]);

	return 0;
}