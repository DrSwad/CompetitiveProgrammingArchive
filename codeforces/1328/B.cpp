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
		int n, k;
		scanf("%d %d", &n, &k);

		int L = 1, R = n - 1;
		while (L != R) {
			int mid = (L + R + 1) / 2;
			int x = n - mid;
			if (x * 1LL * (x + 1) / 2 >= k) L = mid;
			else R = mid - 1;
		}

		int pos1 = L, pos2 = (pos1 + 1) + ((n - pos1) * 1LL * (n - pos1 + 1) / 2) - k;
		for (int i = 1; i < pos1; i++) printf("a");
		printf("b");
		for (int i = pos1 + 1; i < pos2; i++) printf("a");
		printf("b");
		for (int i = pos2 + 1; i <= n; i++) printf("a");
		puts("");
	}

	return 0;
}