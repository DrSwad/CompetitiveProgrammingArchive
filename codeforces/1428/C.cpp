#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "/Users/swad/Desktop/CP/debug.h"
#endif

// const int N = int(1e5) + 10;
// const int MOD = int(1e9) + 7;



int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		string s;
		cin >> s;

		int queue = 0;
		for (char c : s) {
			if (queue && c == 'B') {
				queue--;
			} else {
				queue++;
			}
		}

		printf("%d\n", queue);
	}

	return 0;
}