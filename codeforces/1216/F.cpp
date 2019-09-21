#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 2e5 + 10;

int n, k;
char s[N];
vector<int> routerPos;
ll dp[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
	
	cin >> n >> k >> (s + 1);

	for (int i = 1; i <= n; i++) if (s[i] == '1') routerPos.push_back(i);

	for (int i = 1; i <= n; i++) {
		// first helpful router
		int index = lower_bound(routerPos.begin(), routerPos.end(), i - k) - routerPos.begin();
		int pos;
		if (index == routerPos.size() || i + k < routerPos[index]) pos = -1;
		else pos = routerPos[index];

		dp[i] = i + dp[i - 1];
		if (pos != -1) dp[i] = min(dp[i], pos + dp[max(0, pos - k - 1)]);
	}

	cout << dp[n] << endl;

	return 0;
}