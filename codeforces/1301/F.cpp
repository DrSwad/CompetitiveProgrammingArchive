#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

const int N = 1003;
const int K = 43;

int n, m, k;
vector<int> adj[N * N + K][2];
int dist[K][N * N];

void initDist(int from) {
	vector<bool> vis(n * m + k, false);
	vis[from] = true;

	vector<vector<int>> at_dist(1);
	at_dist[0].push_back(from);

	for (int curr_dist = 0; curr_dist < at_dist.size(); curr_dist++) {
		for (int node : at_dist[curr_dist]) {
			for (int nxt : adj[node][0]) if (!vis[nxt]) {
				vis[nxt] = true;
				dist[from - n * m][nxt] = curr_dist + 1;
				while (curr_dist + 1 >= at_dist.size()) at_dist.push_back(vector<int>());
				at_dist[curr_dist + 1].push_back(nxt);
			}
			for (int nxt : adj[node][1]) if (!vis[nxt]) {
				vis[nxt] = true;
				dist[from - n * m][nxt] = curr_dist + 2;
				while (curr_dist + 2 >= at_dist.size()) at_dist.push_back(vector<int>());
				at_dist[curr_dist + 2].push_back(nxt);
			}
		}
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &m, &k);
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			int curr_cell = r * m + c;
			int color;
			scanf("%d", &color);
			color = n * m + color - 1;

			adj[curr_cell][0].push_back(color);
			adj[color][0].push_back(curr_cell);
			if (r - 1 >= 0) adj[curr_cell][1].push_back(curr_cell - m);
			if (r + 1 < n) adj[curr_cell][1].push_back(curr_cell + m);
			if (c - 1 >= 0) adj[curr_cell][1].push_back(curr_cell - 1);
			if (c + 1 < m) adj[curr_cell][1].push_back(curr_cell + 1);
		}
	}

	for (int i = 0; i < k; i++) initDist(n * m + i);

	int q;
	scanf("%d", &q);
	while (q--) {
		int r1, c1, r2, c2;
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		int from = (r1 - 1) * m + (c1 - 1);
		int to = (r2 - 1) * m + (c2 - 1);

		int min_dist = abs(r1 - r2) + abs(c1 - c2);
		for (int i = 0; i < k; i++) {
			min_dist = min(min_dist, (dist[i][from] + dist[i][to]) / 2);
		}

		printf("%d\n", min_dist);
	}

	return 0;
}