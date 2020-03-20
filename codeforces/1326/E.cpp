#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(3e5) + 10;

int n;
int p[N], ip[N];
int q[N], iq[N];
int ans[N];

int st[4 * N];
void stBuild(int stI, int L, int R) {
	if (L == R) {
		st[stI] = iq[L];
		return;
	}

	int mid = (L + R) / 2;
	stBuild((stI << 1), L, mid);
	stBuild((stI << 1) + 1, mid + 1, R);

	st[stI] = min(st[(stI << 1)], st[(stI << 1) + 1]);
}
void stBuild() {
	stBuild(1, 1, n);
}
int stQuery(int stI, int L, int R, int l, int r) {
	if (r < L || R < l) return INT_MAX;
	if (l <= L && R <= r) return st[stI];

	int mid = (L + R) / 2;
	int q1 = stQuery((stI << 1), L, mid, l, r);
	int q2 = stQuery((stI << 1) + 1, mid + 1, R, l, r);
	return min(q1, q2);
}
int stQuery(int l) {
	return stQuery(1, 1, n, l, n);
}
void stUpdate(int stI, int L, int R, int at) {
	if (R < at || at < L) return;
	if (L == R) {
		st[stI] = INT_MAX;
		return;
	}

	int mid = (L + R) / 2;
	stUpdate((stI << 1), L, mid, at);
	stUpdate((stI << 1) + 1, mid + 1, R, at);

	st[stI] = min(st[(stI << 1)], st[(stI << 1) + 1]);
}
void stUpdate(int at) {
	stUpdate(1, 1, n, at);
}

int st2[4 * N], lz[4 * N];
void pullUp(int stI, int L, int R) {
	int mid = (L + R) / 2;
	int left = mid - L + 1;
	int right = R - mid;
	st2[stI] = max(lz[(stI << 1)] + st2[(stI << 1)], lz[(stI << 1) + 1] + st2[(stI << 1) + 1]);
}
void pushDown(int stI, int L, int R) {
	lz[(stI << 1)] += lz[stI];
	lz[(stI << 1) + 1] += lz[stI];
	lz[stI] = 0;
}
int stQuery2(int stI, int L, int R) {
	int len = R - L + 1;
	if (lz[stI] + st2[stI] <= 0) return -1;
	if (L == R) return L;

	pushDown(stI, L, R);
	pullUp(stI, L, R);

	int mid = (L + R) / 2;
	int q = stQuery2((stI << 1) + 1, mid + 1, R);
	if (q != -1) return q;
	return stQuery2((stI << 1), L, mid);
}
int stQuery2() {
	return stQuery2(1, 1, n);
}
void stUpdate2(int stI, int L, int R, int l, int r, int val) {
	if (r < L || R < l) return;
	if (l <= L && R <= r) {
		lz[stI] += val;
		return;
	}

	pushDown(stI, L, R);

	int mid = (L + R) / 2;
	stUpdate2((stI << 1), L, mid, l, r, val);
	stUpdate2((stI << 1) + 1, mid + 1, R, l, r, val);

	pullUp(stI, L, R);
}
void stUpdate2(int l, int r, int val) {
	stUpdate2(1, 1, n, l, r, val);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		ip[p[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &q[i]);
		iq[q[i]] = i;
	}

	stBuild();

	int m = 1;
	for (int i = n; i >= 1; i--) {
		stUpdate2(1, ip[i], 1);
		int at = stQuery2();

		int min_iq = stQuery(at);
		int min_at = q[min_iq];
		stUpdate(min_at);
		stUpdate2(1, min_at, -1);

		while (m <= min_iq) ans[m++] = i;
	}

	for (int i = 1; i <= n; i++) {
		if (i > 1) printf(" ");
		printf("%d", ans[i]);
	}
	puts("");

	return 0;
}