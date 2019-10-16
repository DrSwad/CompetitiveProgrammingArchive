#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;

int n;
int a[3 * N];
map<int, int> mp;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = n; i < 3 * n; i++) a[i] = a[i % n];

	for (int l = 0, r = 0; l < n; l++) {
		while (r < 3 * n && (mp.empty() || a[r] >= (mp.rbegin()->x + 1) / 2)) {
			mp[a[r]]++;
			r++;
		}
		printf("%d ", r == 3 * n ? -1 : r - l);
		mp[a[l]]--;
		if (mp[a[l]] == 0) mp.erase(a[l]);
	}

	return 0;
}