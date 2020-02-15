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

const int N = int(1e5) + 10;
const int LOGN = 20;

int n;
vector<int> adj[N];
int par[N], lv[N];
int P[LOGN][N];

void dfs(int at, int parent) {
	par[at] = parent;
	if (parent >= 0) lv[at] = lv[parent] + 1;
	for (int nxt : adj[at]) if (nxt != parent) dfs(nxt, at);
}

void initSp(int n) {
    memset(P, -1, sizeof P);
    for (int i = 0; i < n; i++) {
        P[0][i] = par[i];
    }
    for (int i = 1; i < LOGN; i++) {
        for (int j = 0; j < n; j++) {
            if (P[i - 1][j] != -1) {
                P[i][j] = P[i - 1][P[i - 1][j]];
            }
        }
    }
}

int lca(int u, int v) {
    if (lv[u] < lv[v]) {
        swap(u, v);
    }
    for (int i = LOGN - 1; i >= 0; i--) {
        if (lv[u] - (1 << i) >= lv[v]) {
            u = P[i][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LOGN - 1; i >= 0; i--) {
        if (P[i][u] != P[i][v]) {
            u = P[i][u];
            v = P[i][v];
        }
    }
    return par[u];
}

int dist(int u, int v) {
	int l = lca(u, v);
	return lv[u] - lv[l] + lv[v] - lv[l];
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--, v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(0, -1);
	initSp(n);

	int q;
	scanf("%d", &q);

	while (q--) {
		int x, y, a, b, k;
		scanf("%d %d %d %d %d", &x, &y, &a, &b, &k);
		x--, y--, a--, b--;

		function<bool (int)> check = [&](int dist_ab) {
			if (dist_ab <= k && (k - dist_ab) % 2 == 0) {
				printf("YES\n");
				return true;
			}
			return false;
		};

		if (check(dist(a, b))) continue;

		int dist_ax = dist(a, x);
		int dist_ay = dist(a, y);
		int dist_bx = dist(b, x);
		int dist_by = dist(b, y);
		int cycle_len = dist(x, y) + 1;

		if (check(dist_ax + 1 + dist_by)) continue;
		if (check(dist_ay + 1 + dist_bx)) continue;
		if (check(dist_ax + 1 + cycle_len + dist_by)) continue;
		if (check(dist_ay + 1 + cycle_len + dist_bx)) continue;

		printf("NO\n");
	}

	return 0;
}