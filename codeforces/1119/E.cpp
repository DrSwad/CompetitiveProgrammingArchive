#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(3e5) + 10;

int n;
int a[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	ll twos = 0;
	ll ans = 0;
	for (int i = n; i >= 1; i--) {
		if (a[i] == 1) {
			if (twos > 0) {
				ans++;
				twos--;
			}
		}
		else {
			if (a[i] % 2 == 1) {
				a[i] -= 3;
				ans++;
			}
			twos += a[i] / 2;
		}
	}
	ans += (2 * twos) / 3;
	cout << ans << endl;

	return 0;
}