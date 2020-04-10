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

	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		vector<pii> v(n + 1);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &v[i].x, &v[i].y);
		}

		v[0] = {0, 0};
		bool flag = true;
		for (int i = 1; i <= n; i++) {
			if (v[i].x < v[i - 1].x) flag = false;
			if (v[i].y < v[i - 1].y) flag = false;
			if (v[i].x - v[i - 1].x < v[i].y - v[i - 1].y) flag = false;
		}

		if (flag) puts("YES");
		else puts("NO");
	}

	return 0;
}