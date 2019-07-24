#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

const int N = 3e5 + 10;

struct item {
	int l, r, val;
	item() {}
	item(int l, int r, int val) : l(l), r(r), val(val) {}
};
deque<item> dq;

int n;
int a[N];
int vis[N], cnt[2 * N];
ll ans;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);

		while (vis[a[i]]) {
			item d = dq.front();
			dq.pop_front();

			vis[a[d.l]]--;
			cnt[d.l + d.val - 1]--;

			d.l++;
			if (d.l <= d.r) {
				cnt[d.l + d.val - 1]++;
				dq.push_front(d);
			}
		}

		vis[a[i]]++;

		item d = item(i, i, a[i]);
		while (!dq.empty() && (dq.back().val < a[i])) {
			d.l = dq.back().l;
			cnt[dq.back().l + dq.back().val - 1]--;
			dq.pop_back();
		}

		cnt[d.l + d.val - 1]++;
		dq.push_back(d);

		ans += cnt[i];
	}

	cout << ans << endl;

	return 0;
}