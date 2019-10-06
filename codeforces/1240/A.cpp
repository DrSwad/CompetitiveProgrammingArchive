#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 2e5 + 10;

int n;
int a, b;
int x, y;
int arr[3 * N];
ll pref[3 * N];
ll k;

int gcd(int a, int b) {
	if (a < b) swap(a, b);

	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}

	return a;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	while (q--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			arr[i] /= 100;
		}
		sort(arr + 1, arr + n + 1, greater<int>());
		for (int i = 1; i <= 3 * n + 10; i++) pref[i] = pref[i - 1] + arr[i];

		scanf("%d %d", &x, &a);
		scanf("%d %d", &y, &b);
		scanf("%lld", &k);

		if (x < y) {
			swap(x, y);
			swap(a, b);
		}

		int ans = -1;
		for (int i = 1; i <= n; i++) {
			ll L = ll(a) / gcd(a, b) * b;

			int cnt_L = i / L;
			int cnt_a = i / a - cnt_L;
			int cnt_b = i / b - cnt_L;

			ll sum = pref[cnt_L] * (x + y) +
					(pref[cnt_L + cnt_a] - pref[cnt_L]) * x +
					(pref[cnt_L + cnt_a + cnt_b] - pref[cnt_L + cnt_a]) * y;

			if (sum >= k) {
				ans = i;
				break;
			}
		}

		printf("%d\n", ans);

		memset(arr, 0, sizeof arr);
		memset(pref, 0, sizeof pref);
	}

	return 0;
}