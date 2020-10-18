#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = 210;

char cell[N][N];

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

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf(" %c", &cell[i][j]);
			}
		}

		char pick1 = '0';
		if (cell[1][2] == cell[2][1]) pick1 = cell[1][2];
		else if (cell[n][n - 1] == '0' && cell[n - 1][n] == '0') pick1 = '1';

		char pick2 = ((pick1 - '0') ^ 1) + '0';

		vector<pii> ans;
		if (cell[1][2] != pick1) ans.push_back({1, 2});
		if (cell[2][1] != pick1) ans.push_back({2, 1});
		if (cell[n][n - 1] != pick2) ans.push_back({n, n - 1});
		if (cell[n - 1][n] != pick2) ans.push_back({n - 1, n});

		printf("%d\n", (int)ans.size());
		for (auto p : ans) printf("%d %d\n", p.x, p.y);
	}

	return 0;
}