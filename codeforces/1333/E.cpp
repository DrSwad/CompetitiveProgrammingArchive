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

vector<int> construct(int n) {
	if (n == 3) return {0, 1, 5, 8, 2, 6, 3, 4, 7};
	vector<int> v = construct(n - 1), ret(n * n);
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			ret[i * n + 1 + j] = v[i * (n - 1) + j] + 2 * n - 1;
		}
	}
	for (int i = 0; i < n; i++) ret[i * n + 0] = 2 * n - 2 - i;
	for (int j = 0; j < n; j++) ret[(n - 1) * n + j] = n - 1 - j;
	reverse(ret.begin(), ret.end());
	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int n;
	cin >> n;

	if (n <= 2) puts("-1");
	else {
		vector<int> v = construct(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d", v[i * n + j] + 1);
				if (j == n - 1) puts("");
				else printf(" ");
			}
		}
	}

	return 0;
}