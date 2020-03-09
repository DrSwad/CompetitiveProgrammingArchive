#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = 505;

int n;
int a[N];
map<int, int> nxt[N];
int dp[N][N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	for (int i = 1; i <= n; i++) {
		dp[i][i] = 1;
		nxt[i][a[i]] = i;
	}

	for (int len = 2; len <= n; len++) {
		for (int i = 1; i + len <= n + 1; i++) {
			int j = i + len - 1;
			dp[i][j] = 1 + dp[i + 1][j];

			int val = a[i], at = i + 1;
			while (nxt[at].find(val) != nxt[at].end() &&
					nxt[at][val] <= j) {
				at = nxt[at][val] + 1;
				dp[i][j] = min(dp[i][j], 1 + dp[at][j]);
				val++;

				if (at == j + 1) nxt[i][val] = j;
			}
		}
	}

	printf("%d\n", dp[1][n]);

	return 0;
}