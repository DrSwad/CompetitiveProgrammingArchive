#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10, MAX = 1e9;

int n;
ll k;
int a[N];
ll pref[N];
int ans = INT_MAX;

int solve(int at) {
	ll needLeft = at * 1LL * a[at] - pref[at];
	if (needLeft > k) return INT_MAX;

	int L = a[at], R = a[n];
	while (L != R) {
		int mid = (L + R) / 2;
		int pos = lower_bound(a + 1, a + n + 1, mid) - a;
		ll needRight = (pref[n] - pref[pos - 1]) - mid * 1LL * (n - pos + 1);

		if (needRight <= k - needLeft) R = mid;
		else L = mid + 1;
	}

	return L - a[at];
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + a[i];
	for (int i = 1; i <= n; i++) ans = min(ans, solve(i));

	reverse(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = MAX - a[i];
		pref[i] = pref[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++) ans = min(ans, solve(i));

	cout << ans << endl;

	return 0;
}