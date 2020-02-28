#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = 300 + 3;
const int M = int(2e6) + 3;

int n, m, q;
int cell[N * N];
bool vis[N * N];
int clan[N * N];
vector<pii> add[M], rem[M];
vector<pii> events[M];
int used[M];
int ans[M];

int findClan(int mem) {
	if (mem == clan[mem]) return mem;
	else return clan[mem] = findClan(clan[mem]);
}
bool merge(int mem1, int mem2) {
	if (vis[mem2] == 0) return false;

	mem1 = findClan(mem1);
	mem2 = findClan(mem2);
	if (mem1 == mem2) return false;
	clan[mem1] = mem2;
	return true;
}

void processColor(int color) {
	int cnt = 0;
	fill(vis, vis + n * m, 0);
	iota(clan, clan + n * m, 0);

	for (pii &p : add[color]) if (!vis[p.x]) {
		cnt++;
		if (p.x % m > 0) cnt -= merge(p.x, p.x - 1);
		if (p.x % m + 1 < m) cnt -= merge(p.x, p.x + 1);
		if (p.x / m > 0) cnt -= merge(p.x, p.x - m);
		if (p.x / m + 1 < n)cnt -= merge(p.x, p.x + m);
		vis[p.x] = true;
		events[p.y].push_back(make_pair(color, cnt));
	}

	cnt = 0;
	fill(vis, vis + n * m, 0);
	iota(clan, clan + n * m, 0);
	reverse(rem[color].begin(), rem[color].end());

	for (int at = 0; at < n * m; at++) if (cell[at] == color) {
		cnt++;
		if (at % m > 0) cnt -= merge(at, at - 1);
		if (at % m + 1 < m) cnt -= merge(at, at + 1);
		if (at / m > 0) cnt -= merge(at, at - m);
		if (at / m + 1 < n)cnt -= merge(at, at + m);
		vis[at] = true;
	}

	for (pii &p : rem[color]) if (!vis[p.x]) {
		events[p.y].push_back(make_pair(color, cnt));
		cnt++;
		if (p.x % m > 0) cnt -= merge(p.x, p.x - 1);
		if (p.x % m + 1 < m) cnt -= merge(p.x, p.x + 1);
		if (p.x / m > 0) cnt -= merge(p.x, p.x - m);
		if (p.x / m + 1 < n)cnt -= merge(p.x, p.x + m);
		vis[p.x] = true;
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &m, &q);
	int c;
	for (int i = 1; i <= q; i++) {
		int x, y;
		scanf("%d %d %d", &x, &y, &c);
		x--, y--;

		int at = x * m + y;
		rem[cell[at]].push_back(make_pair(at, i));
		cell[at] = c;
		add[cell[at]].push_back(make_pair(at, i));
	}

	for (int color = 0; color <= c; color++) processColor(color);
	events[0].push_back(make_pair(0, 1));

	int cnt = 0;
	for (int i = 0; i <= q; i++) {
		for (pii &e : events[i]) {
			cnt -= used[e.x];
			used[e.x] = e.y;
			cnt += used[e.x];
		}
		if (i) printf("%d\n", cnt);
	}

	return 0;
}