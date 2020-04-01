#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128 LL;
typedef pair<int, int> pii;
#define x first
#define y second
typedef complex<double> base;

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int MAXT = 2505;
const int MAXN = 55;
const int MOD = int(1e9) + 7;
const double PI = acos(-1);

void fft(vector<base> &a, bool inv) {
	int n = a.size();
	int j = 0;

	for (int i = 1; i < n; i++) {
		int bit = n >> 1;

		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;

		if (i < j) swap(a[i], a[j]);
	}

	vector<base> roots(n / 2);
	double ang = 2 * PI / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++)
		roots[i] = base(cos(ang * i), sin(ang * i));

	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;

		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; k++) {
				base u = a[j + k], v = a[j + k + i / 2] * roots[k * step];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}

	if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());

	int n = 2;
	while (n < a.size() + b.size()) n <<= 1;

	fa.resize(n);
	fft(fa, false);

	fb.resize(n);
	fft(fb, false);

	for (int i = 0; i < n; i++) fa[i] *= fb[i];

	fft(fa, 1);
	vector<ll> ret(n);
	for (int i = 0; i < n; i++) ret[i] = (ll)round(fa[i].real());

	return ret;
}

int n, T;
int cnt[3];
vector<int> gen[3];
int gen_ways[3][MAXN][MAXT];
int gen2_ways[MAXN][MAXN][MAXT];
int take_ways[MAXN][MAXN][MAXN][3];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &T);

	for (int i = 1; i <= n; i++) {
		int t, g;
		scanf("%d %d", &t, &g);
		g--;
		gen[g].push_back(t);
		cnt[g]++;
	}

	for (int g = 0; g < 3; g++) {
		gen_ways[g][0][0] = 1;

		for (int i = 0; i < cnt[g]; i++) {
			for (int take = cnt[g]; take >= 1; take--) {
				for (int sum = 0; sum < MAXT; sum++) {
					if (sum >= gen[g][i]) {
						gen_ways[g][take][sum] += gen_ways[g][take - 1][sum - gen[g][i]];

						if (gen_ways[g][take][sum] >= MOD) gen_ways[g][take][sum] -= MOD;
					}
				}
			}
		}
	}

	for (int take0 = 0; take0 <= cnt[0]; take0++) {
		for (int take1 = 0; take1 <= cnt[1]; take1++) {
			vector<ll> a(gen_ways[0][take0], gen_ways[0][take0] + MAXT);
			vector<ll> b(gen_ways[1][take1], gen_ways[1][take1] + MAXT);
			vector<ll> c = multiply(a, b);
			for (int sum = 0; sum < MAXT; sum++)
				gen2_ways[take0][take1][sum] = c[sum] % MOD;
		}
	}

	take_ways[1][0][0][0] = take_ways[0][1][0][1] = take_ways[0][0][1][2] = 1;
	for (int take0 = 0; take0 <= cnt[0]; take0++) {
		for (int take1 = 0; take1 <= cnt[1]; take1++) {
			for (int take2 = 0; take2 <= cnt[2]; take2++) {
				if (take0 + take1 + take2 <= 1) continue;

				if (take0 > 0) {
					take_ways[take0][take1][take2][0] =
						(ll)take0 *
						(take_ways[take0 - 1][take1][take2][1] +
						take_ways[take0 - 1][take1][take2][2]) % MOD;
				}
				if (take1 > 0) {
					take_ways[take0][take1][take2][1] =
						(ll)take1 *
						(take_ways[take0][take1 - 1][take2][0] +
						take_ways[take0][take1 - 1][take2][2]) % MOD;
				}
				if (take2 > 0) {
					take_ways[take0][take1][take2][2] =
						(ll)take2 *
						(take_ways[take0][take1][take2 - 1][0] +
						take_ways[take0][take1][take2 - 1][1]) % MOD;
				}
			}
		}
	}

	int ans = 0;
	for (int take0 = 0; take0 <= cnt[0]; take0++) {
		for (int take1 = 0; take1 <= cnt[1]; take1++) {
			for (int take2 = 0; take2 <= cnt[2]; take2++) {
				for (int sum = 0; sum <= T; sum++) {
					int curr_take_ways = 0;
					for (int g = 0; g < 3; g++) {
						curr_take_ways += take_ways[take0][take1][take2][g];
						if (curr_take_ways >= MOD) curr_take_ways -= MOD;
					}

					ans += (ll)gen2_ways[take0][take1][sum] *
							gen_ways[2][take2][T - sum] % MOD
							* curr_take_ways % MOD;
					if (ans >= MOD) ans -= MOD;
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}