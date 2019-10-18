#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long lint;
typedef unsigned int uint;

typedef pair<int, int> pii;
#define x first
#define y second

#define size(a) (int)a.size()

// const int N = int(1e5) + 10;

uint n, m;
vector<uint> a;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%u %u", &n, &m);
	a.resize(m + 1);
	for (uint i = 1; i <= m; i++) scanf("%u", &a[i]);

	if (n == 1) {
		cout << 0 << endl;
		return 0;
	}

	vector<uint> b(m + 2 + n, 0);
	for (uint i = m + 2; i < m + 2 + n; i++) b[i] = 1;
	for (uint l = m + 2, i = 1; i <= m + 1; i++) {
		if (i <= m) {
			b[l + (a[i] - 1) - 2] += b[l + (a[i] - 1) - 1];
			b[l + (a[i] - 1) - 1] = 0;
		}
		l--;
		b[l + n - 1] += b[l + n];
	}

	lint ans = 0LL;
	for (uint i = 1; i <= n; i++) ans += i * 1LL * b[i];
	for (uint i = 1; i <= n; i++) ans -= i;

	fill(b.begin(), b.end(), 0);
	for (uint i = 1; i <= n; i++) b[i] = 1;
	for (uint r = n, i = 1; i <= m + 1; i++) {
		if (i <= m) {
			b[(r - n + a[i]) + 2] += b[(r - n + a[i]) + 1];
			b[(r - n + a[i]) + 1] = 0;
		}
		r++;
		b[r - n + 1] += b[r - n];
	}

	for (uint i = 1; i <= n; i++) ans += i * 1LL * b[m + n + 2 - i];
	for (uint i = 1; i <= n; i++) ans -= i;

	ans += n;
	cout << ans << endl;

	return 0;
}