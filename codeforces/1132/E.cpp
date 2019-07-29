#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 9;

ll W;
ll cnt[N];
ll ans;

vector<int> v(N, N);

void takeSmall(int at, ll take, ll& curr);

void goSmall(int at, ll& curr) {
	if (at == N) {
		ans = max(ans, curr);
		return;
	}

	if (v[at] == N) {
		for (ll i = 0; i <= min(cnt[at], (ll)N - 1); i++) {
			takeSmall(at, i, curr);
		}
	}
	else {
		for (ll i = cnt[at]; i >= max(0LL, cnt[at] - v[at] + 1); i--) {
			takeSmall(at, i, curr);
		}
	}
}

void takeSmall(int at, ll take, ll& curr) {
	if (take > at) {
		for (int j = at + 1; j <= min(take, (ll)N - 1); j++) v[j] = min(v[j], at);
	}
	curr += take * 1LL * at;

	if (curr <= W) goSmall(at + 1, curr);

	curr -= take * 1LL * at;
	if (take > at) {
		for (int j = at + 1; j <= min(take, (ll)N - 1); j++) {
			if (v[j] == at) v[j] = N;
		}
	}
}

void goBig(int at, int bigAt, ll& curr) {
	if (at == N) {
		ll rem = W - curr;
		ll maxi = min(rem / bigAt, cnt[bigAt]);

		ans = max(ans, curr + maxi * bigAt);

		return;
	}

	if (at < bigAt) {
		for (ll i = 0; i <= min(cnt[at], (ll)bigAt); i++) {
			curr += i * at;

			if (curr <= W) goBig(at + 1, bigAt, curr);

			curr -= i * at;
		}
	}
	else if (at > bigAt) {
		for (ll i = cnt[at]; i >= max(0LL, cnt[at] - bigAt + 1); i--) {
			curr += i * at;

			if (curr <= W) goBig(at + 1, bigAt, curr);

			curr -= i * at;
		}
	}
	else goBig(at + 1, bigAt, curr);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> W;
	for (int i = 1; i < N; i++) cin >> cnt[i];

	ll curr = 0LL;

	goSmall(1, curr);

	for (int i = 1; i < N; i++) {
		goBig(1, i, curr);
	}

	cout << ans << endl;

	return 0;
}