#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 2e5 + 10;

int h, n;
int p[N];
int ans;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	while (q--) {
		scanf("%d %d", &h, &n);
		for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
		ans = 0;
		for (int i = 1; i <= n - 1; i++) {
			if (i == n - 1) ans += p[n] != 1;
			else {
				if (p[i + 1] != p[i + 2] + 1) ans++;
				else i++;
			}
		}

		cout << ans << endl;
	}

	return 0;
}