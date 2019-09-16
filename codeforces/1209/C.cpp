#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 2e5 + 10;

int n;
char s[N];
int ans[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		cin >> n;
		scanf(" %s", s + 1);

		map<int, int> mp;

		for (int i = 1; i <= n; i++) mp[s[i]]++;

		bool flag = true;
		int maxi = 0, mini = -1;

		for (int i = 1; i <= n; i++) {
			mp[s[i]]--;
			if (mp[s[i]] == 0) mp.erase(s[i]);

			int col = 0;
			if (!mp.empty() && mp.begin()->x < s[i]) col = 2;

			if (s[i] < maxi) {
				if (col == 2) {
					flag = false;
					break;
				}
				col = 1;
			}
			maxi = max(maxi, (int)s[i]);

			if (mini != -1 && s[i] > mini) { 
				if (col == 1) {
					flag = false;
					break;
				}
				col = 2;
			}

			if (col == 0) col = 1;

			if (mini == -1 && col == 2) mini = s[i];

			ans[i] = col;
		}

		if (!flag) printf("-");
		else {
			for (int i = 1; i <= n; i++) printf("%d", ans[i]);
		}
		printf("\n");
	}

	return 0;
}