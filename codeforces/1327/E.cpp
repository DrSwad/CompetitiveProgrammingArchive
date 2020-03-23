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

int n;
int p10[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	p10[0] = 1;
	for (int i = 1; i < N; i++) p10[i] = p10[i - 1] * 10LL % MOD;

	for (int i = 1; i < n; i++) {
		ll ans = 0LL;
		(ans += 2LL * 9LL * p10[n - i] % MOD) %= MOD;
		(ans += (n - 1 - i) * 81LL * p10[n - i - 1] % MOD) %= MOD;
		printf("%lld ", ans);
	}

	cout << 10 << endl;

	return 0;
}