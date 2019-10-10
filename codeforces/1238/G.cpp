#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> pii;

#define x first
#define y second

const int N = 5e5 + 10;

int n, m, c, c0;
int t[N], a[N], b[N];
map<int, int> mp;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	while (q--) {
		scanf("%d %d %d %d", &n, &m, &c, &c0);

		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &t[i], &a[i], &b[i]);
		}
		n++;
		t[n] = m;
		a[n] = 0;
		b[n] = 0;

		vector<int> order(n);
		iota(order.begin(), order.end(), 1);
		sort(order.begin(), order.end(), [](int i, int j) {return t[i] < t[j];});

		ll ans = 0LL;
		mp[0] = c0;
		int at = 0;
		int curr = c0;

		for (int i : order) {
			int dist = t[i] - at;
			at = t[i];

			while (dist > 0 && !mp.empty()) {
				int cost = mp.begin()->x;
				int cnt = mp.begin()->y;

				int take = min(dist, cnt);
				dist -= take;
				curr -= take;
				ans += take * 1LL * cost;

				mp.begin()->y -= take;
				if (mp.begin()->y == 0) mp.erase(mp.begin());
			}

			if (dist > 0) {
				ans = -1LL;
				break;
			}

			int cost = b[i];
			int cnt = a[i];

			int take = min(cnt, c - curr);
			curr += take;

			while (take < cnt && !mp.empty() && mp.rbegin()->x > cost) {
				int _take = min(cnt - take, mp.rbegin()->y);

				mp.rbegin()->y -= _take;
				if (mp.rbegin()->y == 0) mp.erase(--mp.end());
				take += _take;
			}

			mp[cost] += take;
		}

		printf("%lld\n", ans);

		mp.clear();
	}

	return 0;
}