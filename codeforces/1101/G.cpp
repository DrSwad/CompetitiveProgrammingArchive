#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 2e5 + 10, LOG_PREF = 31;

int n;
int base[LOG_PREF];

void tryGauss(int mask) {
	for (int i = 0; i < LOG_PREF; i++) {
		if ((mask & 1 << i) == 0) continue;

		if (!base[i]) {
			base[i] = mask;
			return;
		}

		mask ^= base[i];
	}

	if (mask != 0) {
		for (int i = 0; i < LOG_PREF; i++) {
			if ((mask & 1 << i) > 0) {
				base[i] = mask;
				return;
			}
		}
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;

	int pref = 0;

	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);

		pref ^= a;
		tryGauss(pref);
	}

	if (pref == 0) {
		cout << -1 << endl;
		return 0;
	}

	int ans = 0;

	for (int i = 0; i < LOG_PREF; i++) {
		ans += (base[i] > 0);
	}

	cout << ans << endl;

	return 0;
}