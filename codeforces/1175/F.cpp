#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 3e5 + 10;

int n;
int a[N];
ii hsh[N];
ii hshSum[N];
ii prefSum[N];

void add(ii& a, ii b) {
	a.x ^= b.x;
	a.y ^= b.y;
}

bool isOkay(int l, int r) {
	if (l <= 0) return false;
	if (r > n) return false;

	ii currSum = prefSum[r];
	add(currSum, prefSum[l - 1]);

	return currSum == hshSum[r - l + 1];
}

ll solve(int at) {
	ll ret = 0LL;

	int r;
	int mx = 1;
	for (r = at + 1; r <= n && a[r] != 1; r++) {
		mx = max(mx, a[r]);

		ret += isOkay(r - mx + 1, r);
	}

	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	ll x = 0LL;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		x ^= a[i];
	}

	mt19937 rnd(time(NULL));
	for (int i = 1; i < N; i++) {
		hsh[i].x = rnd() ^ x;
		hsh[i].y = rnd() ^ x;

		hshSum[i] = hsh[i];
		add(hshSum[i], hshSum[i - 1]);
	}

	ll ans = 0LL;

	for (int tc = 0; tc < 2; tc++) {
		for (int i = 1; i <= n; i++) {
			prefSum[i] = hsh[a[i]];
			add(prefSum[i], prefSum[i - 1]);
		}

		for (int i = 1; i <= n; i++) {
			if (a[i] == 1) {
				ans += solve(i);
				ans += (tc == 0);
			}
		}

		reverse(a + 1, a + n + 1);
	}

	cout << ans << endl;

	return 0;
}