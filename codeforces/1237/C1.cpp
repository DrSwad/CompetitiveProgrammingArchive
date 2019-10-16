#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#endif

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 5e4 + 10;

struct point {
	int x, y, z, id;
} p[N];

int n;
bool vis[N];

double inline dist(int i, int j) {
	return sqrt(
		abs(p[i].x - p[j].x) * 1LL * abs(p[i].x - p[j].x) +
		abs(p[i].y - p[j].y) * 1LL * abs(p[i].y - p[j].y) +
		abs(p[i].z - p[j].z) * 1LL * abs(p[i].z - p[j].z)
		);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
		p[i].id = i;
	}

	priority_queue<pair<double, pii>> pq;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			pq.push({-dist(i, j), {i, j}});
		}
	}

	while (!pq.empty()) {
		auto top = pq.top(); pq.pop();
		int i = top.y.x;
		int j = top.y.y;
		if (vis[i] || vis[j]) continue;
		printf("%d %d\n", i, j);
		vis[i] = vis[j] = true;
	}

	return 0;
}