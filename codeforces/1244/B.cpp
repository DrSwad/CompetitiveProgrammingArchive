#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e3 + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		scanf("%d", &n);

		char s[N];
		scanf("%s", s + 1);

		int mini = n + 1, maxi = 0;
		for (int i = 1; i <= n; i++) {
			if (s[i] == '1') {
				mini = min(mini, i);
				maxi = max(maxi, i);
			}
		}

		int ans = n;
		ans = max(ans, 2 * maxi);
		ans = max(ans, 2 * (n + 1 - mini));

		printf("%d\n", ans);
	}

	return 0;
}