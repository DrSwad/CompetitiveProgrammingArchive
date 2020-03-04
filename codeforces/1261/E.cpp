#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(1e3) + 10;

int n;
int a[N];
int b[N][N];
vector<vector<int>> c[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	if (a[1] > 1) c[1].push_back(vector<int>());
	for (int row = 1; row <= a[1]; row++) {
		b[row][1] = 1;
		if (a[1] > 1) c[1].back().push_back(row);
	}

	if ((n + 1) - a[1] > 1) c[1].push_back(vector<int>());
	for (int row = a[1] + 1; row <= n + 1; row++) {
		b[row][1] = 0;
		if ((n + 1) - a[1] > 1) c[1].back().push_back(row);
	}

	for (int col = 2; col <= n; col++) {
		if (c[col - 1].empty()) {
			for (int row = 1; row <= a[col]; row++) b[row][col] = 1;
			continue;
		}

		int rem = a[col];
		b[c[col - 1][0][0]][col] = 0;
		b[c[col - 1][0][1]][col] = 1; rem--;

		for (int row = 1; rem; row++) {
			if (row != c[col - 1][0][0] && row != c[col - 1][0][1]) {
				b[row][col] = 1;
				rem--;
			}
		}

		for (vector<int> &_c : c[col - 1]) {
			vector<int> zero, one;

			for (int row : _c) {
				if (b[row][col] == 0) zero.push_back(row);
				else one.push_back(row);
			}

			if (zero.size() > 1) c[col].push_back(zero);
			if (one.size() > 1) c[col].push_back(one);
		}
	}

	int tot_rows = 0;
	for (int row = 1; row <= n + 1; row++) {
		tot_rows += accumulate(b[row] + 1, b[row] + n + 1, 0) > 0;
	}
	cout << tot_rows << "\n";

	for (int row = 1; row <= n + 1; row++) {
		int cnt = accumulate(b[row] + 1, b[row] + n + 1, 0);
		if (cnt > 0) {
			for (int col = 1; col <= n; col++) {
				cout << b[row][col];
			}
			cout << "\n";
		}
	}

	return 0;
}