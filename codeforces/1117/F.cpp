#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
typedef long double ld;
 
#define x first
#define y second
 
const int N = 1e5 + 10, P = 20;

int n, p;
char s[N];
int A[P][P];

vector<int> pos[P];
int cnt[P][N];
bitset<(1 << P)> legal, curr_legal, dp;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> p;
	scanf("%s", s);
	for (int i = 0; i < p; i++)
	for (int j = 0; j < p; j++)
		cin >> A[i][j];

	for (int i = 0; i < p; i++) {
		for (int j = 1; j <= n; j++) {
			if (s[j - 1] == char('a' + i)) pos[i].push_back(j - 1);
			cnt[i][j] = cnt[i][j - 1] + (s[j - 1] == char('a' + i));
		}
	}

	legal.set();
	int full = (1 << p) - 1;

	for (int c1 = 0; c1 < p; c1++)
	for (int c2 = c1; c2 < p; c2++) {
		if (A[c1][c2]) continue;
		
		curr_legal.set();

		int at1 = 0, at2 = 0;
		while (at1 < pos[c1].size() && at2 < pos[c2].size()) {
			if (c1 == c2 && at1 == at2) {
				at2++;
				continue;
			}

			int L = pos[c1][at1];
			int R = pos[c2][at2];
			if (L > R) swap(L, R);
			
			int mask = 0;
			for (int i = 0; i < p; i++) {
				if (cnt[i][R] - cnt[i][L + 1] > 0)
					mask |= (1 << i);
			}

			if ((mask & 1 << c1) == 0 && (mask & 1 << c2) == 0) {
				curr_legal.reset(full ^ mask);
			}

			if (pos[c1][at1] < pos[c2][at2]) at1++;
			else at2++;
		}

		for (int mask = full; mask > 0; mask--) {
			if (!curr_legal.test(mask)) {
				for (int i = 0; i < p; i++) {
					if (i != c1 && i != c2 && mask & (1 << i))
						curr_legal.reset(mask ^ (1 << i));
				}
			}
		}

		legal &= curr_legal;
	}

	int ans = n;
	dp.set(full);
	for (int mask = full; mask >= 0; mask--) {
		if (dp.test(mask)) {
			int currAns = n;
			for (int i = 0; i < p; i++) {
				if (mask & (1 << i)) {
					if (legal.test(mask ^ (1 << i))) {
						dp.set(mask ^ (1 << i));
					}
				}
				else currAns -= cnt[i][n];
			}

			ans = min(ans, currAns);
		}
	}

	cout << ans << endl;

	return 0;
}