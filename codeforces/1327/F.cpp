#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(5e5) + 10;
const int MOD = 998244353;

int n, k, m;
int l[N], r[N], x[N];
vector<int> bit, min_r, dp, pow2, ans;

int solve() {
	for (int i = 1; i <= n; i++) bit[i] += bit[i - 1];
	vector<int> pref(n + 2, 0);
	for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + (bit[i] == 0);

	ans[n + 1] = 1;

	for (int i = n; i >= 1; i--) {
		dp[i] = dp[i + 1];
		if (bit[i] == 0) (dp[i] += ans[i + 1]) %= MOD;

		if (min_r[i] == 0) ans[i] = ans[i + 1] * (bit[i] == 0 ? 2 : 1) % MOD;
		else ans[i] = (dp[l[min_r[i]]] - dp[r[min_r[i]] + 1] + MOD) % MOD * 1LL * pow2[pref[l[min_r[i]] - 1] - pref[i - 1]] % MOD;
	}

	return ans[1];
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &k, &m);
	for (int i = 1; i <= m; i++) scanf("%d %d %d", &l[i], &r[i], &x[i]);

	bit.resize(n + 2);
	min_r.resize(n + 2);
	dp.resize(n + 2);
	pow2.resize(n + 2);
	ans.resize(n + 2);

	pow2[0] = 1;
	for (int i = 1; i < n + 2; i++) pow2[i] = pow2[i - 1] * 2LL % MOD;

	ll answer = 1LL;

	for (int i = 0; i < k; i++) {
		fill(bit.begin(), bit.end(), 0);
		fill(min_r.begin(), min_r.end(), 0);
		fill(dp.begin(), dp.end(), 0);
		fill(ans.begin(), ans.end(), 0);

		for (int j = 1; j <= m; j++) {
			if (x[j] & 1 << i) bit[l[j]]++, bit[r[j] + 1]--;
			else {
				if (min_r[l[j]] == 0 || r[j] < r[min_r[l[j]]]) {
					min_r[l[j]] = j;
				}
			}
		}
		int mini = 0;
		for (int i = n; i >= 1; i--) {
			if (min_r[i] != 0) {
				if (mini != 0 && r[mini] < r[min_r[i]]) min_r[i] = mini;
				else mini = min_r[i];
			}
		}

		(answer *= solve()) %= MOD;
	}

	cout << answer << endl;

	return 0;
}