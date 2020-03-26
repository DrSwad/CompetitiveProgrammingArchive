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

int a[N], b[N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		a[1] = b[1] = 1;
		bool flag = false;
		char ch;
		scanf(" %c", &ch);

		for (int i = 2; i <= n; i++) {
			scanf(" %c", &ch);
			if (flag) {
				b[i] = 0;
				a[i] = ch - '0';
			}
			else {
				if (ch == '0' || ch == '2') a[i] = b[i] = (ch - '0') / 2;
				else {
					flag = true;
					a[i] = 0;
					b[i] = 1;
				}
			}
		}

		for (int i = 1; i <= n; i++) printf("%d", a[i]); puts("");
		for (int i = 1; i <= n; i++) printf("%d", b[i]); puts("");
	}

	return 0;
}