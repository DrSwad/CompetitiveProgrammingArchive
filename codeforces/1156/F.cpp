#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 5005, MOD = 998244353;

int n;
int inv[N];
int fact[N];
int invFact[N];
int cnt[N];
ll dp[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		cnt[a]++;
	}

	inv[1] = 1;
	for (int i = 2; i < N; i++) {
		inv[i] = ((MOD - MOD / i) * 1LL * inv[MOD % i]) % MOD;
	}

	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = (fact[i - 1] * 1LL * i) % MOD;
	}

	invFact[0] = 1;
	for (int i = 1; i < N; i++) {
		invFact[i] = (invFact[i - 1] * 1LL * inv[i]) % MOD;
	}

	ll good = 0LL;

	dp[0] = 1;
	int rem = n;

	for (int i = 1; i < N; i++) {
		if (cnt[i] == 0) continue;

		rem -= cnt[i];
		ll perm2 = (cnt[i] * 1LL * (cnt[i] - 1)) % MOD;

		for (int j = 0; j < N; j++) {
			int tot = rem + (cnt[i] - 2) + j;
			if (tot < 0 || tot > n) continue;

			good += (dp[j] * 1LL * perm2 % MOD) * 1LL * fact[tot] % MOD;
			good %= MOD;
		}

		for (int j = N - 1; j >= 0; j--) {
			ll newVal = 0;
			if (j >= cnt[i]) newVal += dp[j - cnt[i]];
			if (j >= cnt[i] - 1) newVal += (cnt[i] * 1LL * dp[j - (cnt[i] - 1)]) % MOD;
			newVal %= MOD;
			dp[j] = newVal;
		}
	}

	ll ans = (good * 1LL * invFact[n]) % MOD;

	cout << ans << endl;

	return 0;
}