#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 2e5 + 10, LOGN = 20, M = 5e5 + 10;

int n;
ii a[N];
int nxt[N][LOGN];
int m;
ii q[N];
int st[M];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].x, &a[i].y);
	}

	sort(a + 1, a + n + 1);

	for (int i = 0, j = 1, mx = 0; i < M; i++) {
		while (j <= n && a[j].x <= i) {
			if (a[j].y > a[mx].y) mx = j;
			j++;
		}

		if (a[mx].y > i) st[i] = mx;
	}

	for (int i = n; i >= 1; i--) {
		nxt[i][0] = st[a[i].y];

		for (int p = 1; p < LOGN; p++) {
			nxt[i][p] = nxt[nxt[i][p - 1]][p - 1];
		}
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &q[i].x, &q[i].y);

		int cnt = 0;
		int at = st[q[i].x];
		while (nxt[at][0] != 0 && a[at].y < q[i].y) {
			int p;
			for (p = 0; p < LOGN - 1; p++) {
				if (nxt[at][p + 1] == 0 || a[nxt[at][p + 1]].y >= q[i].y) break;
			}

			cnt += 1 << p;
			at = nxt[at][p];
		}

		if (a[at].y < q[i].y) printf("-1\n");
		else printf("%d\n", cnt + 1);
	}

	return 0;
}