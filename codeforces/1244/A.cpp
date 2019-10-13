#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e5 + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int a, b, c, d, k;
		cin >> a >> b >> c >> d >> k;
		int ansx = -1, ansy;
		for (int x = 0; x <= k; x++) {
			if (x * c >= a && (k - x) * d >= b) {
				ansx = x, ansy = k - x;
			}
		}
		if (ansx == -1) cout << ansx << endl;
		else cout << ansx << " " << ansy << endl;
	}

	return 0;
}