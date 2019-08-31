#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second

const int N = 2005;

int n, m, k;
int gid[N][N], val[N][N];
ii a[N], b[N];
vector<int> q_add[N];
vector<ii> row_q[N];
ll ans[N];

ll st[N][4 * N];
void update(int gid, int stI, int L, int R, int at, int del) {
	if (at < L || R < at) return;

	if (L == R) {
		st[gid][stI] += del;
		return;
	}

	int mid = (L + R) / 2;
	update(gid, (stI << 1), L, mid, at, del);
	update(gid, (stI << 1) + 1, mid + 1, R, at, del);

	st[gid][stI] = st[gid][(stI << 1)] + st[gid][(stI << 1) + 1];
}
void update(int gid, int at, int val) {
	update(gid, 1, 1, m, at, val);
}
ll query(int gid, int stI, int L, int R, int l, int r) {
	if (r < L || R < l) return 0;

	if (l <= L && R <= r) return st[gid][stI];

	int mid = (L + R) / 2;
	ll q1 = query(gid, (stI << 1), L, mid, l, r);
	ll q2 = query(gid, (stI << 1) + 1, mid + 1, R, l, r);

	return q1 + q2;
}
ll query(int gid, int l, int r) {
	return query(gid, 1, 1, m, l, r);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		int len;
		scanf("%d", &len);

		for (int j = 1; j <= len; j++) {
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);

			gid[x][y] = i;
			val[x][y] = w;
		}
	}

	bool state[N];
	fill(state, state + N, 1);

	int q;
	cin >> q;
	int at_q = 1;
	for (int i = 1; i <= q; i++) {
		char cmd[8];
		scanf(" %s", cmd);

		if (strcmp(cmd, "SWITCH") == 0) {
			int gid;
			scanf("%d", &gid);
			state[gid] ^= 1;
		}
		else {
			scanf("%d %d", &a[at_q].x, &a[at_q].y);
			scanf("%d %d", &b[at_q].x, &b[at_q].y);

			for (int i = 1; i <= k; i++) {
				if (state[i]) q_add[at_q].push_back(i);
			}

			row_q[a[at_q].x - 1].push_back({-1, at_q});
			row_q[b[at_q].x].push_back({1, at_q});

			at_q++;
		}
	}

	for (int row = 1; row <= n; row++) {
		for (int col = 1; col <= m; col++) {
			update(gid[row][col], col, val[row][col]);
		}

		for (ii qdata : row_q[row]) {
			int sign = qdata.x;
			int qid = qdata.y;

			for (int gid : q_add[qid]) {
				ans[qid] += sign * 1LL * query(gid, a[qid].y, b[qid].y);
			}
		}
	}

	for (int i = 1; i <= at_q - 1; i++) printf("%lld\n", ans[i]);

	return 0;
}