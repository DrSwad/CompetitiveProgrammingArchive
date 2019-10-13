#include <bits/stdc++.h>

using namespace std;

#define debug(a) cerr << #a << ": " << a << endl

typedef long long ll;
typedef pair<int, int> pii;

#define x first
#define y second

const int N = 6e5 + 10;

int n, k;
char s[N];
int col[N];
int ans[N];
vector<pair<pii, int>> v;
int start;

void color(int l, int r, int lc, int rc) {
	int mid = (l + r) / 2;
	for (int i = l; i <= min(mid, l + k - 1); i++) ans[i % n] = lc;
	for (int i = max(mid + 1, r - k + 1); i <= r; i++) ans[i % n] = rc;
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	cin >> n >> k;
	scanf("%s", s);
	for (int i = 0; i < 3 * n; i++) {
		col[i] = s[i % n] == 'W';
		col[i]++;
	}

	for (int i = 0; i < 3 * n; ) {
		int c = col[i];
		int r = i;
		while (r < 3 * n && col[r] == c) r++;
		if (i + 1 < r) v.push_back({{i, r - 1}, c});
		i = r;
	}

	if (v.size() == 0) {
		printf("%s\n", s);
		return 0;
	}

	for (int i = 0; i < v.size(); i++) {
		auto p = v[i];
		int l = p.x.x;
		int r = p.x.y;
		int c = p.y;
		for (int i = l; i <= r; i++) ans[i % n] = c;
		if (i < v.size() - 1) {
			color(r + 1, v[i + 1].x.x - 1, c, v[i + 1].y);
		}
	}

	for (int i = 0; i < n; i++) {
		if (ans[i] == 0) {
			ans[i] = col[i] - 1;
			ans[i] ^= (k & 1);
			ans[i]++;
		}
		if (ans[i] == 1) printf("B");
		else if (ans[i] == 2) printf("W");
	}
	printf("\n");

	return 0;
}