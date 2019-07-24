#include <bits/stdc++.h>

using namespace std;

#define debug(a) cout << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

const int N = 2e5 + 10, MOD = 1e9 + 7;

int n;
int l[N];
int r[N];
int q[N];
int p[N];

int norm(ll a) {
	a %= MOD;
	if (a < 0) a += MOD;
	return a;
}
int norm(int a) {
	return norm((ll)a);
}
int mul(int a, int b) {
	return (a * 1LL * b) % MOD;
}
int binPow(int a, int e) {
	if (e == 0) return 1;

	if (e % 2 == 1) return mul(a, binPow(a, e - 1));

	int mid = binPow(a, e / 2);
	return mul(mid, mid);
}
int inv(int a) {
	return binPow(a, MOD - 2);
}
int consecutive(int i) {
	int pSame = norm(max(0LL,
			(min(r[i + 1], min(r[i], r[i - 1])) - max(l[i + 1], max(l[i], l[i - 1]))) *
			1LL *
			inv(mul(r[i + 1] - l[i + 1], mul(r[i] - l[i], r[i - 1] - l[i - 1])))
		));

	return norm(1 - q[i] - q[i + 1] + pSame);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &l[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &r[i]);
	for (int i = 0; i <= n; i++) r[i]++;

	ll sum = 0;
	for (int i = 1; i <= n; i++) {
		q[i] = norm(max(0LL,
				(min(r[i], r[i - 1]) - max(l[i], l[i - 1])) *
				1LL *
				inv(mul(r[i] - l[i], r[i - 1] - l[i - 1]))
			));

		p[i] = norm(1 - q[i]);
		sum = norm(sum + p[i]);
	}

	ll ans = 0LL;

	for (int i = 1; i <= n; i++) {
		ans = norm(ans + p[i]);

		int currSum = sum;
		for (int j = max(0, i - 1); j <= min(n, i + 1); j++) {
			currSum = norm(currSum - p[j]);
		}
		ans = norm(ans + mul(currSum, p[i]));

		if (i > 1) ans = norm(ans + consecutive(i - 1));
		if (i < n) ans = norm(ans + consecutive(i));
		
	}

	cout << ans << endl;

	return 0;
}