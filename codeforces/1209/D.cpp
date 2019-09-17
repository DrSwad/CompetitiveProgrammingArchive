#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 1e5 + 10;

int n, k;
int par[N], h[N];
int ans;

int parent(int v) {
	return par[v] == v ? v : par[v] = parent(par[v]);
}

bool merge(int x, int y) {
	x = parent(x);
	y = parent(y);

	if (x == y) return false;

	if (h[x] < h[y]) swap(x, y);

	par[y] = x;
	h[x] += h[x] == h[y];

	return true;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;

	iota(par + 1, par + n + 1, 1);

	for (int i = 1; i <= k; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		
		ans += !merge(x, y);
	}

	cout << ans << endl;

	return 0;
}