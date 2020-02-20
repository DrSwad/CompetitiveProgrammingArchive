#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = 5010;
const int MOD = int(1e9) + 7;

int n, m;
int s[N];
vector<int> spos[N];
int f[N], h[N];
int l[N], r[N];
int cows_at[N];
int inv[N];
int ans[N];

int cows_got[N];
int ways_got[N];
void update(int l, int r, int c_got, int w_got, int inv_w_got) {
	if (l > r) return;
	cows_got[l] += c_got;
	cows_got[r + 1] -= c_got;
	ways_got[l] = ways_got[l] * 1LL * w_got % MOD;
	ways_got[r + 1] = ways_got[r + 1] * 1LL * inv_w_got % MOD;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &m);

	inv[1] = 1;
	for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * 1LL * (MOD - MOD / i) % MOD;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i]);
		spos[s[i]].push_back(i);
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &f[i], &h[i]);
	}

	for (int i = 1; i <= m; i++) {
		if (spos[f[i]].size() < h[i]) l[i] = -1, r[i] = -1;
		else {
			l[i] = spos[f[i]][h[i] - 1];
			r[i] = spos[f[i]][spos[f[i]].size() - h[i]];
			cows_at[l[i]]++;
		}
	}

	for (int i = 0; i <= n; i++) cows_got[i] = 0;
	for (int i = 0; i <= n; i++) ways_got[i] = 1;

	for (int i = 1; i <= n; i++) {
		int sz = spos[i].size();
		vector<int> pref(sz + 2, 0);
		for (int j = 1; j <= sz; j++) {
			pref[j] = pref[j - 1] + cows_at[spos[i][j - 1]];
		}
		for (int j = 0; j <= sz; j++) {
			int lcows = pref[j];
			int rcows = pref[sz - j];
			if (lcows > rcows) swap(lcows, rcows);
			int L = j == 0 ? 0 : spos[i][j - 1];
			int R = j == sz ? n + 1 : spos[i][j];
			if (lcows == 0) {
				if (rcows >= 1) {
					update(L + 1, R - 1, 1, rcows, inv[rcows]);
				}
			}
			else if (rcows >= 2) {
				update(L + 1, R - 1, 2, lcows * (rcows - 1), inv[lcows] * 1LL * inv[rcows - 1] % MOD);
			}
			else {
				update(L + 1, R - 1, 1, 2, inv[2]);
			}
		}
		for (int j = 1; j <= sz; j++) {
			int rcows = pref[sz - j];
			if (j <= sz - j) rcows--;
			if (rcows >= 1) {
				update(spos[i][j - 1], spos[i][j - 1], 1, rcows, inv[rcows]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		ways_got[i] = ways_got[i - 1] * 1LL * ways_got[i] % MOD;
		cows_got[i] += cows_got[i - 1];
	}
	for (int i = 1; i <= n; i++) {
		ways_got[i] = ways_got[i] * 1LL * cows_at[i] % MOD;
		cows_got[i] += cows_at[i] > 0;
	}

	int max_got = 0;
	for (int i = 1; i <= n; i++) {
		if (cows_at[i] > 0) {
			ans[cows_got[i]] = (ans[cows_got[i]] + ways_got[i]) % MOD;
			max_got = max(max_got, cows_got[i]);
		}
	}

	int curr_got = 0;
	int curr_ans = 1;
	vector<int> scnt(n + 1, 0);
	for (int i = 1; i <= m; i++) {
		if (r[i] != -1) {
			if (scnt[f[i]] == 0) curr_got++;
			scnt[f[i]]++;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (scnt[i] != 0) {
			curr_ans = curr_ans * 1LL * scnt[i] % MOD;
		}
	}
	ans[curr_got] = (ans[curr_got] + curr_ans) % MOD;
	max_got = max(max_got, curr_got);

	ans[0] = 1;
	printf("%d %d\n", max_got, ans[max_got]);

	return 0;
}