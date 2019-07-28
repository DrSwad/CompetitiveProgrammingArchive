#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 3e5 + 10;

int n, x;
int a[N];
ll dp[N][3][3];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	fill (&dp[0][0][0], &dp[N][0][0], LLONG_MIN);
	fill (&dp[0][0][0], &dp[1][0][0], 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++)
		for (int k = 0; k < 3; k++) {
			if (j >= 1) {
				if (j == 2) dp[i][j][k] = dp[i - 1][j][k];
				if (k != 1) dp[i][j][k] = max(dp[i][j][k], max(dp[i - 1][1][k] + a[i], 0LL));
				else dp[i][j][k] = max(dp[i][j][k], max(dp[i - 1][1][0] + a[i], 0LL));
				if (k >= 1) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][1][1] + a[i] * 1LL * x);
			}
		}
	}

	cout << dp[n][2][2] << endl;

	return 0;
}