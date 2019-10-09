#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10, M = 20;

int n, m;
char s[N];
int cost[M][M];
ll dp[1 << M];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> m;
	scanf("%s", s);

	for (int i = 0; i < n - 1; i++) {
		cost[s[i] - 'a'][s[i + 1] - 'a']++;
		cost[s[i + 1] - 'a'][s[i] - 'a']++;
	}

	for (int mask = 1; mask < 1 << m; mask++) {
		dp[mask] = LLONG_MAX;
		int pos = __builtin_popcount(mask);
		for (int last = 0; last < m; last++) if (mask & 1 << last) {
			ll add = 0;
			for (int bit = 0; bit < m; bit++) if (bit != last) {
				if (mask & 1 << bit) add += pos * 1LL * cost[bit][last];
				else add -= pos * 1LL * cost[bit][last];
			}
			dp[mask] = min(dp[mask], dp[mask ^ 1 << last] + add);
		}
	}

	cout << dp[(1 << m) - 1] << endl;

	return 0;
}