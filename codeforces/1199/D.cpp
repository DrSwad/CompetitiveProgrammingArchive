#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<ll, ll> ii;
 
#define x first
#define y second
 
const int N = 2e5 + 10;

int n;
int a[N];
int last[N];
int q;

int st[4 * N];
void update(int stI, int L, int R, int at, int val) {
	if ((L > at) || (R < at)) return;

	if (L == R) {
		st[stI] = max(st[stI], val);
		return;
	}

	int mid = (L + R) / 2;
	update((stI << 1), L, mid, at, val);
	update((stI << 1) + 1, mid + 1, R, at, val);

	st[stI] = max(st[(stI << 1)], st[(stI << 1) + 1]);
}
void update(int at, int val) {
	update(1, 1, q, at, val);
}
int query(int stI, int L, int R, int l, int r) {
	if ((L > r) || (R < l)) return 0;

	if ((L >= l) && (R <= r)) return st[stI];

	int mid = (L + R) / 2;
	int q1 = query((stI << 1), L, mid, l, r);
	int q2 = query((stI << 1) + 1, mid + 1, R, l, r);

	return max(q1, q2);
}
int query(int l, int r) {
	if (l > r) return 0;
	return query(1, 1, q, l, r);
}
 
int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	cin >> q;
	for (int i = 1; i <= q; i++) {
		int t;
		scanf("%d", &t);
		if (t == 1) {
			int p, x;
			scanf("%d %d", &p, &x);
			last[p] = i;
			a[p] = x;
		}
		else {
			int x;
			scanf("%d", &x);
			update(i, x);
		}
	}

	for (int i = 1; i <= n; i++) {
		int res = query(last[i] + 1, q);
		a[i] = max(a[i], res);
		printf("%d ", a[i]);
	}
 
	return 0;
}