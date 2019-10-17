#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second
#define size(a) (int)a.size()

// const int N = 310;

int n;

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int at = j * n;
			int nxt = (j + 1) * n;
			if (j % 2 == 0) printf("%d", at + i + 1);
			else printf("%d", nxt - 1 - i + 1);

			if (j < n - 1) printf(" ");
		}
		printf("\n");
	}

	return 0;
}