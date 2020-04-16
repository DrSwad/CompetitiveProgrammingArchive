#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = 3005;
const int MOD = 998244353;

int n, m;
char s[N], t[N];
int dp[N][N];
int dp2[N][N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf(" %s %s", s + 1, t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);

	for (int j = 0; j < N; j++) dp[0][j] = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j + i - 1 <= m; j++) {
			if (s[i] == t[j + i - 1]) (dp[i][j] += dp[i - 1][j]) %= MOD;
			if (s[i] == t[j]) (dp[i][j] += dp[i - 1][j + 1]) %= MOD;
		}
	}

	for (int j = 1; j <= n + 1; j++) dp2[0][j] = n + 2 - j;
	for (int i = 1; i <= m; i++) {
		for (int j = n; j >= 1; j--) {
			dp2[i][j] = (dp2[i][j + 1] + (t[i] == s[j] ? dp2[i - 1][j + 1] : 0)) % MOD;
		}
	}

	int ans = 0;

	for (int i = 0, p2 = 1; i <= n - m; i++, (p2 *= 2) %= MOD) {
		(ans += p2 * 1LL * (dp2[m][i + 1] - dp2[m][i + 2] + MOD) % MOD) %= MOD;
	}

	for (int last_at = 1; last_at <= min(n, m); last_at++) {
		int extra = m - last_at;
		int extra_ways = dp2[extra][last_at + 1];
		int dp_ways = 0;
		if (last_at == 0) dp_ways = 1;
		else if (s[last_at] == t[m]) dp_ways = dp[last_at - 1][extra + 1];
		(ans += extra_ways * 1LL * dp_ways % MOD) %= MOD;
	}

	cout << ans << endl;

	return 0;
}