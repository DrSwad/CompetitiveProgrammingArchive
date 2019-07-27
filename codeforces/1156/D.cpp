#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 2e5 + 10;

int n;
vector<int> adj[2][N];
vector<int> cc[2][N];
int sz[2][N];

bool vis[2][N];
void dfs(int at, int root, int col) {
	vis[col][at] = true;
	cc[col][root].push_back(at);

	for (int c : adj[col][at]) if (!vis[col][c]) {
		dfs(c, root, col);
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		adj[c][u].push_back(v);
		adj[c][v].push_back(u);
	}

	for (int c = 0; c < 2; c++)
		for (int i = 1; i <= n; i++)
			if (!vis[c][i]) dfs(i, i, c);

	for (int c = 0; c < 2; c++)
		for (int i = 1; i <= n; i++)
			for (int j : cc[c][i])
				sz[c][j] = cc[c][i].size();

	ll ans = 0LL;
	for (int i = 1; i <= n; i++)
		ans += sz[0][i] * 1LL * sz[1][i];
	ans -= n;

	cout << ans << endl;

	return 0;
}