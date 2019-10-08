#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 3e5 + 10;

int n;
char s[N];
int a[N];
vector<int> pos[2];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	scanf("%s", s + 1);
	
	pos[0].push_back(0);
	pos[1].push_back(0);

	for (int i = 1; i <= n; i++) {
		a[i] = s[i] == 'A';
		pos[a[i]].push_back(i);
	}
	pos[0].push_back(n + 1);
	pos[1].push_back(n + 1);

	ll ans = n * 1LL * (n - 1) / 2;

	for (int d = 0; d < 2; d++) {
		for (int i = 1; i < pos[d].size() - 1; i++) {
			ans -= (pos[d][i + 1] - 1 - pos[d][i]);
		}
		for (int i = 1; i < pos[d].size() - 1; i++) {
			ans -= (pos[d][i] - 1 - pos[d][i - 1]);
		}
	}

	for (int i = 1; i < n; i++) {
		ans += a[i] != a[i + 1];
	}

	cout << ans << endl;

	return 0;
}