#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 4e5 + 10, MAX_k = 30;

int n, I;
int a[N];
int pref[N];
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> I;
	map<int, int> mp;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		mp[a[i]]++;
	}

	I *= 8;
	int maxk = min(I / n, MAX_k);
	int tot = mp.size();
	int maxK = min(1 << maxk, tot);

	int at = 0;
	for (auto i : mp) {
		at++;
		pref[at] = pref[at - 1] + i.y;
	}

	int ans = INT_MAX;
	for (int i = 1; i <= tot - maxK + 1; i++) {
		ans = min(ans, pref[i - 1] + pref[tot] - pref[i + maxK - 1]);
	}

	cout << ans << endl;
 
	return 0;
}