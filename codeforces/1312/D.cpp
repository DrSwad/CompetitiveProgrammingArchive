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

int n, m;
int inv[N];
int fact[N];
int ifact[N];
int p2;

int nCr(int n, int r) {
	if (n < r) return 0;
	return fact[n] * 1LL * ifact[r] % MOD * ifact[n - r] % MOD;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &m);

	inv[1] = fact[0] = ifact[0] = p2 = 1;
	for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * 1LL * (MOD - MOD / i) % MOD;
	for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * 1LL * i % MOD;
	for (int i = 1; i < N; i++) ifact[i] = ifact[i - 1] * 1LL * inv[i] % MOD;
	for (int i = 1; i <= n - 3; i++) p2 = p2 * 2LL % MOD;

	ll ans = 0LL;
	for (int i = 0; i < m - 1; i++) {
		ans = (ans + nCr(m - 1, n - 2) - nCr(i, n - 2) + MOD) % MOD;
	}
	ans = ans * 1LL * p2 % MOD;

	printf("%lld\n", ans);

	return 0;
}