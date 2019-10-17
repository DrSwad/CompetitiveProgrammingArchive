#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second
#define size(a) (int)a.size()

// const int N = int(1e5) + 10;
const int MOD = int(1e9) + 7;

int bigmod(int a, int e, int m) {
	ll ret = 1LL;
	ll aa = (ll)a;
	while (e) {
		if (e&1) {
			ret *= aa;
			if (ret > m)
				ret %= m;
			e--;
		}
		aa *= aa;
		e /= 2;
		if (aa > m)
			aa %= m;
	}
	return (int)ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;
	m = (bigmod(2, m, MOD) + MOD - 1) % MOD;
	cout << bigmod(m, n, MOD) << endl;

	return 0;
}