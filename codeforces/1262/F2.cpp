#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(2e5) + 10;
const int MOD = 998244353;

int n, k;
int h[N];
int inv[N];
int fact[N];
int ifact[N];

int nCk(int n, int k) {
	if (n < k) return 0;
	return fact[n] * 1LL * ifact[k] % MOD * ifact[n - k] % MOD;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &h[i]);

	int diff = 0;
	for (int i = 1; i <= n; i++) diff += h[i] != h[i % n + 1];
	int p2diff = 1;
	for (int i = 1; i <= diff; i++) p2diff = p2diff * 2LL % MOD;

	inv[1] = fact[0] = ifact[0] = 1;
	for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * 1LL * (MOD - MOD / i) % MOD;
	for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * 1LL * i % MOD;
	for (int i = 1; i < N; i++) ifact[i] = ifact[i - 1] * 1LL * inv[i] % MOD;

	ll ans = 0LL;
	int zero_ways = 1;
	int p2nonzero = p2diff;
	for (int zero_cnt = 0; zero_cnt <= diff; zero_cnt++) {
		int nonzero_cnt = diff - zero_cnt;
		int nonzero_ways = ((ll)p2nonzero - (nonzero_cnt & 1 ? 0 : nCk(nonzero_cnt, nonzero_cnt / 2)) + MOD) * 1LL * inv[2] % MOD;
		ans = (ans + zero_ways * 1LL * nCk(diff, zero_cnt) % MOD * nonzero_ways) % MOD;

		zero_ways = zero_ways * 1LL * (k - 2) % MOD;
		p2nonzero = p2nonzero * 1LL * inv[2] % MOD;
	}

	for (int i = 1; i <= n - diff; i++) ans = ans * 1LL * k % MOD;

	printf("%lld\n", ans);

	return 0;
}