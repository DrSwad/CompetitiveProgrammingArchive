#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;
 
#define x first
#define y second
 
const int N = 1e6 + 10;

int n;
int p[N];
int l[N], r[N];

int q;
ii qlr[N];
vector<int> lQ[N], rQ[N];
ll ans[N];

li st[4 * N];
void update(int stI, int L, int R, int at, ii val) {
	if ((L > at) || (R < at)) return;

	if (L == R) {
		st[stI] = val;
		return;
	}

	int mid = (L + R) / 2;
	update((stI << 1), L, mid, at, val);
	update((stI << 1) + 1, mid + 1, R, at, val);

	st[stI].x = st[(stI << 1)].x + st[(stI << 1) + 1].x;
	st[stI].y = st[(stI << 1)].y + st[(stI << 1) + 1].y;
}
void update(int at, ii val) {
	update(1, 1, n, at, val);
}
li query(int stI, int L, int R, int l, int r) {
	if ((L > r) || (R < l)) return {0, 0};

	if ((L >= l) && (R <= r)) return st[stI];

	int mid = (L + R) / 2;
	li q1 = query((stI << 1), L, mid, l, r);
	li q2 = query((stI << 1) + 1, mid + 1, R, l, r);

	return {q1.x + q2.x, q1.y + q2.y};
}
li query(int l, int r) {
	return query(1, 1, n, l, r);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> q;
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= q; i++) scanf("%d", &qlr[i].x);
	for (int i = 1; i <= q; i++) scanf("%d", &qlr[i].y);

	for (int i = 1; i <= n; i++) {
		int at = i - 1;
		while (at > 0 && p[i] > p[at]) at = l[at] - 1;
		l[i] = at + 1;
	}

	for (int i = n; i >= 1; i--) {
		int at = i + 1;
		while (at <= n && p[i] > p[at]) at = r[at] + 1;
		r[i] = at - 1;
	}

	for (int i = 1; i <= q; i++) {
		lQ[qlr[i].x].push_back(i);
		rQ[qlr[i].y].push_back(i);
	}

	vector< vector<int> > upd(n + 10);
	for (int i = 1; i <= n; i++) {
		upd[l[i] + 1].push_back(i);
		upd[i + 1].push_back(-i);
	}

	for (int i = 1; i <= n + 1; i++) {
		for (int j : upd[i]) {
			if (j > 0) update(j, {l[j], 1});
			else update(-j, {0, 0});
		}

		for (int j : lQ[i]) {
			li res = query(i, qlr[j].y);
			ans[j] += res.x;
			ans[j] -= res.y * 1LL * i;
		}
	}

	for (int i = 1; i <= n + 1; i++) upd[i].clear();
	for (int i = 1; i <= n; i++) {
		upd[r[i] - 1].push_back(i);
		upd[i - 1].push_back(-i);
	}

	for (int i = n; i >= 0; i--) {
		for (int j : upd[i]) {
			if (j > 0) update(j, {r[j], 1});
			else update(-j, {0, 0});
		}

		for (int j : rQ[i]) {
			li res = query(qlr[j].x, i);
			ans[j] -= res.x;
			ans[j] += res.y * 1LL * i;
		}
	}

	vector<ll> pref(n + 1);
	pref[0] = 0LL;
	for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + (r[i] - l[i] + 1);

	for (int i = 1; i <= q; i++) ans[i] += pref[qlr[i].y] - pref[qlr[i].x - 1];

	for (int i = 1; i <= q; i++) printf("%lld ", ans[i]);

	return 0;
}