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



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n, m;
		cin >> n >> m;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (i == 1 && j == 1) cout << 'W';
				else cout << 'B';
			}
			puts("");
		}
	}

	return 0;
}