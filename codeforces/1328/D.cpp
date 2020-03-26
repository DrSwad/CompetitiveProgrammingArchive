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

	int q;
	cin >> q;

	while (q--) {
		int n;
		scanf("%d", &n);

		vector<int> t(n);
		int same = -1;
		for (int i = 0; i < n; i++) {
			scanf("%d", &t[i]);
		}
		for (int i = 0; i < n; i++) {
			if (same == -1 && t[i] == t[(i + 1) % n]) same = i;
		}

		vector<int> col(n);
		col[0] = 0;
		for (int i = 1; i < n; i++) {
			if (t[i] == t[i - 1]) col[i] = col[i - 1];
			else col[i] = col[i - 1] ^ 1;
		}
		if (t[n - 1] != t[0] && col[n - 1] == col[0]) {
			if (same != -1) {
				for (int i = 0; i <= same; i++) col[i] ^= 1;
			}
			else col[n - 1] = 2;
		}

		int tot = *max_element(col.begin(), col.end()) + 1;
		printf("%d\n", tot);
		for (int i = 0; i < n; i++) {
			if (i > 0) printf(" ");
			printf("%d", col[i] + 1);
		}
		puts("");
	}

	return 0;
}