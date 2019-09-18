#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

int n, m;
vector<pii> adj[6 * N];
int ans[6 * N];

bool vis[6 * N];
queue<vector<int>> q;

void addEdge(int u, int v, int w, int &at) {
	string str = to_string(w);
	int len = str.length();

	if (len == 1) {
		adj[u].push_back({str[0] - '0', v});
		adj[v].push_back({str[0] - '0', u});
	}
	else {
		adj[u].push_back({str[0] - '0', at + 1});
		adj[at + 1].push_back({str[len - 1] - '0', u});

		adj[v].push_back({str[0] - '0', at + len - 1});
		adj[at + len - 1].push_back({str[len - 1] - '0', v});
	}

	for (int i = 1; i < len - 1; i++) {
		int curr = at + i;
		int nxt = curr + 1;

		adj[curr].push_back({str[i] - '0', nxt});
		adj[nxt].push_back({str[len - (nxt - at)] - '0', curr});
	}

	at += len - 1;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> m;
	int at = n;
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v, i, at);
	}

	
	q.push({1});
	vis[1] = true;

	while (!q.empty()) {
		vector<int> v = q.front(); q.pop();
		vector<vector<int>> nxt(10);
		map<int, int> mp;
		int curr_ans = v.size() ? ans[v[0]] : 0;

		for (int at : v) {
			sort(adj[at].begin(), adj[at].end());

			for (pii p : adj[at]) if (!vis[p.y]) {
				int node = p.y;
				int weight = p.x;
				if (mp.find(node) == mp.end() || mp[node] > weight) {
					mp[node] = weight;
				}
			}
		}

		for (pii p : mp) {
			int node = p.x;
			int weight = p.y;

			vis[node] = true;
			ans[node] = (curr_ans * 10LL + weight) % MOD;
			nxt[weight].push_back(node);
		}

		for (vector<int> v : nxt) if (!v.empty()) q.push(v);
	}

	for (int i = 2; i <= n; i++) printf("%d\n", ans[i]);

	return 0;
}