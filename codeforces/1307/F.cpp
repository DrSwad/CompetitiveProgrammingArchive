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

const int N = int(4e5) + 10;
const int LOGN = 19;

int n, k, r;
vector<int> adj[N];
int up[LOGN][N], lv[N];
int clan[N];

int findClan(int mem) {
	if (mem == clan[mem]) return mem;
	else return clan[mem] = findClan(clan[mem]);
}
void merge(int mem, int with) {
	clan[findClan(with)] = findClan(mem);
}

void dfs(int curr, int from) {
	lv[curr] = lv[from] + 1;
	up[0][curr] = from;
	for (int jump = 1; jump < LOGN; jump++) {
		up[jump][curr] = up[jump - 1][up[jump - 1][curr]];
	}
	for (int nxt : adj[curr]) {
		if (nxt != from) dfs(nxt, curr);
	}
}
int lca(int u, int v) {
	if (lv[u] < lv[v]) swap(u, v);
	for (int diff = lv[u] - lv[v]; diff > 0; diff -= diff & -diff) {
		u = up[__builtin_ctz(diff)][u];
	}
	if (u == v) return u;
	for (int jump = LOGN - 1; jump >= 0; jump--) {
		if (up[jump][u] != up[jump][v])
			u = up[jump][u], v = up[jump][v];
	}
	return up[0][u];
}

int walkUp(int from, int len) {
	while (len) {
		from = up[__builtin_ctz(len)][from];
		len -= len & -len;
	}
	return from;
}
bool check(int u, int v) {
	int l = lca(u, v);
	int dist = lv[u] - lv[l] + lv[v] - lv[l];
	if (dist <= 2 * k) return true;

	if (lv[u] > lv[v]) swap(u, v);
	if (lv[u] - lv[l] < k) u = walkUp(v, dist - k);
	else u = walkUp(u, k);
	v = walkUp(v, k);

	return findClan(u) == findClan(v);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &k, &r);

	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u].push_back(n + i);
		adj[n + i].push_back(u);

		adj[v].push_back(n + i);
		adj[n + i].push_back(v);
	}

	dfs(1, 0);

	vector<int> dist(2 * n, N);
	queue<int> q;

	while (r--) {
		int x;
		scanf("%d", &x);
		dist[x] = 0;
		q.push(x);
	}

	iota(clan, clan + 2 * n, 0);

	while (!q.empty()) {
		int at = q.front(); q.pop();
		if (dist[at] == k) break;

		for (int nxt : adj[at]) {
			merge(at, nxt);
			if (dist[at] + 1 < dist[nxt]) {
				dist[nxt] = dist[at] + 1;
				q.push(nxt);
			}
		}
	}

	int Q;
	scanf("%d", &Q);

	while (Q--) {
		int u, v;
		scanf("%d %d", &u, &v);
		puts(check(u, v) ? "YES" : "NO");
	}

	return 0;
}