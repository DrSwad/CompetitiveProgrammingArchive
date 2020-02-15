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

const int N = 53;
const int M = int(2e4) + 10;
const ll INF = ll(1e16);

int n, m, k;
int cell[N][M];
int pref_sum[N][M];
ll dp[N][M];

ll st[3 * N][4 * M];
void update(int treeI, int stI, int L, int R, int at, ll val) {
	if (at < L || R < at) return;

	if (L == R) {
		st[treeI][stI] = val;
		return;
	}

	int mid = (L + R) / 2;
	update(treeI, (stI << 1), L, mid, at, val);
	update(treeI, (stI << 1) + 1, mid + 1, R, at, val);

	st[treeI][stI] = max(st[treeI][(stI << 1)], st[treeI][(stI << 1) + 1]);
}
void update(int treeI, int at, ll val) {
	update(treeI, 1, 1, m, at, val);
}
ll query(int treeI, int stI, int L, int R, int l, int r) {
	if (r < L || R < l) return -INF;

	if (l <= L && R <= r) return st[treeI][stI];

	int mid = (L + R) / 2;
	ll q1 = query(treeI, (stI << 1), L, mid, l, r);
	ll q2 = query(treeI, (stI << 1) + 1, mid + 1, R, l, r);

	return max(q1, q2);
}
ll query(int treeI, int l, int r) {
	return query(treeI, 1, 1, m, l, r);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	fill(&st[0][0], &st[0][0] + sizeof(st) / sizeof(st[0][0]), -INF);

	scanf("%d %d %d", &n, &m, &k);
	for (int row = 1; row <= n; row++) {
		for (int col = 1; col <= m; col++) {
			scanf("%d", &cell[row][col]);
			pref_sum[row][col] = cell[row][col] + pref_sum[row][col - 1];
		}
	}

	for (int col = 1; col <= m - k + 1; col++) {
		dp[n][col] = pref_sum[n][min(col + k - 1, m)] - pref_sum[n][col - 1];
		update(3 * n, col, dp[n][col]);
		update(3 * n + 1, col, dp[n][col] - pref_sum[n][col + k - 1]);
		update(3 * n + 2, col, dp[n][col] + pref_sum[n][col - 1]);
	}

	for (int row = n - 1; row >= 1; row--) {
		for (int col = 1; col <= m - k + 1; col++) {
			ll covers = pref_sum[row][min(col + k - 1, m)] - pref_sum[row][col - 1]
						+ pref_sum[row + 1][min(col + k - 1, m)] - pref_sum[row + 1][col - 1];

			ll dp_left = -INF, dp_middle_left = -INF;
			ll dp_right = -INF, dp_middle_right = -INF;

			if (col - k >= 1) dp_left = query(3 * (row + 1), 1, col - k);
			dp_middle_left = query(3 * (row + 1) + 1, max(col - k, 1), col) + pref_sum[row + 1][col - 1];
			dp_middle_right = query(3 * (row + 1) + 2, col, min(col + k, m)) - pref_sum[row + 1][col + k - 1];
			if (col + k <= m) dp_right = query(3 * (row + 1), col + k, m);

			dp[row][col] = covers + max(max(dp_left, dp_middle_left), max(dp_right, dp_middle_right));
			update(3 * row, col, dp[row][col]);
			update(3 * row + 1, col, dp[row][col] - pref_sum[row][col + k - 1]);
			update(3 * row + 2, col, dp[row][col] + pref_sum[row][col - 1]);
		}
	}

	ll ans = 0LL;
	for (int col = 1; col <= m - k + 1; col++) ans = max(ans, dp[1][col]);
	printf("%lld\n", ans);

	return 0;
}