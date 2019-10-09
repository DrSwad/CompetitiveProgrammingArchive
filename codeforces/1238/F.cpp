#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 3e5 + 10;

int n;
vector<int> adj[N];
int dp[N][3];

void dfs(int at, int from) {
	int ch = 0;
	priority_queue<int> pq;
	for (int nxt : adj[at]) if (nxt != from) {
		dfs(nxt, at);
		ch++;
		
		pq.push(dp[nxt][0]);
		dp[at][0] = max(dp[at][0], 1 + dp[nxt][0]);
		dp[at][1] = max(dp[at][1], 1 + dp[nxt][2]);
	}
	if (ch == 0) return;

	dp[at][0] += ch - 1;

	if (ch >= 2) {
		int tmp = 0;
		tmp += pq.top(); pq.pop();
		tmp += pq.top(); pq.pop();
		dp[at][1] = max(dp[at][1], 1 + tmp + (ch - 2));
		dp[at][2] = max(dp[at][2], 1 + tmp + (ch - 2));
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	while (q--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			dp[i][0] = dp[i][1] = dp[i][2] = 1;
		}

		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		dfs(1, 0);

		printf("%d\n", *max_element(&dp[0][0], &dp[n + 1][0]));
	}

	return 0;
}