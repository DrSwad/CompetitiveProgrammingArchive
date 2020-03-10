#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(3e5) + 10;

int n;
ll a[N];

int x, y, z;
vector<int> grundy;
map<int, int> grundy5;
int cycle_from;

int getGrundy(ll a, int i) {
	if (a < 0) return 0;

	int g;
	if (a < grundy.size()) g = grundy[a];
	else {
		int cycle_len = grundy.size() - 1 - cycle_from;
		a = (a - (grundy.size() - 1)) % cycle_len;
		if (a == 0) a = cycle_len;
		g = grundy[cycle_from + a];
	}

	return (g & (3 << (2 * i))) >> (2 * i);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		scanf("%d", &n);
		scanf("%d %d %d", &x, &y, &z);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

		grundy.clear();
		grundy5.clear();
		grundy.push_back(0);
		grundy5[0] = 0;

		for (int i = 1; ; i++) {
			int gx = 0, gy = 0, gz = 0;
			int _gx, _gy, _gz;
			_gx = i <= x ? 0 : (grundy[i - x] & 48) >> 4;
			_gy = i <= y ? 0 : (grundy[i - y] & 12) >> 2;
			_gz = i <= z ? 0 : (grundy[i - z] & 3) >> 0;

			while (_gx == gx || _gy == gx || _gz == gx) gx++;
			while (_gx == gy || _gz == gy) gy++;
			while (_gx == gz || _gy == gz) gz++;

			grundy.push_back((gx << 4) + (gy << 2) + gz);

			int last5 = 0;
			for (int j = i; j > i - 5 && j > 0; j--) {
				last5 |= grundy[j] << ((i - j) * 6);
			}

			if (grundy5.find(last5) != grundy5.end()) {
				cycle_from = grundy5[last5];
				break;
			}
			grundy5[last5] = i;
		}

		int xorsum = 0;
		for (int i = 1; i <= n; i++) {
			xorsum ^= getGrundy(a[i], 2);
		}

		int ans = 0;
		int vals[] = {z, y, x};
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 3; j++) {
				ans += (xorsum ^ getGrundy(a[i], 2) ^ getGrundy(a[i] - vals[j], j)) == 0;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}