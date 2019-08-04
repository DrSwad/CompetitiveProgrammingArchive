#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
typedef long double ld;
 
#define x first
#define y second
 
const int N = 505;

struct offer {
	ll a, b, k;

	bool operator < (const offer& other) const {
		return b > other.b;
	}
} offers[N];

int n;
ll dp[N][N];

ll DP(int day, int at) {
	ll &ret = dp[day][at];
	if (ret != -1) return ret;

	ret = 0LL;
	if (at == 0) return ret;

	offer off = offers[at];
	ret = DP(day, at - 1);
	ret = max(ret, DP(day, at - 1) + off.a - off.k * off.b);
	if (day >= 1) ret = max(ret, DP(day - 1, at - 1) + off.a - ((ll)day - 1) * off.b);

	return ret;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> offers[i].a >> offers[i].b >> offers[i].k;

	sort(offers + 1, offers + n + 1);

	memset(dp, -1, sizeof dp);

	ll ans = 0LL;
	for (int day = 0; day <= n; day++)
		ans = max(ans, DP(day, n));

	cout << ans << endl;

	return 0;
}