#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 2e5 + 10;
const ll MAX_X = 1e13;

int n, k;
ll a[N], b[N];

bool check(ll x) {
	auto cmp = [](const pair<ll, ii>& p1, const pair<ll, ii>& p2) {
		return p1.x > p2.x;
	};
	priority_queue<pair<ll, ii>, vector<pair<ll, ii>>, decltype(cmp)> pq(cmp);

	for (int i = 1; i <= n; i++) {
		pq.push({a[i] / b[i], {a[i] % b[i], b[i]}});
	}

	for (int d = 0; d <= k - 1; d++) {
		pair<ll, ii> top = pq.top();
		pq.pop();
		ll day = top.x;
		ll rem = top.y.x;
		ll _b = top.y.y;

		if (day < d) return false;

		rem = rem + x;

		pq.push({day + rem / _b, {rem % _b, _b}});
	}

	return true;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &b[i]);

	ll L = 0, R = MAX_X;
	while (L != R) {
		ll mid = (L + R) / 2;
		if (check(mid)) R = mid;
		else L = mid + 1;
	}

	if (check(L)) cout << L << endl;
	else cout << -1 << endl;

	return 0;
}