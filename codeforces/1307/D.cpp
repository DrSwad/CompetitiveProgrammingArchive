#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(2e5) + 10;

int n, m, k;
int a[N];
vector<int> adj[N];
int dist[2][N];
pii adist[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	memset(dist, -1, sizeof dist);

	dist[0][1] = 0;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int at = q.front(); q.pop();
		for (int nxt : adj[at]) if (dist[0][nxt] == -1) {
			dist[0][nxt] = dist[0][at] + 1;
			q.push(nxt);
		}
	}

	dist[1][n] = 0;
	q = queue<int>();
	q.push(n);
	while (!q.empty()) {
		int at = q.front(); q.pop();
		for (int nxt : adj[at]) if (dist[1][nxt] == -1) {
			dist[1][nxt] = dist[1][at] + 1;
			q.push(nxt);
		}
	}

	for (int i = 1; i <= k; i++) {
		adist[i] = make_pair(dist[0][a[i]], dist[1][a[i]]);
	}

	sort(adist + 1, adist + k + 1, [&](pii &p1, pii &p2) {
		return p1.x - p1.y > p2.x - p2.y;
	});

	int max_y = adist[1].y, max_dist = 0;
	for (int i = 2; i <= k; i++) {
		max_dist = max(max_dist, adist[i].x + max_y + 1);
		max_y = max(max_y, adist[i].y);
	}

	printf("%d\n", min(dist[0][n], max_dist));

	return 0;
}