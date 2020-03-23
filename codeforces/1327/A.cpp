#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(1e5) + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;
	while (t--) {
		int n, k;
		scanf("%d %d", &n, &k);
		if (n < k * 1LL * k || (n - k * 1LL * k) % 2 != 0) puts("NO");
		else puts("YES");
	}

	return 0;
}