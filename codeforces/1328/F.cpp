#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(2e5) + 10;

int n, k;
ll a[N], cnt[N], l[N], lm[N], r[N], rm[N];
ll ans[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &k);

	map<int, int> mp;
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		mp[a]++;
	}

	n = mp.size();
	int i = 1;
	for (auto it = mp.begin(); it != mp.end(); it++, i++) {
		a[i] = it->x;
		cnt[i] = it->y;

		if (i == 1) continue;
		l[i] = l[i - 1] + cnt[i - 1];
		lm[i] = lm[i - 1] + l[i] * (a[i] - a[i - 1]) - cnt[i - 1];
	}
	for (i = n; i >= 1; i--) {
		if (i == n) continue;
		r[i] = r[i + 1] + cnt[i + 1];
		rm[i] = rm[i + 1] + r[i] * (a[i + 1] - a[i]) - cnt[i + 1];
	}

	// for (int i = 1; i <= n; i++) {
	// 	debug() << name(i) name(a[i]) name(cnt[i]) name(l[i]) name(r[i]) name(lm[i]) name(rm[i]);
	// }

	for (int i = 1; i <= n; i++) {
		if (cnt[i] >= k) {
			ans[i] = 0;
			continue;
		}

		ll ansL, ansR;
		if (i > 1) ansL = lm[i] + min(k - cnt[i], l[i]) + (l[i] + cnt[i] >= k ? 0 : rm[i] + (k - cnt[i] - l[i]));
		else ansL = LLONG_MAX;
		if (i < n) ansR = rm[i] + min(k - cnt[i], r[i]) + (r[i] + cnt[i] >= k ? 0 : lm[i] + (k - cnt[i] - r[i]));
		else ansR = LLONG_MAX;
		ans[i] = min(ansL, ansR);
	}

	cout << *min_element(ans + 1, ans + n + 1) << endl;

	return 0;
}