#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, int> pli;

#define x first
#define y second

const int K = 1e4 + 10;
const int LOG_N = 70;
const int SQRT_N = 4e7 + 10;
const int MOD = 1e9 + 7;

ll n;
int k;
vector<pli> divs;
int inv[LOG_N];
int dp[LOG_N][LOG_N];
ll ans;

void go(int at, int carry_num, int carry_cnt) {
	if (at == divs.size()) {
		ans = (ans + carry_num * 1LL * carry_cnt % MOD) % MOD;
		return;
	}

	ll p = divs[at].x;
	int exp = divs[at].y;

	for (int e = 0; e <= exp; e++) {
		go(at + 1, carry_num, carry_cnt * 1LL * dp[exp + 1][e + 1] % MOD);
		carry_num = carry_num * 1LL * p % MOD;
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;

	if (n == 1) {
		printf("1\n");
		return 0;
	}

	for (int i = 2; i < SQRT_N; i++) {
		int exp = 0;
		while (n % i == 0) {
			exp++;
			n /= i;
		}
		if (exp > 0) divs.push_back({i, exp});
	}
	if (n > 1) divs.push_back({n, 1});

	inv[1] = 1;
	for (int i = 2; i < LOG_N; i++) {
		inv[i] = (MOD - MOD / i) * 1LL * inv[MOD % i] % MOD;
	}

	for (int _k = 0; _k <= k; _k++) {
		for (int i = 1; i < LOG_N; i++) {
			for (int j = 1; j <= i; j++) {
				if (_k == 0) dp[i][j] = 1;
				else {
					dp[i][j] = (inv[i] * 1LL * dp[i][j] + dp[i - 1][j]) % MOD;
				}
			}
		}
	}

	for (int i = LOG_N - 1; i >= 1; i--) {
		for (int j = 1; j <= i; j++) {
			dp[i][j] = (dp[i][j] - dp[i - 1][j] + MOD) % MOD;
		}
	}

	go(0, 1, 1);

	cout << ans << endl;

	return 0;
}