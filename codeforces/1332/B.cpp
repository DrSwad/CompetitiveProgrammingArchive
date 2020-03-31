#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;

int minp[N];
void sieve() {
	for (int i = 2; i < N; i++) if (minp[i] == 0) {
		for (int j = i; j < N; j += i) {
			if (minp[j] == 0) minp[j] = i;
		}
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	sieve();

	int t;
	cin >> t;

	while (t--) {
		int n;
		scanf("%d", &n);

		vector<int> c(n), cols;
		for (int i = 0; i < n; i++) {
			int a;
			scanf("%d", &a);
			cols.push_back(minp[a]);
			c[i] = minp[a];
		}

		sort(cols.begin(), cols.end());
		cols.resize(unique(cols.begin(), cols.end()) - cols.begin());
		map<int, int> mp;
		for (int i = 0; i < cols.size(); i++) mp[cols[i]] = i + 1;

		printf("%d\n", (int)mp.size());
		for (int i = 0; i < n; i++) {
			if (i > 0) printf(" ");
			printf("%d", mp[c[i]]);
		}
		puts("");
	}

	return 0;
}