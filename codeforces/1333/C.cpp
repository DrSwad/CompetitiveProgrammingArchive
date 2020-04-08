#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<int> a(n + 1, 0);
	vector<ll> psum(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		psum[i] = psum[i - 1] + a[i];
	}

	map<ll, int> mp;
	mp[0] = 1;

	ll ans = 0LL;

	for (int l = 1, r = 1; l <= n; l++) {
		while (r <= n && mp.find(psum[r]) == mp.end()) {
			mp[psum[r]] = 1;
			r++;
		}
		ans += r - l;
		mp.erase(psum[l - 1]);
	}

	cout << ans << endl;

	return 0;
}