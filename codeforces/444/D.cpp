#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(5e4) + 10;
const int M = int(6e5) + 10;

int n;
char s[N];
vector<int> pos[M];
map<pii, int> dp;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%s", s + 1);
	n = strlen(s + 1);

	int p27[5];
	p27[0] = 1;
	for (int i = 1; i <= 4; i++) p27[i] = p27[i - 1] * 27;

	for (int len = 1; len <= 4; len++) {
		int num = 0;
		for (int i = 1; i <= n; i++) {
			num %= p27[len - 1];
			num *= 27;
			num += s[i] - 'a' + 1;
			if (i >= len) pos[num].push_back(i - len + 1);
		}
	}

	int q;
	cin >> q;

	while (q--) {
		string sa, sb;
		cin >> sa >> sb;

		int a = 0, b = 0;
		for (int i = 0; i < sa.length(); i++) a *= 27, a += sa[i] - 'a' + 1;
		for (int i = 0; i < sb.length(); i++) b *= 27, b += sb[i] - 'a' + 1;

		if (pos[a].size() > pos[b].size() ||
			(pos[a].size() == pos[b].size() && a > b)) {
			swap(sa, sb);
			swap(a, b);
		}

		if (dp.find(make_pair(a, b)) != dp.end()) printf("%d\n", dp[make_pair(a, b)]);
		else {
			int ans = n + 1;
			for (int i : pos[a]) {
				int _j = lower_bound(pos[b].begin(), pos[b].end(), i) - pos[b].begin();
				if (_j < pos[b].size()) {
					int j = pos[b][_j];
					int l = i;
					int r = max(i + sa.length() - 1, j + sb.length() - 1);
					ans = min(ans, r - l + 1);
				}

				_j--;
				if (_j >= 0) {
					int j = pos[b][_j];
					int l = j;
					int r = max(i + sa.length() - 1, j + sb.length() - 1);
					ans = min(ans, r - l + 1);
				}
			}

			if (ans > n) ans = -1;
			printf("%d\n", dp[make_pair(a, b)] = ans);
		}
	}

	return 0;
}