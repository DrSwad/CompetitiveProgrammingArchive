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
		int n;
		scanf("%d", &n);

		vector<int> a(n), b(n);
		for (int &i : a) scanf("%d", &i);
		for (int &i : b) scanf("%d", &i);

		vector<vector<int>> pref(3, vector<int>(n, 0));
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < n; j++) {
				pref[i][j] = (a[j] == i - 1) + (j == 0 ? 0 : pref[i][j - 1]);
			}
		}

		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (a[i] < b[i] && (i == 0 || pref[2][i - 1] == 0)) flag = false;
			else if (a[i] > b[i] && (i == 0 || pref[0][i - 1] == 0)) flag = false;
		}

		if (flag) puts("YES");
		else puts("NO");
	}

	return 0;
}