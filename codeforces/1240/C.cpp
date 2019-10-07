#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 5e5 + 10;

int q;
int n, k;
vector<pii> adj[N];
ll dp[N][2];

void dfs(int at, int from) {
	ll sum = 0LL;
	vector<ll> v;

	for (auto nxt : adj[at]) {
		int to = nxt.x;
		int w = nxt.y;
		if (to == from) continue;

		dfs(to, at);
		sum += dp[to][0];
		v.push_back(dp[to][1] - dp[to][0] + w);
	}

	sort(v.begin(), v.end(), greater<ll>());

	dp[at][0] = dp[at][1] = sum;

	for (int taken = 0; taken < 2; taken++) {
		for (int i = 0; i < min((int)v.size(), k - taken); i++) {
			if (v[i] > 0) dp[at][taken] += v[i];
		}
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> q;
	while (q--) {
		scanf("%d %d", &n, &k);

		for (int i = 1; i <= n; i++) adj[i].clear();

		for (int i = 1; i < n; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			adj[u].push_back({v, w});
			adj[v].push_back({u, w});
		}

		dfs(1, 0);

		printf("%lld\n", dp[1][0]);
	}

	return 0;
}