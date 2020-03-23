#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(2e5) + 10;

int solveCycle(vector<int> cycle) {
	int n = cycle.size();
	vector<int> divs;
	for (int d = 1; d * d <= n; d++) {
		if (n % d == 0) divs.push_back(d);
	}
	for (int i = divs.size() - 1; i >= 0; i--) {
		int d = divs[i];
		if (d * d != n) divs.push_back(n / d);
	}
	for (int d : divs) {
		for (int i = 0; i < d; i++) {
			int at = i;
			bool flag = true;
			do {
				if (cycle[i] != cycle[at]) {
					flag = false;
					break;
				}
				at = (at + d);
				if (at >= n) at -= n;
			} while (at != i);
			if (flag) return d;
		}
	}
	return 0;
}

int solve(int n, vector<int> p, vector<int> c) {
	vector<bool> vis(n, false);
	int ret = INT_MAX;

	for (int i = 0; i < n; i++) {
		if (vis[i]) continue;

		vector<int> colors;
		int at = i;
		do {
			vis[at] = true;
			colors.push_back(c[at]);
			at = p[at];
		} while(at != i);

		ret = min(ret, solveCycle(colors));
	}

	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		scanf("%d", &n);
		vector<int> p(n), c(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &p[i]);
			p[i]--;
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &c[i]);
		}
		printf("%d\n", solve(n, p, c));
	}

	return 0;
}