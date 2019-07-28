#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 2e5 + 10, MOD = 998244353;

int n, k;
vector<int> v[2];
ll dp[N][2];
ll ans = 1LL;

void go(vector<int>& v) {
	int n = v.size();
	for (int i = 0; i < n; i++) {
		if (i < n - 1 && v[i] == -1) continue;

		int st = v[i], en;
		int at = i, cnt = 0;

		do {
			if (v[at] == -1) cnt++;
			at--;
		} while (v[at] == -1 && at >= 0);

		if (at < 0) en = -1;
		else en = v[at];

		ll curr = 1LL;

		if (st == -1 || en == -1) {
			for (int j = 1; j <= cnt - 1; j++) {
				curr *= (k - 1);
				curr %= MOD;
			}

			if (cnt) curr *= (st == -1 && en == -1 ? k : k - 1);
			curr %= MOD;
		}
		else curr = dp[cnt + 2][st == en];

		ans *= curr;
		ans %= MOD;
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;

	dp[2][0] = 1;
	dp[2][1] = 0;
	for (int i = 3; i < N; i++) {
		dp[i][0] = (dp[i - 1][0] * (k - 2) + dp[i - 1][1]) % MOD;
		dp[i][1] = dp[i - 1][0] * (k - 1) % MOD;
	}

	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);

		v[i % 2].push_back(a);
	}

	go(v[0]);
	go(v[1]);

	cout << ans << endl;

	return 0;
}