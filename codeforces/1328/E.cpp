#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(2e5) + 10;

int n, m;
vector<int> adj[N];

vector<int> line;
int h[N], s[N], e[N];
vector<pii> hs[N], he[N];

void dfs(int at, int p) {
	h[at] = h[p] + 1;

	line.push_back(at);
	s[at] = line.size();
	hs[h[at]].push_back(make_pair(s[at], at));

	for (int to : adj[at]) {
		if (to != p) dfs(to, at);
	}

	line.push_back(at);
	e[at] = line.size();
	he[h[at]].push_back(make_pair(e[at], at));
}

bool solve(vector<int> nodes) {
	sort(nodes.begin(), nodes.end(), [&](int i, int j) {return h[i] < h[j];});

	int tot = nodes.size();
	vector<int> suff_max(tot), suff_min(tot);
	suff_max[tot - 1] = e[nodes[tot - 1]];
	suff_min[tot - 1] = s[nodes[tot - 1]];
	for (int i = tot - 2; i >= 0; i--) {
		suff_max[i] = max(suff_max[i + 1], e[nodes[i]]);
		suff_min[i] = min(suff_min[i + 1], s[nodes[i]]);
	}

	for (int l = 0; l < nodes.size(); ) {
		int _s = suff_min[l], _e = suff_max[l];
		int _h = h[nodes[l]];
		if (_h == 1) {
			l++;
			continue;
		}

		auto s_at = lower_bound(hs[_h - 1].begin(), hs[_h - 1].end(), make_pair(_s, 0));
		s_at--;
		auto e_at = lower_bound(he[_h - 1].begin(), he[_h - 1].end(), make_pair(_e, 0));

		if (s_at->y != e_at->y) return false;

		int r = l;
		while (r < nodes.size() && h[nodes[r]] == h[nodes[l]]) r++;
		l = r;
	}

	return true;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, 0);

	while (m--) {
		int k;
		scanf("%d", &k);
		vector<int> v(k);
		for (int i = 0; i < k; i++) {
			scanf("%d", &v[i]);
		}
		if (solve(v)) puts("YES");
		else puts("NO");
	}

	return 0;
}