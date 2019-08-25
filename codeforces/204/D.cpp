#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 1e6 + 10;
const int MOD = 1e9 + 7;

int n, k;
char s[N];
int a[N];
ll pref[3][N];
ll dp[2][N];
ll pow2[N];

void go(ll dp[], int x) {
	ll bad = 0LL, bad_k = 0LL;

	for (int i = k; i <= n; i++) {
		if (a[i - k] == 2) {
			bad = bad * 2LL % MOD;
		}
		bad = (bad + dp[i - k]) % MOD;

		bad_k = (bad_k - dp[i - k] + dp[i - 1] + MOD) % MOD;

		if (pref[x ^ 1][i] - pref[x ^ 1][i - k] == 0) {
			dp[i] = (pow2[pref[2][i - k]] - bad - bad_k + 2LL * MOD) % MOD;
		}
	}
}
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> k;
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'X') a[i] = 2;
		else a[i] = (s[i] != 'B');

		for (int j = 0; j < 3; j++)
			pref[j][i] = pref[j][i - 1];

		pref[a[i]][i]++;
	}

	pow2[0] = 1;
	for (int i = 1; i <= n; i++) {
		pow2[i] = pow2[i - 1] * 2LL % MOD;
	}

	go(dp[0], 0);
	reverse(a + 1, a + n + 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j <= n / 2; j++) {
			int tmp = pref[i][j];
			pref[i][j] = pref[i][n] - pref[i][n - j];
			pref[i][n - j] = pref[i][n] - tmp;
		}
	}

	go(dp[1], 1);
	reverse(a + 1, a + n + 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j <= n / 2; j++) {
			int tmp = pref[i][j];
			pref[i][j] = pref[i][n] - pref[i][n - j];
			pref[i][n - j] = pref[i][n] - tmp;
		}
	}
	for (int i = 1; i <= n / 2; i++) {
		swap(dp[1][i], dp[1][n + 1 - i]);
	}

	ll ans = 0LL;
	ll pref = 0LL;
	for (int i = 1; i <= n; i++) {
		if (a[i - 1] == 2) {
			pref = pref * 2LL % MOD;
		}
		pref = (pref + dp[0][i - 1]) % MOD;

		ans = (ans + pref * dp[1][i]) % MOD;
	}

	cout << ans << endl;

	return 0;
}