#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 5e5 + 10;
const int MAGIC = 500;

int n;
int a[N];
int a_rem[MAGIC][MAGIC][2];
vector<int> a_check[N];
ll tot[N];

bool check(int x, int y) {
	int toty = tot[y];
	int x1 = 0, x2 = 0;

	int i;
	for (i = a_check[y].size() - 1; i >= 0 && x1 == 0; i--) {
		int j = a_check[y][i];
		if (a[j] >= x) x1 = j;
	}
	if (x1 == 0) return false;
	toty = toty - a[x1] / y + (a[x1] - x) / y;

	int new_a = a[x1] - x;
	int new_rem = new_a % y;

	for (; i >= 0 && x2 == 0; i--) {
		int j = a_check[y][i];
		if (a[j] >= x) x2 = j;
	}
	if (x2 == 0 && new_a < x) return false;

	if (x2 == 0 || (a[x2] % y < new_rem && x <= new_a)) {
		toty = toty - new_a / y + (new_a - x) / y;
	}
	else {
		toty = toty - a[x2] / y + (a[x2] - x) / y;
	}
	return toty >= x;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);

	for (int i = 2; i < MAGIC; i++) {
		for (int j = 1; j <= n; j++) {
			int rem = a[j] % i;
			a_rem[i][rem][0] = a_rem[i][rem][1];
			a_rem[i][rem][1] = j;

			tot[i] += a[j] / i;
		}

		for (int rem = 0; rem < i; rem++) {
			if (a_rem[i][rem][0] != 0) a_check[i].push_back(a_rem[i][rem][0]);
			if (a_rem[i][rem][1] != 0) a_check[i].push_back(a_rem[i][rem][1]);
		}
	}

	for (int i = MAGIC; i < N; i++) {
		int a_at = 0, num_at = 0;
		while (true) {
			num_at++;

			int a_nxt = lower_bound(a + 1, a + n + 1, num_at * i) - a;
			tot[i] += (a_nxt - a_at) * 1LL * (num_at - 1);

			a_at = a_nxt;
			if (a_at > 1 && a[a_at - 1] >= (num_at - 1) * i)
				a_check[i].push_back(a_at - 1);
			if (a_at > 2 && a[a_at - 2] >= (num_at - 1) * i)
				a_check[i].push_back(a_at - 2);

			if (num_at * i >= N) break;
		}

		sort(a_check[i].begin(), a_check[i].end(), [i](int x, int y) {
			int remx = a[x] % i;
			int remy = a[y] % i;
			return remx != remy ? remx < remy : x < y;
		});
	}

	ll ans = 0LL;
	for (int y = 2; y < N; y++) {
		int Lx = 2, Rx = N;
		while (Lx != Rx) {
			int midx = (Lx + Rx + 1) / 2;
			if (check(midx, y)) Lx = midx;
			else Rx = midx - 1;
		}
		if (check(Lx, y)) {
			ans = max(ans, y * 1LL * Lx);
		}
	}

	printf("%lld\n", ans);

	return 0;
}