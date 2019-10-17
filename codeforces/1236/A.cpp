#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second
#define size(a) (int)a.size()

const int N = 110;

int dp[N][N][N];
int a, b, c;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	for (int k = 0; k < N; k++) {
		if (i >= 1 && j >= 2) dp[i][j][k] = 3 + dp[i - 1][j - 2][k];
		if (j >= 1 && k >= 2) dp[i][j][k] = 3 + dp[i][j - 1][k - 2];
	}

	int t;
	cin >> t;

	while (t--) {
		cin >> a >> b >> c;
		cout << dp[a][b][c] << endl;
	}

	return 0;
}