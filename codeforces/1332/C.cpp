#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

const int N = int(1e5) + 10;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n, k;
		scanf("%d %d", &n, &k);
		string s;
		cin >> s;

		int ans = 0;
		for (int i = 0; i < k / 2; i++) {
			vector<int> cnt(26);
			int tot = 0;
			for (int j = 0; j < n / k; j++) {
				cnt[s[k * j + i] - 'a']++;
				cnt[s[k * j + k - 1 - i] - 'a']++;
				tot += 2;
			}

			ans += tot - *max_element(cnt.begin(), cnt.end());
		}

		if (k % 2 == 1) {
			vector<int> cnt(26);
			int tot = 0;
			for (int j = 0; j < n / k; j++) {
				cnt[s[k * j + k / 2] - 'a']++;
				tot++;
			}

			ans += tot - *max_element(cnt.begin(), cnt.end());
		}

		printf("%d\n", ans);
	}

	return 0;
}