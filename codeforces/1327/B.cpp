#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(1e5) + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		scanf("%d", &n);
		vector<vector<int>> adj(n);
		for (int i = 0; i < n; i++) {
			int k;
			scanf("%d", &k);
			adj[i].resize(k);
			for (int j = 0; j < k; j++) {
				int x;
				scanf("%d", &x);
				adj[i][j] = --x;
			}
		}
		set<int> st;
		for (int i = 0; i < n; i++) st.insert(i);
		int left = -1;
		for (int i = 0; i < n; i++) {
			bool flag = false;
			for (int j : adj[i]) {
				if (st.find(j) != st.end()) {
					st.erase(j);
					flag = true;
					break;
				}
			}
			if (!flag) left = i;
		}
		if (left == -1) puts("OPTIMAL");
		else {
			puts("IMPROVE");
			printf("%d %d\n", left + 1, *st.begin() + 1);
		}
	}

	return 0;
}