#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 55;

int n;
int pref[N][N];
int dp[N][N][N][N];

int totalBlacks(int x1, int y1, int x2, int y2) {
	return pref[x2][y2] - pref[x2][y1 - 1] - pref[x1 - 1][y2] + pref[x1 - 1][y1 - 1];
}

int DP(int x1, int y1, int x2, int y2) {
	if (x2 < x1 || y2 < y1) return 0;
	int &ret = dp[x1][y1][x2][y2];
	if (ret != -1) return ret;

	if (totalBlacks(x1, y1, x2, y2) == 0) return ret = 0;

	int h = x2 - x1 + 1;
	int w = y2 - y1 + 1;

	if (max(h, w) == 1) return ret = 1;
	ret = max(h, w);

	if (w >= h) {
		for (int i = 1; i <= w; i++) {
			if (totalBlacks(x1, y1 + i - 1, x2, y1 + i - 1) > 0) continue;

			ret = min(ret, DP(x1, y1, x2, y1 + i - 2) + DP(x1, y1 + i, x2, y2));
		}
	}
	else {
		for (int i = 1; i <= h; i++) {
			if (totalBlacks(x1 + i - 1, y1, x1 + i - 1, y2) > 0) continue;

			ret = min(ret, DP(x1, y1, x1 + i - 2, y2) + DP(x1 + i, y1, x2, y2));
		}
	}

	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	char c;
	for (int i = 1; i <= n; i++) {
		scanf("%c", &c);
		for (int j = 1; j <= n; j++) {
			scanf("%c", &c);
			pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + (c == '#');
		}
	}

	memset(dp, -1, sizeof dp);

	cout << DP(1, 1, n, n) << endl;

	return 0;
}