#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
typedef long double ld;
 
#define x first
#define y second
 
const int N = 105;

int n;
char s[N];
int a[N];
ll dp[N][N][N];

ll DP(int times, int l, int r) {
	if (times >= N || l > r) return 0LL;
	if (dp[times][l][r] != -1LL) return dp[times][l][r];

	ll& ret = dp[times][l][r];
	ret = 0LL;
	ret = max(ret, a[times] + DP(1, l + 1, r));

	for (int at = l + 1; at <= r; at++) {
		if (s[at] == s[l]) {
			ret = max(ret, DP(1, l + 1, at - 1) + DP(times + 1, at, r));
		}
	}

	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	scanf("%d %s", &n, s + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	memset(dp, -1, sizeof dp);
	cout << DP(1, 1, n) << endl;

	return 0;
}