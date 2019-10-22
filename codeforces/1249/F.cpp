#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long ll;
typedef unsigned int uint;

typedef pair<int, int> pii;
#define x first
#define y second

#define size(a) (int)a.size()

const int N = 210;

uint n, k;
vector<uint> adj[N];
uint a[N];
uint dp[N][N];

void dfs(uint at, uint parent) {
	vector<uint> ch;
	for (uint child : adj[at]) {
		if (child != parent) {
			dfs(child, at);
			ch.push_back(child);
		}
	}

	for (uint min_dist = n; min_dist > k; min_dist--) {
		for (uint child : ch) dp[at][min_dist] += dp[child][min_dist - 1];
		dp[at][min_dist] = max(dp[at][min_dist], dp[at][min_dist + 1]);
	}

	for (uint min_dist = k; min_dist > 0; min_dist--) {
		uint rest_dist = max((k + 1) - min_dist, min_dist);

		uint sum = 0;
		for (uint child : ch) sum += dp[child][rest_dist - 1];

		for (uint child : ch) {
			dp[at][min_dist] = max(dp[at][min_dist],
				sum - dp[child][rest_dist - 1] + dp[child][min_dist - 1]);
		}

		dp[at][min_dist] = max(dp[at][min_dist], dp[at][min_dist + 1]);
	}

	dp[at][0] = a[at];
	for (uint child : ch) dp[at][0] += dp[child][k];
	dp[at][0] = max(dp[at][0], dp[at][1]);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;
	for (uint i = 1; i <= n; i++) scanf("%u", &a[i]);
	for (uint i = 1; i <= n - 1; i++) {
		uint u, v;
		scanf("%u %u", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 0);

	cout << dp[1][0] << endl;

	return 0;
}