#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, int> li;

#define x first
#define y second

const int N = 2e5 + 10;
const ll MAX_X = 1e13;

int n, k;
ll a[N], b[N];

bool check(ll x) {
	auto cmp = [](const li& p1, const li& p2) {
		return p1.x > p2.x;
	};
	priority_queue<li, vector<li>, decltype(cmp)> pq(cmp);

	for (int i = 1; i <= n; i++) {
		pq.push({a[i] / b[i], i});
	}

	vector<ll> _a(a, a + n + 1);

	for (int d = 0; d <= k - 1; d++) {
		li top = pq.top();
		pq.pop();
		ll day = top.x;
		int id = top.y;

		if (day < d) return false;

		_a[id] = _a[id] % b[id] + x;

		pq.push({day + _a[id] / b[id], id});
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