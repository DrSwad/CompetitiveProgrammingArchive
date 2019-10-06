#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 3e5 + 10;

int q;
int n;
int a[N];
int l[N], r[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> q;
	while (q--) {
		scanf("%d", &n);

		fill(l + 1, l + n + 1, n + 1);
		fill(r + 1, r + n + 1, 0);

		vector<int> cmp;
		cmp.reserve(n);

		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			cmp.push_back(a[i]);
		}

		sort(cmp.begin(), cmp.end());
		cmp.resize(unique(cmp.begin(), cmp.end()) - cmp.begin());

		for (int i = 1; i <= n; i++) {
			a[i] = lower_bound(cmp.begin(), cmp.end(), a[i]) - cmp.begin() + 1;
			l[a[i]] = min(l[a[i]], i);
			r[a[i]] = max(r[a[i]], i);
		}

		int tot = cmp.size();

		int ans = tot;
		for (int L = 1, R = 1; L <= tot; ) {
			while (R <= tot - 1 && r[R] <= l[R + 1]) R++;
			ans = min(ans, L - 1 + (tot - R));
			L = ++R;
		}

		printf("%d\n", ans);
	}

	return 0;
}