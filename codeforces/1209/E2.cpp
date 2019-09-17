#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 12, M = 2e3 + 5;

int n, m;
int a[N][M];
int take[N][1 << N];
int dp[N][1 << N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		cin >> n >> m;

		vector<int> maxi(m, 0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &a[i][j]);
				maxi[j] = max(maxi[j], a[i][j]);
			}
		}

		vector<int> order(m);
		iota(order.begin(), order.end(), 0);
		sort(order.begin(), order.end(), [maxi](int i, int j) {return maxi[i] > maxi[j];});
		if (m > n) order.resize(n);

		for (int i = 0; i < order.size(); i++) {
			int col = order[i];

			for (int mask = 1; mask < 1 << n; mask++) {
				take[i][mask] = 0;

				for (int shift = 0; shift < n; shift++) {
					int sum = 0;
					for (int j = 0; j < n; j++) {
						if (mask & 1 << j) {
							sum += a[(j + shift) % n][col];
						}
					}

					take[i][mask] = max(take[i][mask], sum);
				}
			}
		}

		for (int mask = 1; mask < 1 << n; mask++) {
			dp[0][mask] = take[0][mask];
		}

		for (int i = 1; i < order.size(); i++) {
			int col = order[i];

			for (int mask = 1; mask < 1 << n; mask++) {
				dp[i][mask] = dp[i - 1][mask];

				for (int smask = mask; smask > 0; smask = (smask - 1) & mask) {
					dp[i][mask] = max(dp[i][mask], take[i][smask] + dp[i - 1][mask ^ smask]);
				}
			}
		}

		cout << dp[order.size() - 1][(1 << n) - 1] << endl;
	}

	return 0;
}