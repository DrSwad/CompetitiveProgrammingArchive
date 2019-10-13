#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;

int n;
int cost[N][3];
vector<int> adj[N];
ll dp[3][3];
int ans[N];

void printAns() {
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	exit(EXIT_SUCCESS);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	for (int col = 0; col < 3; col++) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &cost[i][col]);
		}
	}

	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) {
		if (adj[i].size() >= 3) {
			printf("-1");
			return 0;
		}
	}

	int leaf;
	for (leaf = 1; leaf <= n; leaf++) {
		if (adj[leaf].size() == 1) break;
	}

	int adjLeaf = adj[leaf][0];

	for (int colLeaf = 0; colLeaf < 3; colLeaf++) {
		for (int colAdjLeaf = 0; colAdjLeaf < 3; colAdjLeaf++) {
			ll &totCost = dp[colLeaf][colAdjLeaf];
			totCost = LLONG_MAX;

			if (colLeaf == colAdjLeaf) continue;

			totCost = cost[leaf][colLeaf] + cost[adjLeaf][colAdjLeaf];

			int prevCol[2] = {colLeaf, colAdjLeaf};
			int prevAt = adjLeaf;
			int currAt = adj[adjLeaf][0] ^ adj[adjLeaf][1] ^ leaf;
			int visited = 2;
			while (true) {
				int col = 0 ^ 1 ^ 2 ^ prevCol[0] ^ prevCol[1];
				totCost += cost[currAt][col];

				visited++;
				if (visited == n) break;

				prevCol[0] = prevCol[1];
				prevCol[1] = col;

				int nxtAt = adj[currAt][0] ^ adj[currAt][1] ^ prevAt;
				prevAt = currAt;
				currAt = nxtAt;
			}
		}
	}

	ll minCost = *min_element(&dp[0][0], &dp[3][0]);
	printf("%lld\n", minCost);

	for (int colLeaf = 0; colLeaf < 3; colLeaf++) {
		for (int colAdjLeaf = 0; colAdjLeaf < 3; colAdjLeaf++) {
			if (dp[colLeaf][colAdjLeaf] > minCost) continue;

			ans[leaf] = colLeaf + 1;
			ans[adjLeaf] = colAdjLeaf + 1;

			int prevCol[2] = {colLeaf, colAdjLeaf};
			int prevAt = adjLeaf;
			int currAt = adj[adjLeaf][0] ^ adj[adjLeaf][1] ^ leaf;
			int visited = 2;
			while (visited < n) {
				int col = 0 ^ 1 ^ 2 ^ prevCol[0] ^ prevCol[1];
				ans[currAt] = col + 1;

				visited++;
				if (visited == n) break;

				prevCol[0] = prevCol[1];
				prevCol[1] = col;

				int nxtAt = adj[currAt][0] ^ adj[currAt][1] ^ prevAt;
				prevAt = currAt;
				currAt = nxtAt;
			}

			printAns();
		}
	}

	return 0;
}