#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 2e5 + 10;

int n, m;
int x[N];
int qid[N], xid[N];

pii loopOnce(int at, int len) {
	int at1 = upper_bound(x + 1, x + n + 1, x[at] + len) - x - 1;
	int len1 = len - (x[at1] - x[at]);

	int at2 = lower_bound(x + 1, x + n + 1, x[at1] - len1) - x;
	int len2 = len1 - (x[at1] - x[at2]);

	return {at2, len2};
}

int solve(int at, int len) {
	pii p = loopOnce(at, len);

	if (p.x != at) return solve(p.x, p.y);

	int lenChange = len - p.y;
	if (lenChange == 0) return at;
	len %= lenChange;
	return solve(at, len);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
	
	iota(qid + 1, qid + n + 1, 1);
	sort(qid + 1, qid + n + 1, [](int i, int j) {return x[i] < x[j];});
	for (int i = 1; i <= n; i++) xid[qid[i]] = i;

	sort(x + 1, x + n + 1);

	while (m--) {
		int at, len;
		scanf("%d %d", &at, &len);
		printf("%d\n", qid[solve(xid[at], len)]);
	}

	return 0;
}