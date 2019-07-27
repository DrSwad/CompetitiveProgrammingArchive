#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 11, MOD = 1e6 + 3;

int inv[MOD];
int f[N];
int c[N];

int query(int x) {
	cout << "? " << x << endl;
	cout.flush();

	int y;
	cin >> y;
	assert(y != -1);
	return y;
}
void answer(int x) {
	cout << "! " << x << endl;
	cout.flush();

	exit(EXIT_SUCCESS);
}

int mul(int a, int b) {
	return (a * 1LL * b) % MOD;
}
int func(int x) {
	if (x < N) return f[x];

	int prod = 1;
	for (int i = 0; i < N; i++) {
		prod = mul(prod, x - i);
	}

	int ret = 0;

	for (int i = 0; i < N; i++) {
		ret = (ret + mul(c[i], mul(prod, inv[x - i]))) % MOD;
	}

	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	for (int i = 0; i < N; i++) f[i] = query(i);

	inv[1] = 1;
	for (int i = 2; i < MOD; i++) {
		inv[i] = mul(MOD - MOD / i, inv[MOD % i]);
	}

	for (int i = 0; i < N; i++) {
		c[i] = 1;
		for (int j = 0; j < N; j++) if (j != i) {
			c[i] = mul(c[i], inv[abs(i - j)]);
			if (i < j) c[i] = MOD - c[i];
		}
		c[i] = mul(c[i], f[i]);
	}

	for (int i = 0; i < MOD; i++)
		if (func(i) == 0) answer(i);

	answer(-1);

	return 0;
}