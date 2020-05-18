#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(3e3) + 2;

int n, m, k;
vector<int> adj[N];
unordered_map<int, int> mp;
int from[N * N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 1; i <= k; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		mp[a * N * N + b * N + c] = 1;
	}

	adj[n].push_back(n + 1);
	queue<int> q;
	q.push(1);
	from[1] = -1;

	while (!q.empty()) {
		int at_edge = q.front(); q.pop();

		for (int to : adj[at_edge % N]) {
			int nxt_edge = at_edge % N * N + to;
			if (from[nxt_edge] || mp.find(at_edge * N + to) != mp.end()) continue;
			from[nxt_edge] = at_edge;

			q.push(nxt_edge);
		}
	}

	if (!from[n * N + n + 1]) {
		puts("-1");
		return 0;
	}

	vector<int> path;
	for (int i = n * N + n + 1; from[i] != -1; i = from[i])
		path.push_back(i / N);
	reverse(path.begin(), path.end());

	printf("%d\n", (int)path.size() - 1);
	for (int i = 0; i < path.size(); i++) {
		if (i > 0) printf(" ");
		printf("%d", path[i]);
	}
	puts("");

	return 0;
}