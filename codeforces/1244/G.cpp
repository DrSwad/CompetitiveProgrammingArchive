#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 1e6 + 10;

int n;
ll k;
int a[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;

	k -= n * 1LL * (n + 1) / 2;
	if (k < 0) {
		printf("-1\n");
		return 0;
	}

	iota(a + 1, a + n + 1, 1);
	reverse(a + 1, a + n + 1);

	ll added = 0;
	for (int i = 1; i <= n / 2; i++) added += a[i] - i;
	ll diff = max(0LL, added - k);

	printf("%lld\n", n * 1LL * (n + 1) / 2 + added - diff);

	for (int i = 1; i <= n / 2; i++) {
		if (diff >= a[i] - i) {
			diff -= (a[i] - i);
			swap(a[i], a[n + 1 - i]);
		}
	}

	if (diff == 1) {
		if (n % 2 == 1) {
			a[n / 2] = n / 2 + 1;
			a[n / 2 + 1] = n / 2;

			a[n / 2 + 2] = n / 2 + 2;
		}
		else {
			a[n / 2 - 1] = n / 2;
			a[n / 2] = n / 2 - 1;

			a[n / 2 + 1] = n / 2 + 2;
			a[n / 2 + 2] = n / 2 + 1;
		}
	}

	for (int i = 1; i <= n; i++) printf("%d ", i);
	printf("\n");
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	printf("\n");

	return 0;
}