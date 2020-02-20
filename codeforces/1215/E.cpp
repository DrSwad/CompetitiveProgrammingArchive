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

const int N = 20;

int n;
vector<int> pos[N];
ll cnt[N][N];
ll dp[1 << N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		pos[--a].push_back(i);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			for (int p : pos[i]) {
				cnt[i][j] += lower_bound(pos[j].begin(), pos[j].end(), p) - pos[j].begin();
			}
		}
	}

	for (int mask = 1; mask < 1 << N; mask++) {
		dp[mask] = LLONG_MAX;
		for (int i = 0; i < N; i++) if (mask & 1 << i) {
			ll curr = dp[mask ^ 1 << i];
			for (int j = 0; j < N; j++) if (j != i && mask & 1 << j) {
				curr += cnt[i][j];
			}
			dp[mask] = min(dp[mask], curr);
		}
	}

	printf("%lld\n", dp[(1 << N) - 1]);

	return 0;
}