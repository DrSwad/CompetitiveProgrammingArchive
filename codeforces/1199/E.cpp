#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 3e5 + 10, M = 5e5 + 10;

int T;
int n, m;
vector<int> adj[N];
vector<ii> e;
vector<int> matching;
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> T;
	while (T--) {
		scanf("%d %d", &n, &m);
		int totN = 3 * n;

		for (int i = 1; i <= m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);

			e.push_back({u, v});
			adj[u].push_back(e.size() - 1);
			adj[v].push_back(e.size() - 1);
		}

		bool visNode[totN + 1];
		memset(visNode, 0, sizeof visNode);
		bool visEdge[m];
		memset(visEdge, 0, sizeof visEdge);

		for (int nId = 1; nId <= totN; nId++) if (!visNode[nId]) {
			int n2Id = 0;

			for (int eId : adj[nId]) if (!visEdge[eId]) {
				n2Id = e[eId].x;
				if (n2Id == nId) n2Id = e[eId].y;
				matching.push_back(eId);
				break;
			}

			if (n2Id) {
				visNode[nId] = true;
				visNode[n2Id] = true;

				for (int eId : adj[nId]) visEdge[eId] = true;
				for (int eId : adj[n2Id]) visEdge[eId] = true;
			}
		}

		if (matching.size() >= n) {
			printf("Matching\n");
			for (int i = 0; i < n; i++) printf("%d ", matching[i] + 1);
			printf("\n");
		}
		else {
			printf("IndSet\n");
			int rem = n;
			for (int i = 1; i <= totN && rem > 0; i++) if (!visNode[i]) {
				printf("%d ", i);
				rem--;
			}
			printf("\n");
		}

		for (int i = 1; i <= totN; i++) adj[i].clear();
		e.clear();
		matching.clear();
	}
 
	return 0;
}