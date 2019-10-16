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
int a[N];
int b[N];
int c[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		c[b[i]] = i;
	}

	int maxi = 0;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += maxi > c[a[i]];
		maxi = max(maxi, c[a[i]]);
	}
	cout << ans << endl;

	return 0;
}