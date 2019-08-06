#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 1e5 + 10;
const int LOG_A = 20;
const int MOD = 1e9 + 7;

int n;
int a[N];

int q;
ii q_data[N];
vector<int> q_at[N];
int powers[N];
int ans[N];

int base[LOG_A], sz;
bool tryGauss(int mask) {
	for (int i = 0; i < LOG_A; i++) {
		if ((mask & 1 << i) == 0) continue;

		if (!base[i]) return false;

		mask ^= base[i];
	}

	return true;
}
void addGauss(int mask) {
	for (int i = 0; i < LOG_A; i++) {
		if ((mask & 1 << i) == 0) continue;

		if (!base[i]) {
			base[i] = mask;
			sz++;

			return;
		}

		mask ^= base[i];
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> q;

	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	for (int i = 1; i <= q; i++) {
		scanf("%d %d", &q_data[i].x, &q_data[i].y);
		q_at[q_data[i].x].push_back(i);
	}

	powers[0] = 1;
	for (int i = 1; i < N; i++)
		powers[i] = powers[i - 1] * 2LL % MOD;

	for (int at = 1; at <= n; at++) {
		addGauss(a[at]);

		for (int at_q : q_at[at])
			if (tryGauss(q_data[at_q].y)) {
				ans[at_q] = powers[at - sz];
			}
	}

	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);

	return 0;
}