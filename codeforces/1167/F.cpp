#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 5e5 + 10, MOD = 1e9 + 7;

int n;
int a[N];

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

int st[4 * N];
void init() {
	for (int i = 0; i < 4 * N; i++) st[i] = 0;
}
void update(int stI, int L, int R, int at, int val) {
	if ((L > at) || (R < at)) return;

	if (L == R) {
		st[stI] = val;
		return;
	}

	int mid = (L + R) / 2;
	update((stI << 1), L, mid, at, val);
	update((stI << 1) + 1, mid + 1, R, at, val);

	st[stI] = norm(st[(stI << 1)] + st[(stI << 1) + 1]);
}
void update(int at, int val) {
	update(1, 1, n, at, val);
}
int query(int stI, int L, int R, int l, int r) {
	if ((L > r) || (R < l)) return 0;

	if ((L >= l) && (R <= r)) return st[stI];

	int mid = (L + R) / 2;
	int q1 = query((stI << 1), L, mid, l, r);
	int q2 = query((stI << 1) + 1, mid + 1, R, l, r);

	return norm(q1 + q2);
}
int query(int l, int r) {
	return query(1, 1, n, l, r);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	ll ans = 0LL;
	for (int i = 1; i <= n; i++) {
		ans += mul(mul(a[i], i), n - i + 1);
		ans = norm(ans);
	}

	vector<int> cmp;
	for (int i = 1; i <= n; i++) cmp.push_back(a[i]);
	sort(cmp.begin(), cmp.end());
	cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());

	for (int i = 1; i <= n; i++) {
		int at = lower_bound(cmp.begin(), cmp.end(), a[i]) - cmp.begin() + 1;

		ans += mul(a[i], mul(n - i + 1, query(1, at)));
		ans = norm(ans);

		update(at, i);
	}

	init();

	for (int i = n; i >= 1; i--) {
		int at = lower_bound(cmp.begin(), cmp.end(), a[i]) - cmp.begin() + 1;

		ans += mul(a[i], mul(i, query(1, at)));
		ans = norm(ans);

		update(at, n - i + 1);
	}

	cout << ans << endl;

	return 0;
}