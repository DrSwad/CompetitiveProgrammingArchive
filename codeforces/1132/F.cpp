#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<ll, ll> ii;

#define x first
#define y second

const int N = 505;

int n;
string s;
int dp[N][N];

int DP(int l, int r) {
	if (l > r) return 0;
	if (dp[l][r]) return dp[l][r];

	dp[l][r] = 1 + DP(l + 1, r);

	for (int i = l + 1; i <= r; i++) {
		if (s[l - 1] == s[i - 1]) {
			dp[l][r] = min(dp[l][r], DP(l + 1, i - 1) + DP(i, r));
		}
	}

	return dp[l][r];
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> s;
	cout << DP(1, n) << endl;

	return 0;
}