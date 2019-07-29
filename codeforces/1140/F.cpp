#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> ii;

#define x first
#define y second

const int N = 3e5 + 10, LOGN = 20;

int p[2 * N];
int s1[2 * N];
int s2[2 * N];

void init() {
	for (int i = 1; i < N; i++) {
		p[i] = i;
		s1[i] = 1;

		p[i + N] = i + N;
		s2[i + N] = 1;
	}
}

int* where[4 * LOGN * N];
int val[4 * LOGN * N];
int state = 0;

void rollback() {
	state--;
	(*where[state]) = val[state];
}

void change(int& x, int y) {
	where[state] = &x;
	val[state] = x;

	x = y;

	state++;
}

ll res = 0LL;

int parent(int x) {
	if (p[x] == x) return x;
	return parent(p[x]);
}

void merge(int x, int y) {
	x = parent(x);
	y = parent(y);

	if (x == y) return;

	if (s1[x] + s2[x] < s1[y] + s2[y]) swap(x, y);

	res -= s1[x] * 1LL * s2[x];
	res -= s1[y] * 1LL * s2[y];

	change(p[y], x);
	change(s1[x], s1[x] + s1[y]);
	change(s2[x], s2[x] + s2[y]);

	res += s1[x] * 1LL * s2[x];
}

vector<ii> st[4 * N];

void add(int stI, int L, int R, int l, int r, ii p) {
	if ((L > r) || (R < l)) return;

	if ((L >= l) && (R <= r)) {
		st[stI].push_back(p);
		return;
	}

	int mid = (L + R) / 2;
	add((stI << 1), L, mid, l, r, p);
	add((stI << 1) + 1, mid + 1, R, l, r, p);
}

ll ans[N];

void dfs(int stI, int L, int R) {
	ll lastRes = res;
	int lastState = state;

	for (ii p : st[stI]) merge(p.x, p.y + N);

	if (L == R) {
		ans[L] = res;
	}
	else {
		int mid = (L + R) / 2;
		dfs((stI << 1), L, mid);
		dfs((stI << 1) + 1, mid + 1, R);
	}

	while (state != lastState) rollback();
	res = lastRes;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	int q;
	cin >> q;

	map<ii, int> last;

	for (int i = 1; i <= q; i++) {
		ii p;
		scanf("%d %d", &p.x, &p.y);

		if (last.count(p)) {
			add(1, 1, q, last[p], i - 1, p);
			last.erase(p);
		}
		else {
			last[p] = i;
		}
	}

	for (auto x : last) {
		add(1, 1, q, x.y, q, x.x);
	}

	init();

	dfs(1, 1, q);

	for (int i = 1; i <= q; i++) {
		printf("%lld ", ans[i]);
	}

	return 0;
}